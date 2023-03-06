#include <iostream>
#include "InitValuesContainer.h"
#include "SwitchForString.h"
#include "IGenerator.h"
#include "Clerk.h"
#include "Generators.h"
using namespace std;

void printInfo() {
	cout << "Params for programm : " << endl;
	cout << "   /g:<method_code> - defines the operating mode of the program. Possible values: lc, add, 5p, lfstr, nfsr, mt, rc4, rsa, bbs" << endl;
	cout << "   /i:<init_vector> - defines the init vector for generator" << endl;
	cout << "   /n:<sequence_length> - defines length of sequence. Default value: 10_000" << endl;
	cout << "   /f:<file_name> - defines the file to write the result to. Default value: rnd.dat" << endl;
	cout << "   /h - help info" << endl;
	cout << "Examples : " << endl;
	cout << "   linear congruent method - .\\rng.exe /g:lc /i:106,13,1283,6075 (a = 106, x_0 = 13, c = 1283, m = 6075)" << endl;
	cout << "   additive method - .\\rng.exe /g:add /i:5,7,377 (x_n-1 = 5, x_n-2 = 7, m = 377)" << endl;
	cout << "   shift register with feedback - .\\rng.exe /g:lfsr /i:12,541 (n = 12, x_0 = 541)" << endl;
	cout << "   5 parametrs register with feedback - .\\rng.exe /g:5p /i:107,31,57,82,30 (p = 107, q1 = 31, q2 = 57, q3 = 82, w = 30)" << endl;
	cout << "   Blum-Blum-Shab - .\\rng.exe /g:bbs /i:100151,224951,31 (p = 100151, q = 224951, x = 31)" << endl;
	cout << "   RC4 - .\\rng.exe /g:rc4 /i:1,2,3,4,5,6,7,31,48,178,46,91,30,15,132,154,108,222,245,211,103 (key = initvector)" << endl;
	cout << "   RSA - .\\rng.exe /g:rsa /i:100151,224951,287,22528,22 (n = 100151, p = 224951, e = 287, x_0 = 22528, l = 22)" << endl;
	cout << "   Nonlinear combination - .\\rng.exe /g:nfsr /i:30,1765421 /n:500 (n = 30, x_0 = 1765421)" << endl;
	cout << "   MT19937 - .\\rng.exe /g:mt /i:500 (seed = 500)" << endl;
}

int main(int argc, char *argv[])
{	
	InitValuesContainer container(argc, argv);
	IGenerator* generator = NULL;

	SWITCH(container.getMethodCode()) {
		CASE("lc") :
			generator = new Lc(container);
			break;
		CASE("add") :
			generator = new Add(container);
			break;
		CASE("5p") :
			generator = new FiveP(container);
			break;
		CASE("lfsr") :
			generator = new Lfsr(container);
			break;
		CASE("nfsr") :
			generator = new Nfsr(container);
			break;
		CASE("mt") :
			generator = new MT19937(container);
			break;
		CASE("rc4") :
			generator = new RC4(container);
			break;
		CASE("rsa") :
			generator = new RSA(container);
			break;
		CASE("bbs") :
			generator = new Bbs(container);
			break;
		CASE("h") :
			printInfo();
			break;
		DEFAULT:
			printInfo();
			break;
	}
	if (generator != NULL) {
		generator->generateSequence();
		Clerk clerk(generator);
		clerk.writeSequence();
	}
	return 0;
}

