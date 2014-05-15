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

int poj1365_()
{
    vector<int> t = PreparePrimeTable2(32768);
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
        
        int n = num-1;
        if (t[n] == 0)
            printf("%d 1\n", num-1);
        else {
            vector<int> fs = Factorization(n,t);
            printf("%d ", fs[0]);
            int e = 1;
            int l = fs[0];
            for (int i=1; i<fs.size(); ++i) {
                if (fs[i] == l)
                    ++e;
                else {
                   printf("%d %d ", e, fs[i]);
                    l = fs[i];
                    e = 1;
                }
            }
            printf("%d\n", e);
        }
    }
    return 0;
}

