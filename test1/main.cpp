#include<iostream>
#define N 2
typedef long long dout_t;
typedef int din_t;
#define NO_SYNTH

dout_t add(din_t din[N],int width){

    #ifdef NO_SYNTH
        long long *out_accum = (long long *)malloc(sizeof(long long));
        int * array_local = (int *)malloc(N * sizeof(int));
    #else
        //综合的时候使用以下进行替换 
        long long _out_accum;
        long long *out_accum = &_out_accum;
        std::cout << out_accum  << std::endl;
        int _array_local[N];
        std::cout << &_array_local[0] << "-------------------" << _array_local << std::endl;
        int* array_local = &_array_local[0];// &_array_local[0]与_array_local都是数组的首地址
    #endif

    int i,j;
    LOOP:for(i = 0; i < N; i++){
        *(array_local + i) = din[i];
    }
    *out_accum = 0; //将out_accum中存储的值置为0;
    LOOP_SUM:for(j = 0; j < N; j++){
        *out_accum += *(array_local + j);
    }
    return *out_accum;
};

// #define MALLOC
void getMocloc(int B,int C){
    int *p;
    #ifdef MALLOC
        p = (int *)malloc(sizeof(int) * B * C);
    #else
        // int _p[B * C];
        // INIT:for(int i = 0; i < B * C; i++){
        //     p[i]=0;
        // }
        p = new int[B * C];
        for(int i = 0; i < B * C; i++){
            std::cout << *(p+i)  << "--";
        }
    #endif
    std::cout << p << std::endl;
}


int main(){

    din_t din[N];
    INIT:for(int i = 0; i < N; i++){
        din[i] = i + 1;
    }

    dout_t res = add(din,1);
    std::cout << din << std::endl; //传递的参数即地址;
    std::cout << res << std::endl;

    int *nums = (int *)malloc(sizeof(3));
    nums[0] = 1;
    std::cout << "nums[0] = " << nums[0] << std::endl;
    std::cout << sizeof(int) << "Bytes" << std::endl;


    getMocloc(2,2);
    getMocloc(2,3);
    getMocloc(2,4);
    getMocloc(2,5);

}