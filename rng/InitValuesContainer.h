#pragma once
#include <vector>
#include <string>

using namespace std;

class InitValuesContainer
{
public:
	static const char delimiter = ':';
	static const char delimiterForVector = ',';
	InitValuesContainer() = default;
	InitValuesContainer(int argc, char* argv[]);
	void createInitVector(string const& str, vector<int>& out);
	void tokenize(string const& str, const char delimiter, vector<std::string>& out);
	vector<int> getInitVector();
	string getMethodCode();
	int getLengthOfSequence();
	string getFileName();
private:
	vector<int> initVector;
	string methodCode;
	int lenghtOfSequence = 10000;
	string fileName = "rnd.dat";

};
