#include <iostream>

// 定义一个 Stride
struct Stride {
    size_t stride_B;
    size_t stride_C;
    size_t stride_H;
    size_t stride_W;

};

template<typename T>
struct Tensor {
    size_t B;
    size_t C;
    size_t H;
    size_t W;
    T* p = nullptr;

    Tensor() {

    }

    Tensor(size_t B, size_t C, size_t H, size_t W) : B(B), C(C), H(H), W(W) {
        // this->B = B;
        // this->C = C;
        p = (T*)malloc(sizeof(T) * B * C * H * W);
    }

    Stride stride() const {
         return Stride{C*H*W, H*W, W, 1};
    }

    size_t size() const{
        return B * C * H * W;
    }

    // 打印,把多维度的数据存储为1维数组
    void print_elems() const {
        size_t size = this->size();
        for( size_t i = 0; i < size; i++) {
            std::cout << p[i] << " ";
        }
        std::cout <<std::endl;
    }
};




template<typename T>
void add_array(T* p_a,T* p_b,T* res, size_t size){
    size_t i;
    for(i = 0; i < size; ++i) {
        res[i] = p_a[i] + p_b[i];
    }
}

// 进行广播
template<typename T>
void expand(Tensor<T>& src, Tensor<T>& dst) { // expand for broadcast,  e.g., 4*1*200*1 -> 4*3*200*400
    Stride src_str = src.stride();
    Stride dst_str = dst.stride();
    size_t src_index;
    size_t b_i, c_i, h_i, w_i;

    // adjust strides of dimensions with 1 to 0 for broadcasting.
    src_str.stride_B *= (src.B == 1 ? 0 : 1);
    src_str.stride_C *= (src.C == 1 ? 0 : 1);
    src_str.stride_H *= (src.H == 1 ? 0 : 1);
    src_str.stride_W *= (src.W == 1 ? 0 : 1);

    #ifdef USE_OMP
    #pragma omp parallel private(b_i,c_i,h_i,w_i, src_index) num_threads(4)
    {
        #pragma omp for schedule(static)
    #endif
        for(b_i = 0; b_i < dst.B; ++b_i) {
            for(c_i = 0; c_i < dst.C; ++c_i) {
                for(h_i = 0; h_i < dst.H; ++h_i) {
                    for(w_i = 0; w_i < dst.W; ++ w_i) {
                        src_index = 0;
                        src_index += b_i * src_str.stride_B;
                        src_index += c_i * src_str.stride_C;
                        src_index += h_i * src_str.stride_H;
                        src_index += w_i * src_str.stride_W;
                        dst.p[b_i * dst_str.stride_B + c_i * dst_str.stride_C + h_i *
                        dst_str.stride_H + w_i * dst_str.stride_W] = src.p[src_index];
                    }
                }
            }
        }
    #ifdef USE_OMP
    }
    #endif
}


//判断张量维度是否能够相加
/**
 * -1:不允许相加
 * 0: 无广播操作
 * 1: a需要执行广播操作
 * 2：b需要执行广播操作
 * 3：c需要执行广播操作
 *
*/
template<typename T>
int elem_wise_op_size_check(Tensor<T> &a,Tensor<T> &b){
    if(a.B != 1 && b.B != 1 && a.B != b.B) return -1;
    if(a.C != 1 && b.C != 1 && a.C != b.C) return -1;
    if(a.H != 1 && b.H != 1 && a.H != b.H) return -1;
    if(a.W != 1 && b.W != 1 && a.W != b.W) return -1;

    int broadcast_cnt = 0;
    if(a.B == 1 || a.C == 1 || a.H == 1 || a.W == 1)  broadcast_cnt += 1;
    if(b.B == 1 || b.C == 1 || b.H == 1 || b.W == 1)  broadcast_cnt += 2;

    // if((a.B == 1 && a.B != b.B )|| a.C == 1 || a.H == 1 || a.W == 1)  broadcast_cnt += 1;
    // 有一个特殊情况 BCHW a=(1,1,2,2),b=(1,2,2,2)时,不需要广播也行,此算法判断的时两者都需要广播
    return broadcast_cnt;
}



// 求和
template<typename T>
Tensor<T> add(Tensor<T>& a, Tensor<T>& b) {

    //判断是否需要广播
    int states = elem_wise_op_size_check(a,b);
    if( states == -1 ) return Tensor<T>();
    size_t res_B = std::max(a.B,b.B);
    size_t res_C = std::max(a.C,b.C);
    size_t res_H = std::max(a.H,b.H);
    size_t res_W = std::max(a.W,b.W);

    Tensor<T> res(res_B, res_C, res_H, res_W);

    if (states == 0) {  // no broadcast
        add_array(a.p, b.p, res.p, res.size());
    }else if (states == 1) { // broadcast a
        Tensor<T> broadcast_a(res_B, res_C, res_H, res_W);
        expand(a, broadcast_a);
        add_array(broadcast_a.p, b.p, res.p, res.size());
    } else if (states == 2) { // broadcast b
        Tensor<T> broadcast_b(res_B, res_C, res_H, res_W);
        expand(b, broadcast_b);
        add_array(a.p, broadcast_b.p, res.p, res.size());
    } else if (states == 3) { // broadcast a and b
        Tensor<T> broadcast_a(res_B, res_C, res_H, res_W);
        expand(a, broadcast_a);
        Tensor<T> broadcast_b(res_B, res_C, res_H, res_W);
        expand(b, broadcast_b);
        add_array(broadcast_a.p, broadcast_b.p, res.p, res.size());
    }
    return res;
}