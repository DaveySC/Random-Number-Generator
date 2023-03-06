#include <iostream>
#include <fstream>
#include "Clerk.h"

void Clerk::writeSequence() {
	ofstream out;
	out.open(generator->getContainer().getFileName());
	vector<long long> seqence = generator->getGeneratedSequence();
	for (size_t i = 0; i < seqence.size(); i++)
	{
		out << seqence.at(i) << " ";
	}
	out.close();
}
