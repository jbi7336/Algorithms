#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
#define INFILE  "free.inp"
#define OUTFILE "free.out"

class Job{
public:
	int startDay, finalDay, pay;
};

class Profit {
public:
	int workDay, totalProfit;
};

bool Job_sort(Job i, Job j) { // Sort Rule
	if (i.startDay == j.startDay)
		return (i.finalDay < j.finalDay);
	return (i.startDay < j.startDay);
}

bool Pro_sort(Profit i, Profit j) {
	if (i.totalProfit == j.totalProfit)
		return (i.workDay < j.workDay);
	return (i.totalProfit > j.totalProfit);
}

Job* input(int* jobList) {
	int i = 0;
	Job temp;
	Job* work;
	ifstream inFile;

	inFile.open(INFILE);
	inFile >> *jobList;
	work = new Job[*jobList];

	if (inFile.is_open()) {
		while (inFile >> temp.startDay >> temp.finalDay >> temp.pay) {
			work[i++] = temp;
		}
	}
	inFile.close();

	sort(work, work + *jobList, Job_sort);
	
	return work;
} // end of input

void findMaxProfit(Job* work, int n) {
	int cnt, maxHouse = 0;
	int tempP, tempD;
	ofstream outFile;
	Profit* pro;

	// init
	pro = new Profit[n];

	for (int i = 0; i < n; i++) {
		pro[i].totalProfit = work[i].pay;
		pro[i].workDay     = work[i].finalDay - work[i].startDay + 1;
	}

	// Calc table
	for (int i = 1; i < n; i++) {
		cnt = 0;
		for (int j = 0; j < i; j++) {
			if (work[j].finalDay < work[i].startDay) {
				tempP = work[i].pay + pro[j].totalProfit - 10;
				tempD = (work[i].finalDay - work[i].startDay + 1) + pro[j].workDay;

				if (pro[i].totalProfit < tempP) { // diff profit
					pro[i].totalProfit = tempP;
					pro[i].workDay	   = tempD;
				} else if (pro[i].totalProfit == tempP) { // same profit
					if (tempD < pro[i].workDay) {
						pro[i].workDay = tempD;
					}
				}
			}
		}
	}

	// Sort by Rule
	sort(pro, pro + n, Pro_sort);

	// Output
	outFile.open(OUTFILE);
	if (outFile.is_open()) {
		outFile << pro[0].totalProfit << " " << pro[0].workDay << endl;
	}
} // end of findMaxProfit

int main(void) {
	int jobList;
	Job* work;

	work = input(&jobList);
	findMaxProfit(work, jobList);

	return 0;
}