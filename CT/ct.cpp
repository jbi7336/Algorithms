#include <iostream>
#include <fstream>
#include <bitset>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;
#define INPUT  "ct.inp"
#define OUTPUT "ct.out"

int range;
int* col;
int* row;
int* backSlash;
int* slash;

bitset<3>* three;
bitset<4>* four;
bitset<5>* five;
bitset<6>* six;
bitset<7>* seven;
bitset<8>* eight;

void input_file() {
	ifstream inFile;

	inFile.open(INPUT);
	if (inFile.is_open()) {
		// input range
		inFile >> range;

		// make array
		col = new int[range];
		row = new int[range];
		backSlash = new int[range * 2 - 1];
		slash = new int[range * 2 - 1];

		for (int i = 0; i < range; i++)
			inFile >> col[i];

		for (int i = 0; i < range; i++)
			inFile >> row[i];

		for (int i = 0; i < range * 2 - 1; i++)
			inFile >> backSlash[i];

		for (int i = 0; i < range * 2 - 1; i++)
			inFile >> slash[i];
	}
	inFile.close();
}

int bit_count(int n) {
	int count = 0;
	while (n > 0) {
		count += n & 1;
		n >>= 1;
	}

	return count;
}

template <size_t r>
void bit_init(bitset<r>* mat) {
	for (int i = 0; i < range; i++)
		mat[i].reset();
}

template <size_t r>
bool is_safe(bitset<r>* bit, int* colT, int* slash, int* bSlash, int depth) {
	for (int i = 0; i < range; i++) {
		if (bit[depth][i] == 1) {
			colT[(range - 1) - i]--;
			slash[depth + (range - 1) - i]--;
			bSlash[depth + i]--;
		}
	}

	int x = *min_element(colT, colT + range);
	int y = *min_element(bSlash, bSlash + (2 * range - 1));
	int z = *min_element(slash, slash + (2 * range - 1));

	if (min(x, min(y, z)) < 0)
		return false;

	return true;
}

template <size_t r>
bool find_sol_util(bitset<r>* bitMatrix, int depth, int* col, int* slash, int* bSlash) {
	if (depth >= range)
		return true;

	int* colTemp = new int[range];
	int* slashTemp = new int[2 * range - 1];
	int* bSlashTemp= new int[2 * range - 1];
	int x, y;

	x = row[depth];
	y = int(pow(2, x) - 1);

	for (int i = y; i <= (y << (range - x)); i++) {
		if (bit_count(i) == row[depth]) { // bit 수가 맞다면
			// Copy
			memcpy(colTemp, col, sizeof(int) * (range));
			memcpy(slashTemp, slash, sizeof(int) * (2 * range - 1));
			memcpy(bSlashTemp, bSlash, sizeof(int) * (2 * range - 1));

			bitMatrix[depth] = i;
			if (is_safe(bitMatrix, colTemp, slashTemp, bSlashTemp, depth)) {

				if (find_sol_util(bitMatrix, depth + 1, colTemp, slashTemp, bSlashTemp))
					return true;
			} else {
				bitMatrix[depth] = 0; // init
			}
		}
	}

	return false;
}

template <size_t r>
void output_file(bitset<r>* bit) {
	ofstream outFile;

	outFile.open(OUTPUT);
	if (outFile.is_open()) {
		for (int i = 0; i < range; i++) {
			for (int j = range - 1; j >= 0; j--) {
				if (bit[i][j] == 1) {
					outFile << "B ";
				} else {
					outFile << "- ";
				}
			}
			outFile << "\n";
		}
	}
	outFile.close();
}

template <size_t r>
void find_sol(bitset<r>* bitMatrix) {
	bit_init(bitMatrix);
	find_sol_util(bitMatrix, 0, col, slash, backSlash);
	output_file(bitMatrix);
}

int main(void) {
	input_file();

	switch (range) {
		case 3:
			three = new bitset<3>[3];
			find_sol(three);
			break;
		case 4:
			four = new bitset<4>[4];
			find_sol(four);
			break;
		case 5:
			five = new bitset<5>[5];
			find_sol(five);
			break;
		case 6:
			six = new bitset<6>[6];
			find_sol(six);
			break;
		case 7:
			seven = new bitset<7>[7];
			find_sol(seven);
			break;
		case 8:
			eight = new bitset<8>[8];
			find_sol(eight);
			break;
	}

	return 0;
}