#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "number.h"

using namespace std;
using namespace i2a;

bool composite(int m, int a[], int p, int d, vector<bool>& t)
{
    int n = m;
    int e = max(p-d+1,0);
    for (int i=p-1; i>=e; --i) {
        n += a[i];
        if (t[n])
            return false;
    }
    return true;
}

// select a number for position p in sequence a[], v[] record the number [n,m] which is available
bool AntiPrime(int n, int m, int d, int p, int a[], bool v[], vector<bool>& t)
{
	if (p == m-n+1)
		return true;
	for (int i = n; i <= m; ++i) {
        if (!v[i-n])
            continue;
        if (p == 0 || composite(i,a,p,d,t)) {
			v[i-n] = false;
            a[p] = i;
            if (!AntiPrime(n,m,d,p+1,a,v,t)) {
                v[i-n] = true;
                continue;
            }
            else
                return true;
        }
    }
    return false;
}

int main()
{
    int n,m,d;
    vector<bool> t = PreparePrimeTable(1000*10);
    int a[1001];
    bool v[1001];
    while (cin >> n >> m >> d) {
        if (n == 0 && m == 0 && d == 0)
            break;
        memset(v,1,sizeof(v));
        if (!AntiPrime(n,m,d,0,a,v,t))
            printf("No anti-prime sequence exists.\n");
        else {
            for (int i=0; i<=m-n; ++i) {
                if (i != m-n)
                    printf("%d,", a[i]);
                else
                    printf("%d\n", a[i]);
            }
        }
    }
    return 0;
}

