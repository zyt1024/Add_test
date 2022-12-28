#include "stdio.h"
#include "iomanip"
#include "vecAdd.h"
#include "iostream"
using namespace std;
int main(void){
	//	initial data
	data_t A[N]= {1,2,3,4,5,6};
	data_t c = 2;
	data_t B[N] = {0};
	data_t refB[N] = {3,4,5,6,7,8};
	unsigned int i = 0;
	unsigned int errcnt = 0;

	VectorAdd(A,c,B);

	std::cout << setfill('-') << setw(30) << '-' << '\n';
	std::cout << setfill(' ') << setw(10) << left << "A";
	std::cout << setfill(' ') << setw(10) << left << "c";
	std::cout << setfill(' ') << setw(10) << left << "B" << '\n';
	std::cout << setfill('-') << setw(30) << '-' << '\n';

	for(i = 0; i < N; i++ ){
		std::cout << setfill(' ') << setw(10) << left << A[i];
		std::cout << setfill(' ') << setw(10) << left << c;
		std::cout << setfill(' ') << setw(10) << left << B[i];
		if(B[i] == refB[i]){
			std::cout << '\n';
		}
		else{
			std::cout << "(" << refB[i] << ")" << '\n';
			errcnt++;
		}
	}
	if(errcnt > 0){
		std::cout << "TestFailed" << '\n';
	}else {
		std::cout << "TestFinished" << '\n';

	}
}