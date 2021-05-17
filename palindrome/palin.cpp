#include <iostream>
#include <algorithm> // max
#include <string>
#include <fstream>

using namespace std;
string sentence;

bool palin(string sentence, int len) {
	int left  = 0;
	int right = len - 1;

	while (left < right) { // over the haf of sentence
		if (sentence[left++] != sentence[right--]) return false; // not palin
	}

	return true; // palin
}

bool similar_palin(string sentence, int left, int right, bool flag) {
	if (left > right) return true;
	
	if (sentence[left] == sentence[right]) return similar_palin(sentence, left + 1, right - 1, flag);
	else if (flag) return false;
	else return max(similar_palin(sentence, left + 1, right, true), similar_palin(sentence, left, right - 1, true));
}

string result(string sentence) {
	int len = sentence.size();
	if (palin(sentence, len)) return "1";
	if (similar_palin(sentence, 0, len - 1, false)) return "2";
	else return "3";
}

int main() {
	int numberOfSentence;
	ifstream inputFile;
	ofstream outFile;

	inputFile.open("palin.inp");
	if (inputFile.is_open()) {
		outFile.open("palin.out");
		int i = 0;
		while (!inputFile.eof()) {
			string temp;

			getline(inputFile, temp);
			if (i++ == 0) {
				numberOfSentence = stoi(temp);
			} else {
				temp = result(temp) + "\n";
				outFile.write(temp.c_str(), temp.size());
			}
		}
		outFile.close();
	}
	inputFile.close();


	return 0;
}