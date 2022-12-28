#include<iostream>
#define N 2
typedef long long dout_t;
typedef int din_t;
//#define NO_SYNTH

dout_t add(din_t din[N],int width){

    #ifdef NO_SYNTH
        long long *out_accum = malloc(sizeof(long long));
        int * array_local = malloc(N * sizeof(int));
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


int main(){

    din_t din[N];
    INIT:for(int i = 0; i < N; i++){
        din[i] = i + 1;
    }

    dout_t res = add(din,1);
    std::cout << din << std::endl; //传递的参数即地址;
    std::cout << res << std::endl;
}