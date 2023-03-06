#pragma once
#include "IGenerator.h"
class Clerk {
public:
	Clerk() = default;
	Clerk(IGenerator *gen) { generator = gen; }
	void writeSequence();

private:
	IGenerator *generator;
};