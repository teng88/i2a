#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "number.h"

using namespace std;
using namespace i2a;

//typedef signed int                  int32_t;
//typedef unsigned int                uint32_t;
//typedef signed long long int        int64_t;
//typedef unsigned long long int      uint64_t;


int main()
{
	// [2, 10 000]
	vector<bool> t = PreparePrimeTable(10000);
	int c[10001];
	int p[5001];
	int np = 0;
	memset(c, 0, sizeof(c));
	for (int i=2; i<=10000; ++i) {
		if (t[i]) {
			c[i] = 1;
			p[np] = i;
			++np;
		}
	}
	for (int i=0; i<np; ++i) {
		int sum = p[i];
		for (int j=i+1; j<np; ++j){
			sum += p[j];
			if (sum >= 10000)
				break;
			c[sum]++;	
		}
	}
	
	int n;
	while (cin >> n) {
		if (n == 0)
			break;
		printf("%d\n",c[n]);
	}
    return 0;
}

