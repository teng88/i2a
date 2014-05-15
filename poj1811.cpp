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

int poj1811()
{
    int32_t T;
    int64_t N; // 2 <= N < 2^54
    int64_t f;
    cin >> T;
    while (T > 0) {
        T--;
        cin >> N;
        
        if ((f=MinFactorPollardRho(N)) == N)
            cout << "Prime" << endl;
        else
            cout << f << endl;
    }
    
	return 0;
}