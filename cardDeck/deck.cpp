#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
#define INFILE  "deck.inp"
#define OUTFILE "deck.out"
typedef long long ll;

int main(void) {
	ifstream inFile;
	ofstream outFile;

	double diffMux, diffPlus;
	ll numberOfDeck, temp, cnt = 0;
	ll realSum = 0, logicSum = 0;
	ll realExp = 0, logicExp = 0;
	ll bigAns, smallAns;

	inFile.open(INFILE);
	if (inFile.is_open()) {
		inFile >> numberOfDeck;
		while (inFile >> temp) {
			realSum += temp;
			realExp += temp * temp;
			cnt++;
		}
	}
	inFile.close();
	

	logicSum = (numberOfDeck + 1) * numberOfDeck / 2;
	diffPlus = (logicSum - realSum);
	
	logicExp = (numberOfDeck + 1) * (2 * numberOfDeck + 1) * numberOfDeck / 6;
	diffMux = (diffPlus * diffPlus - (logicExp - realExp)) / 2;

	bigAns = (diffPlus + sqrt(diffPlus * diffPlus - 4 * diffMux)) / 2;
	smallAns = diffPlus - bigAns;


	outFile.open(OUTFILE);
	if (outFile.is_open()) {
		if (numberOfDeck - cnt == 1) { // 1
			outFile << diffPlus << endl;
		} else { // 2
			logicExp = (numberOfDeck + 1) * (2 * numberOfDeck + 1) * numberOfDeck / 6;
			diffMux = (diffPlus * diffPlus - (logicExp - realExp)) / 2;

			bigAns = (diffPlus + sqrtl(diffPlus * diffPlus - 4 * diffMux)) / 2;
			smallAns = diffPlus - bigAns;

			outFile << smallAns << "\n" << bigAns << endl;
		}
	}
	outFile.close();

	return 0;
}