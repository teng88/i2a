#include "number.h"
#include <cmath>
#include <cstdlib>
#include <cstdint>

namespace i2a
{
	// test only
	int gcdBasic(int a, int b)
	{
        int pa = abs(a), pb = abs(b);
        if (a == 0)
            return pb;
        if (b == 0)
            return pa;
        
		int gcd = 1;
		int c = std::min(pa,pb);
		for (int i=2; i<=c; ++i) {
			if (pa%i == 0 && pb%i == 0)
				gcd = i;
		}
		return gcd;
	}
    
	// The extended form of Euclid's algorithm
    // input a >= 0 && b >= 0
	// d = gcd(a,b) = ax + by
	// d'= gcd(b,a mod b) = bx' + (a mod b)y' = bx' + (a - (a/b)*b)y'
	// => d = ay' + b(x'-(a/b)*y')
	// => x = y', y = x'-(a/b)*y'
	int GcdEuclid(int a, int b, int* x, int* y)
	{
		if (b == 0) {
			*x = 1; *y = 0;
			return a;
		}
		else {
			int d2, x2, y2;
			d2 = GcdEuclid(b, a%b, &x2, &y2);
			*x = y2; *y = x2-(a/b)*y2;
			return d2;
		}
	}

	// ax = b (mod n)
	// d = gcd(a,n) = x'a + y'n
	// ax0 = a(x'*(b/d)) (mod n)
	//     = d*(b/d)     (mod n)
	//     = b           (mod n)     
	// axi = a(x'*(b/d) + i*(n/d)) (mod n)
	//     = b + a*i*(n/d)         (mod n)
	//     = b                     (mod n)
	std::vector<int> ModularLinearEquationSolver(int a, int b, int n)
	{
		std::vector<int> rst;
		int d, x, y;
		d = GcdEuclid(a, n, &x, &y);

		if (b%d == 0) {
			int x0 = x * (b/d) % n;
			for (int i=0; i<d; ++i) {
				int xi = (x0 + i*(n/d))%n;
				rst.push_back(xi);
			}
		}
		return rst;
	}
    
    // a*b (mod n)
    int64_t MulMod(int64_t a, int64_t b, int64_t n)
    {
        int64_t s = 0;
        while(b) {
            if(b&1)
                s = (s+a)%n;
            a <<= 1;
            b >>= 1;
            if(a > n)
                a = a%n;
        }
        return s;
    }
    
    // a^b (mod n)
    int64_t ModularExponentiation(int64_t a, int64_t b, int64_t n)
    {
        //int c = 0;
        int64_t d = 1;
        std::vector<int> bb;
        do {
            bb.push_back(b&1);
            b >>= 1;
        }
        while (b > 0);
        
        int k = (int)bb.size();
        for (int i = k-1; i >= 0; --i) {
            //c = 2*c;
            //d = (d*d)%n;
            d = MulMod(d, d, n);
            if (bb[i] == 1) {
                //c = c+1;
                //d = (d*a)%n;
                d = MulMod(d, a, n);
            }
        }
        return d;
    }
    
    // We say that n is a base-a pseudoprime if n is composite and
    // a^(n-1) = 1 (mod n)
    // Fermat’s theorem implies that if n is prime, then n satisfies equation for every a in {1,2,...,n-1}
    // Thus, if we can find any a such that n does not satisfy equation, then n is certainly composite.
    // This func return false if n is composite, true if n is base-2 pseudoprime or true prime
    bool PseudoPrime(int n)
    {
        if (ModularExponentiation(2, n-1, n) != 1)
            return false;
        else
            return true;
    }
    
    // a^(n-1) = 1 (mod n) =>
    // (a^u)^(2^t), n-1 = (2^t)*u, u is odd
    // return TRUE if a is a “witness” to the compositeness of n
    // 2nd check: if n is prime, 0<x<n
    // x^2 = 1 (mod n) have solution x = 1 or n-1
    bool witness(int64_t a, int64_t n)
    {
        int64_t u = n-1, t = 0;
        while((u&1) == 0) {
            ++t;
            u >>= 1;
        }
        
        int64_t x0 = ModularExponentiation(a, u, n);
        for (int i=1; i<=t; ++i) {
            //int64_t xi = (x0*x0)%n;
            int64_t xi = ModularExponentiation(x0, 2, n);
            if (xi == 1 && x0 != 1 && x0 != n-1)
                return true;
            x0 = xi;
        }
        if (x0 != 1)
            return true;
        return false;
    }
    
