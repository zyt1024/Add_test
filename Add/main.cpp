#include "Add.h"
int main(){
    Tensor<int> t(1,2,3,4);
    Stride aa = t.stride();
    std::cout << "(" << aa.stride_B << ",";
    std::cout << aa.stride_C << ","; 
    std::cout << aa.stride_H << ",";
    std::cout << aa.stride_W << ")" << std::endl;
    std::cout << "t.size = " << t.size() << std::endl;

    // 生成张量A和B,并计算张量和

    // (B,C,H,W)
    Tensor<int> a(1,2,2,3);
    for(size_t i = 0; i < a.size();i++){
        a.p[i] = 1;
    }

    // (B,C,H,W)
    Tensor<int> b(1,1,2,1);
        for(size_t i = 0; i < b.size();i++){
        b.p[i] = 4;
    }
    Tensor<int> res = add(a,b);
    res.print_elems();
    return 0;
}
