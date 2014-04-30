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
	void NumberTest()
	{
		printf("start testing\n");
		printf("end testing\n");
	}

	// test only
	int GcdBasic(int a, int b)
	{
		int gcd = 1;
		int c = std::min(a,b);
		for (int i=2; i<=c; ++i) {
			if (a%i == 0 && b%i == 0)
				gcd = i;
		}
		return gcd;
	}

	//Theorem 31.9 (GCD recursion theorem)
	//	For any nonnegative integer a and any positive integer b,
	//	gcd(a,b) = gcd(b, a mod b).
	// For any integer k >= 1, if a > b >= 1 and b < F(k+1), then the call EUCLID(a,b)
	//  makes fewer than k recursive calls.
	int GcdEuclid(int a, int b)
	{
		if (b == 0)
			return a;
		else
			return GcdEuclid(b, a%b);
	}

	// The extended form of Euclid's algorithm
	// d = gcd(a,b) = ax + by
	// d'= gcd(b,a mod b) = bx' + (a mod b)y' = bx' + (a - (a/b)*b)y'
	// => d = ay' + b(x'-(a/b)*b*y')
	// => x = y', y = x'-(a/b)*b*y'
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

	// ax = b (mod n)
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
}

#endif