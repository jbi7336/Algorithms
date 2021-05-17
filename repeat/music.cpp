#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;
#define INFILE  "music.inp"
#define OUTFILE "music.out"

void output(string fs, string bs, int startX, int startY, int maxX, int maxY, int maxValue);
void back_tracking(string fs, string bs, int** table, int maxValue[], int point[]);

int** fill_the_table(int** table, int point[], int maxValue[], string fs, string bs);
int** resize_table(string fs, string bs);

string input(int point[]) {
	ifstream inFile;
	string musicSheet;
	string filename;

	inFile.open(INFILE);
	if (inFile.is_open()) {
		inFile >> point[0] >> point[1] >> point[2];
		inFile >> musicSheet;
	} else {
		perror("File is not exist");
		exit(-1);
	}
	inFile.close();

	return musicSheet;
}

void output(string fs, string bs, int startX, int startY, int maxX, int maxY, int maxValue) {
	// File Output
	ofstream outFile;

	outFile.open(OUTFILE);
	if (outFile.is_open()) {
		string temp[2];
		temp[0] = fs.substr(startX, maxX - startX);
		temp[1] = bs.substr(startY, maxY - startY);

		outFile << fs.substr(startX, maxX - startX) << endl;
		outFile << bs.substr(startY, maxY - startY) << endl;
		outFile << maxValue << endl;
	}
	outFile.close();
}

void find_max_score(string musicSheet, int point[]) {
	int*** table;
	int maxValue[4] = { 0 };
	int sheetSize;
	string fs, bs;

	/*
	*	max[0] = maxValue
	*	max[1] = maxX
	*	max[2] = maxY
	*	max[3] = table index
	*/

	sheetSize = musicSheet.size();
	table = new int** [sheetSize - 1];

	for (int i = 1; i < sheetSize; i++) {
		fs = musicSheet.substr(0, i);
		bs = musicSheet.substr(i, sheetSize - i);

		table[i - 1] = fill_the_table(resize_table(fs, bs), point, maxValue, fs, bs);
	}

	fs = musicSheet.substr(0, maxValue[3]);
	bs = musicSheet.substr(maxValue[3], sheetSize - maxValue[3]);
	back_tracking(fs, bs, table[maxValue[3] - 1], maxValue, point);

	// Allocate memory delete
	delete[] table;
}

int** resize_table(string fs, string bs) {
	int** table;
	int fsSize, bsSize;

	fsSize = fs.size() + 1;
	bsSize = bs.size() + 1;

	// Table init
	table = new int* [fsSize];
	for (int i = 0; i < fsSize; i++)
		table[i] = new int[bsSize];

	for (int i = 0; i < fsSize; i++)
		table[i][0] = 0;

	for (int i = 0; i < bsSize; i++)
		table[0][i] = 0;

	return table;
}

int** fill_the_table(int** table, int point[], int maxValue[], string fs, string bs) {
	// Calc
	int fsSize = fs.size() + 1;
	int bsSize = bs.size() + 1;

	for (int i = 1; i < fsSize; i++) {
		for (int j = 1; j < bsSize; j++) {
			int plusOption;
			if (fs[i - 1] == bs[j - 1]) plusOption = point[0];
			else plusOption = point[1];

			table[i][j] = max(table[i - 1][j - 1] + plusOption,
				max(table[i - 1][j] + point[2], max(table[i][j - 1] + point[2], 0)));

			// Memorise maxValue location
			if (table[i][j] > maxValue[0]) {
				maxValue[0] = table[i][j];
				maxValue[1] = i;
				maxValue[2] = j;
				maxValue[3] = fsSize - 1;
			}
		}
	}

	return table;
}

void back_tracking(string fs, string bs, int** table, int maxValue[], int point[]) {
	int startX = maxValue[1];
	int startY = maxValue[2];

	while (1) {
		int leftValue = (table[startX][startY - 1] == table[startX][startY] - point[2]) ? table[startX][startY - 1] : 0;
		int digValue = (table[startX - 1][startY - 1] == table[startX][startY] - point[0] ||
			table[startX - 1][startY - 1] == table[startX][startY] - point[1]) ? table[startX - 1][startY - 1] : 0;
		int upValue = (table[startX - 1][startY] == table[startX][startY] - point[2]) ? table[startX - 1][startY] : 0;

		if (digValue >= leftValue && digValue >= upValue) {
			startX -= 1;
			startY -= 1;
		} else if (leftValue >= digValue && leftValue >= upValue) {
			startY -= 1;
		} else {
			startX -= 1;
		}

		if (table[startX][startY] == 0)
			break;
	}

	output(fs, bs, startX, startY, maxValue[1], maxValue[2], maxValue[0]);
}

int main(void) {
	string musicSheet;
	int point[3];

	musicSheet = input(point);
	find_max_score(musicSheet, point);

	return 0;
}