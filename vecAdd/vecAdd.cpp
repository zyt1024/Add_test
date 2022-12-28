#include "vecAdd.h"

void VectorAdd(data_t A[N],data_t c,data_t B[N]){
   #pragma HLS PIPELINE
	unsigned int i;
	myloop:for(i = 0;i < N;i++){
		#pragma HLS PIPELINE
		B[i] = A[i]+c;
	}
}