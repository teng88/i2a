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

// MillerRabin: s=5
int poj1365()
{
    string line;
    while (true) {
        getline (cin, line);
        if (line == "0")
            break;
        
        stringstream sline(line);
        // (2, 32767]
        int num = 1;
        int p, e;
        while (sline >> p >> e) {
            while (e > 0) {
                num *= p;
                --e;
            }
        }
        //cout << num-1 << endl;
        if (num-1 == 1) {
            cout << "1 1" << endl;
            continue;
        }
        
        vector<int64_t> fs = FactorizationPollardRho(num-1);
        for (int i=0; i<fs.size(); i+=2) {
            for (int j=i+2; j<fs.size(); j+=2) {
                if (fs[i] < fs[j]) {
                    std::swap(fs[i], fs[j]);
                    std::swap(fs[i+1], fs[j+1]);
                }
            }
        }
        for (int i=0; i<fs.size(); ++i) {
            cout << fs[i];
            if (i != fs.size()-1)
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}

