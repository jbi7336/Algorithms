#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

int main() {
	ifstream input;
	ofstream output;

	unordered_map<string, int> keywords;
	bool flag = false;
	int numberOfWords;
	string words;

	input.open("words.inp", ios::in);
	if (input.is_open()) {
		getline(input, words);
		numberOfWords = stoi(words);

		while (!input.eof()) {
			getline(input, words);
			keywords[words] += 1;
		}
	}
	input.close();

	for (auto w = keywords.begin(); w != keywords.end(); ++w) {
		if (w->second >= (numberOfWords / 2 + 1)) {
			words = w->first;
			flag = true;
		}
	}

	output.open("words.out", ios::out);
	if (output.is_open()) {
		if (flag == true)  output.write(words.c_str(), words.size());
		else output.write("NONE", 4);
	}
	output.close();

	return 0;
}