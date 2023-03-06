#pragma once
#include <cmath>
#include <time.h>
#include "IGenerator.h"
#include <iostream>
#include "InitValuesContainer.h"
#include <random>
class Lc : virtual public IGenerator
{
public:
	Lc(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
private:
};

class Add : virtual public IGenerator
{
public:
	Add(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
private:
};

class Lfsr : virtual public IGenerator
{
public:
	Lfsr(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
	void setPolynomial(vector<int> v);
private:
	vector<int> polynomial = {20,3,0};
};

class FiveP : virtual public IGenerator
{
public:
	FiveP(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
	int getRandomNumber(int min, int max);
};

class Bbs : virtual public IGenerator
{
public:
	Bbs(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
};

class RC4 : virtual public IGenerator
{
public:
	RC4(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
	
};

class RSA : virtual public IGenerator
{
public:
	RSA(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
	long long mod_pow(long long num, long long pow, long long mod);
};

class Nfsr : virtual public IGenerator
{
public:
	Nfsr(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
};

class MT19937 : virtual public IGenerator
{
public:
	MT19937(InitValuesContainer container) :IGenerator(container) {}
	void generateSequence() override;
	void tempering();
	long long generateSequenceElement();

private:
	long long w = 32, n = 624, f = 1812433253, m = 397, r = 31;
	long long a = 0x9908B0DF, d = 0xFFFFFFFF, b = 0x9D2C5680, c = 0xEFC60000;
	long long u = 11, s = 7, t = 15, l = 18, currentPos = 0;
	vector<long long> X;
};