    // The Miller-Rabin randomized primality test
    // n is an odd integer greater than 2
    // return true if composite, false if prime(almost surely)
    bool MillerRabin(int64_t n, int s)
    {
        for (int i=0; i<s; ++i) {
            int64_t a = rand()%(n-1)+1; // [1, n-1]
            if (witness(a,n))
                return true;    // definitely
        }
        return false;   // almost surely
    }
    
    // Integer factorization
    // POLLARD-RHO, factors any number up to R^4 (unless we are unlucky).
    int64_t PollardRho(int64_t n)
    {
        int64_t i = 1;
        int64_t x = rand()%(n-1)+1;
        int64_t y = x;
        int64_t k = 2;
        int64_t c = 0;
        while(c==0 || c==2)
            c = rand()%(n-1)+1;
        
        while (true) {
            ++i;
            x = (MulMod(x,x,n)+n-c)%n;
            int64_t d = GcdEuclid<int64_t>(y-x, n);
            if (d != 1 && d != n)
                return d;
            if (d == n)
                return n;
            if (i == k) {
                y = x;
                k *= 2;
            }
        }
    }
    
    int64_t minFactorPollardRho(int64_t n)
    {
        if(!MillerRabin(n))
            return n;
        
        int64_t p = PollardRho(n);
        if(p > 1)
            p = minFactorPollardRho(p);
        if(p < n) {
            int64_t q = n/p;
            q = minFactorPollardRho(q);
            if(q < p)
                p = q;
        }
        return p;
    }
    
    int64_t MinFactorPollardRho(int64_t n)
    {
        if ((n&1) == 0)
            return 2;
        return minFactorPollardRho(n);
    }
    
    // test function for number.h
    void NumberTest()
	{
		/*printf("start testing GcdEuclid\n");
        for (int i=-1000; i <= 1000; ++i) {
            for (int j=-1000; j <= 1000; ++j) {
                if (GcdBasic(i, j) != GcdEuclid(i, j))
                    printf("failed at i,j = %d,%d\n", i, j);
            }
        }
		printf("end testing\n");*/
        
        /*printf("start testing GcdEuclid extended\n");
        for (int i=0; i <= 10000; ++i) {
            for (int j=0; j <= 10000; ++j) {
                int x,y;
                int gcd = GcdEuclid(i, j, &x, &y);
                if (gcd != GcdEuclid(i, j)) {
                    printf("failed at i,j = %d,%d: gcd wrong\n", i, j);
                    continue;
                }
                if (i*x+j*y != gcd)
                    printf("failed at i,j = %d,%d: x,y wrong\n", i, j);
            }
        }
		printf("end testing\n");*/
        
        printf("start testing ModularExponentiation\n");
        if (ModularExponentiation(7, 560, 561) != 1)
            printf("failed\n");
        printf("end testing\n");
        
        /*printf("start testing MillerRabin\n");
        int64_t test_case[] = {
            1729,
            294409,
            56052361,
            118901521,
            172947529,
            216821881,
            228842209,
            1299963601,
            2301745249,
            9624742921,
            11346205609,
            13079177569,
            21515221081,
            27278026129,
            65700513721,
            71171308081,
            100264053529,
            168003672409,
            172018713961,
            173032371289,
            464052305161,
            527519713969,
            663805468801,
            727993807201,
            856666552249,
            1042789205881,
            1201586232601,
            1396066334401,
            1544001719761,
            1797002211241,
            1920595706641,
            2028691238689,
            2655343122121,
            2718557844481,
            2724933935809,
            2920883888089,
            3091175755489,
            3267961077889,
            3296857440241,
            3414146271409,
            3711619793521,
            3719466204049,
            3878725359169,
            4287981117241,
            4507445537641,
            6323547512449,
            7622722964881,
            8544361005001,
            8681793690961,
            9332984447209,
            11004252611041,
            11413778221441,
            11765530852489,
            13633039686169,
            14470947115561,
            14685655594249
        };
        int len = sizeof(test_case)/sizeof(test_case[0]);
        for (int i=0; i < len; ++i) {
            if (!MillerRabin(test_case[i]))
                printf("failed at %lld", test_case[i]);
        }
        printf("end testing\n");*/
	}
}