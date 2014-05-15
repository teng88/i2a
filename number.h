/**
 * @copyright
 * Copyright (C) 2010-2012 Lab of Machine Vision & Navigation, Zhejiang University. \n
 * All Rights Reserved.
 * 
 * @file     number.h
 * @brief    number brief description
 * 
 * @author   caoteng <teng.cao@foxmail.com>
 * @version  1.0
 * @date     2014/04/29
 * 
 * @details  number details description
 * @remarks  v1.0(2014/04/29): initial release for: 31 Number-Theoretic Algorithms
 */ 

#ifndef _I2A_NUMBER_
#define _I2A_NUMBER_

#include <vector>

namespace i2a
{
	//Theorem 31.9 (GCD recursion theorem)
	//	For any nonnegative integer a and any positive integer b,
	//	gcd(a,b) = gcd(b, a mod b).
	// For any integer k >= 1, if a > b >= 1 and b < F(k+1), then the call EUCLID(a,b)
	//  makes fewer than k recursive calls.
    template<typename T>
	T gcdEuclid(T a, T b)
	{
		if (b == 0)
			return a;
		else
			return gcdEuclid<T>(b, a%b);
	}
    
    // same as gcdEuclid, with support of negative numbers
    template<typename T>
    T GcdEuclid(T a, T b)
    {
        return gcdEuclid<T>(a>0?a:-a, b>0?b:-b);
    }
    
	// The extended form of Euclid's algorithm
    // input a >= 0 && b >= 0
	// d = gcd(a,b) = ax + by
	// d'= gcd(b,a mod b) = bx' + (a mod b)y' = bx' + (a - (a/b)*b)y'
	// => d = ay' + b(x'-(a/b)*y')
	// => x = y', y = x'-(a/b)*y'
	int GcdEuclid(int a, int b, int* x, int* y);

	// ax = b (mod n)
	// d = gcd(a,n) = x'a + y'n
	// ax0 = a(x'*(b/d)) (mod n)
	//     = d*(b/d)     (mod n)
	//     = b           (mod n)     
	// axi = a(x'*(b/d) + i*(n/d)) (mod n)
	//     = b + a*i*(n/d)         (mod n)
	//     = b                     (mod n)
	std::vector<int> ModularLinearEquationSolver(int a, int b, int n);
    
    // a^b (mod n)
    int64_t ModularExponentiation(int64_t a, int64_t b, int64_t n);
    
    // We say that n is a base-a pseudoprime if n is composite and
    // a^(n-1) = 1 (mod n)
    // Fermat’s theorem implies that if n is prime, then n satisfies equation for every a in {1,2,...,n-1}
    // Thus, if we can find any a such that n does not satisfy equation, then n is certainly composite.
    // This func return false if n is composite, true if n is base-2 pseudoprime or true prime
    bool PseudoPrime(int n);
    
    // The Miller-Rabin randomized primality test
    // n is an odd integer greater than 2
    // return true if composite, false if prime(almost surely)
    bool MillerRabin(int64_t n, int s=50);
    
    // Integer factorization
    // find a factor of n (return n if no succeed, dead loop if n is prime)
    // POLLARD-RHO, factors any number up to R^4 (unless we are unlucky).
    int64_t PollardRho(int64_t n);
    
    // find the smallest factor of n (return n if n is a prime)
    int64_t MinFactorPollardRho(int64_t n);
    
    // get the int factorization of n with pollard rho algorithm
    // in the form of: p1 e1 p2 e2 p3 e3 ...
    // where, n = p1^e1 * p2^e2 * p3^e3 ...
    std::vector<int64_t> FactorizationPollardRho(int64_t n);
    
    // generate the prime table for numbers [0 n]
    std::vector<bool> PreparePrimeTable(int n);
    
    // test function for number.h
    void NumberTest();
}

#endif