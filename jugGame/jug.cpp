#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;

#define INFILE  "jug.inp"
#define OUTFILE "jug.out"

int check_overlap(int A[3][100], int n, int S[], int m, int pre);

int who_win(int A[3][100], int n, int S[], int m) {
    for (int i = 0; i < m; i++) {
        int x = check_overlap(A, n, S, m, i);
        if (x == 1) {
            return 1;
        }
    }

    return 2;
} // end of who_win()

int check_overlap(int A[3][100], int n, int S[], int m, int pre) {
    // n = numberOfStone
    // Exist calc data return data
    if (A[pre][n] != 0) {
        return A[pre][n];
    }

    // init
    if (n == 0 || n < S[0]) {
        A[pre][n] = 1;
        return 1;
    }

    // Overlap Check
    for (int j = 0; j < m; j++) {
        // Not allow negative number
        // And Check preSelect number
        if (j != pre && (n - S[j]) >= 0) {
            int x = check_overlap(A, n - S[j], S, m, j);
            if (x == 2) {
                A[pre][n] = 1;
                return 1;
            }
        }
    }
    A[pre][n] = 2;
    return 2;
} // end of check_overlap()

void input(int S[], int findWhosWin[]) {
    ifstream inFile;

    inFile.open(INFILE);
    if (inFile.is_open()) {
        inFile >> S[0] >> S[1] >> S[2];
        for (int i = 0; i < 10; i++) {
            inFile >> findWhosWin[i];
        }
    }
    inFile.close();
} // end of input()

void output(int findWhosWin[], int* AnsTable) {
    ofstream outFile;
    int j = 0;

    outFile.open(OUTFILE);
    if (outFile.is_open()) {
        for (int i = 0; i < 10; i++) {
            // Data 1 == First Win
            // Data 2 == Second Win
            if (AnsTable[findWhosWin[i]] == 1) outFile << "F" << endl;
            else outFile << "S" << endl;
        }
    }
    outFile.close();
} // end of output()

int main(void) {
    int Array[3][100] = { 0 };
    int findWhosWin[10];
    int S[3];
 
    // input
    input(S, findWhosWin);
    int maxStone = *max_element(findWhosWin, findWhosWin + 10);
    int* AnsTable = new int[maxStone + 1];

    // calc
    // calculate number of stone start from 0
	for (int i = 0; i <= maxStone; i++) {
        AnsTable[i] = who_win(Array, i, S, 3);
	}

    // Output
    output(findWhosWin, AnsTable);

    delete AnsTable;
    
    return 0;
}