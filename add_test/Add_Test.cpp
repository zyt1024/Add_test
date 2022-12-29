#include "Add_Test.h"

int main(){

    // 生成张量A和B,并计算张量和
    // (B,C,H,W)
    Tensor<int> a(1,2,1,3);
    for(size_t i = 0; i < a.size();i++){
        a.p[i] = i + 1;
    }

    

    // (B,C,H,W)
    Tensor<int> b(1,1,2,1);
        for(size_t i = 0; i < b.size();i++){
        b.p[i] = 7 + i;
    }
    Tensor<int> res = add<int>(a,b);
    res.print_elems();
    print(a);
    a.shape();
    print(b);
    b.shape();
    print(res);
    res.shape();

    // Tensor<int> multiply_res = multiply<int>(a,b);
    // multiply_res.print_elems();
    return 0;
}