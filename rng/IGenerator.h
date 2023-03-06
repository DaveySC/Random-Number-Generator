#pragma once
#include <vector>
#include "InitValuesContainer.h"

using namespace std;

class IGenerator
{
protected:
	InitValuesContainer container;
	vector<long long> sequence;
public:
	IGenerator() = default;
	IGenerator(InitValuesContainer cont) { container = cont; }
	virtual void generateSequence() = 0;
	vector<long long> getGeneratedSequence();
	InitValuesContainer getContainer();
private:
	
};

