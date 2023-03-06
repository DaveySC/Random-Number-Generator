#include "Generators.h"

void Add::generateSequence() {
	vector<int> params = container.getInitVector();
	int current, prev = params.at(0), prevPrev = params.at(1), m = params.at(2);

	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		current = (prev + prevPrev) % m;
		sequence.push_back(current);
		prevPrev = prev;
		prev = current;
	}
}


void Lc::generateSequence()
{
	vector<int> params = container.getInitVector();
	int x = params.at(1);
	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		int xNext = (params.at(0) * x + params.at(2)) % params.at(3);
		sequence.push_back(xNext);
		x = xNext;
	}
}

void Lfsr::generateSequence()
{
	int number = container.getInitVector().at(1);
	int length = container.getInitVector().at(0);

	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		int controlBit = 0;
		for (size_t i = 0; i < polynomial.size(); i++)
		{
			controlBit ^= ((number >> polynomial.at(i)) & 1);
		}
		
		number = number >> 1;
		number = (controlBit << length) | number;
		sequence.push_back(number);
	}
	

}

void Lfsr::setPolynomial(vector<int> v)
{
	this->polynomial = v;
}

void FiveP::generateSequence()
{
	vector<int> params = container.getInitVector();
	int p = params.at(0), q1 = params.at(1), q2 = params.at(2),
		q3 = params.at(3), w = params.at(4);
	vector<int> number;
	vector<int> polynom = {0, q1, q2, q3};

	int counter = 0;
	
	for (size_t i = 0; i < p; i++) {
		int helper = getRandomNumber(0, 1);
		number.push_back(helper);
		counter += helper;
	}
	if (counter == 0) number[getRandomNumber(0, p - 2)] = 1;
	
	
	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		int controlBit = 0;
		for (size_t j = 0; j < polynom.size(); j++) controlBit ^= number.at(polynom.at(j));
		
		number.insert(number.end(), controlBit);
		number.erase(number.begin() + 1);
		long long sequenceElement = 0;
		for (size_t j = 0; j < w; j++)
		{
			sequenceElement = ((long long)number.at(j) << j) | sequenceElement;
		}
		sequence.push_back(sequenceElement);
	}

}

int FiveP::getRandomNumber(int min, int max)
{
	random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);

	return dist6(rng);
}

void Bbs::generateSequence()
{
	vector<int> params = container.getInitVector();
	long long p = params.at(0), q = params.at(1), x = params.at(2);
	long long n = p * q;
	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		x = (x * x) % n;
		sequence.push_back(x);
	}

}

//mb perebelat' nado, on tut generit chisla ot 0 do 255, mb nugno eto ispolzovat kak chasti dly inta
void RC4::generateSequence()
{
	const int length = 256;
	vector<int> secretKey = container.getInitVector();
	int sBox[length] = {0};
	int key[length] = {0};
	for (size_t i = 0; i < length; i++) sBox[i] = i;
	for (size_t i = 0; i < length; i++) key[i] = secretKey.at(i % secretKey.size());

	int j = 0;
	for (size_t i = 0; i < length; i++)
	{
		j = (j + sBox[i] + key[i]) % length;
		swap(sBox[i], sBox[j]);
	}
	j = 0; int i = 0, count = container.getLengthOfSequence();
	while (count-- > 0)
	{
		i = (i + 1) % length;
		j = (j + sBox[i]) % length;
		swap(sBox[i], sBox[j]);
		int t = (sBox[i] + sBox[j]) % length;
		sequence.push_back(sBox[t]);
	}

}

void RSA::generateSequence()
{
	vector<int> params = container.getInitVector();
	long long p = params.at(0), q = params.at(1), e = params.at(2), x = params.at(3), l = params.at(4);
	long long n = p * q, f = (p - 1) * (q - 1);


	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		long long counter = l - 1;
		long long seqElem = 0;
		for (size_t j = 0; j < l; j++)
		{
			x = mod_pow(x, e, n);
			long long bit = x & 1;
			seqElem = seqElem | (bit << counter);
			counter--;

		}
		sequence.push_back(seqElem);
	}

}

long long RSA::mod_pow(long long num, long long pow, long long mod)
{
	unsigned long long test;
	unsigned long long n = num;
	for (test = 1; pow; pow >>= 1)
	{
		if (pow & 1)
			test = ((test % mod) * (n % mod)) % mod;
		n = ((n % mod) * (n % mod)) % mod;
	}

	return test; 
}

void Nfsr::generateSequence()
{
	Lfsr g1(container);
	Lfsr g2(container);
	Lfsr g3(container);
	
	g1.setPolynomial({ 18,5,2,1,0});
	g2.setPolynomial({ 13,4,3,1,0 });
	g3.setPolynomial({ 17,3,0 });
	
	g1.generateSequence();
	g2.generateSequence();
	g3.generateSequence();

	vector<long long> s1 = g1.getGeneratedSequence();
	vector<long long> s2 = g2.getGeneratedSequence();
	vector<long long> s3 = g3.getGeneratedSequence();

	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		long long x = s1.at(i), y = s2.at(i), s = s3.at(i);
		
		long long out = (x & y) ^ (y & s) ^ s;
		sequence.push_back(out);
	}

}

void MT19937::generateSequence()
{
	//initialization
	long long seed = container.getInitVector().at(0);
	X.push_back(seed);
	for (size_t i = 1; i < this->n; i++)
	{
		long long tmp = (f * (X[i - 1] ^ (X[i - 1] >> (w - 2))) + i) & ((static_cast<long long>(1) << w) - 1);
		X.push_back(tmp);
	}

	for (size_t i = 0; i < container.getLengthOfSequence(); i++)
	{
		sequence.push_back(generateSequenceElement());
	}


}
void MT19937::tempering()
{
	for (size_t i = 1; i < this->n; i++)
	{
		int lowerMask = (1 << r) - 1;
		int upperMask = (~lowerMask) & ((1 << w) - 1);
		int tmp = (X[i] & upperMask) + (X[(i + 1) % n] & lowerMask);
		int tmpA = tmp >> 1;
		if (tmp % 2) tmpA = tmpA ^ a;
		X[i] = X[(i + m) % n] ^ tmpA;
	}
	currentPos = 0;
}
long long MT19937::generateSequenceElement()
{
	if (currentPos == n) tempering();
	long long y = X[currentPos];
	y = y ^ ((y >> u) & d);
	y = y ^ ((y << s) & b);
	y = y ^ ((y << t) & c);
	y = y ^ (y >> l);
	currentPos += 1;
	return y & ((static_cast<long long>(1) << w) - 1);
}