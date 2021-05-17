#include <iostream>
#include <fstream>
#include <cmath>
#include <cfloat>

using namespace std;
#define INFILE  "station.inp"
#define OUTFILE "station.out"

class Point {
public:
	double x, y, z;
	
	Point(double ex = 0, double ey = 0, double ez = 0) {
		x = ex; y = ey; z = ez;
	}

	Point operator+(const Point& p) {
		return Point(x + p.x, y + p.y, z + p.z);
	}

	Point operator/(const double& n) {
		return Point(x / n, y / n, z / n);
	}
};

double distance(Point p, Point q) {
	double ans;
	ans = sqrt(pow(q.x - p.x, 2) + pow(q.y - p.y, 2) + pow(q.z - p.z, 2));

	return ans;
}

double div_con(Point p, Point s, Point f, double dist) {
	Point mid   = (s + f)   / 2;
	Point left  = (s + mid) / 2;
	Point right = (mid + f) / 2;

	double ld, rd, md;
	md = distance(p, mid);
	ld = distance(p, left);
	rd = distance(p, right);
	
	if (md == 0 || abs((dist - md)) <= 1e-30) return md;
	dist = md;

	if (ld < rd)
		return div_con(p, s, mid, dist);
	else
		return div_con(p, mid, f, dist);
}

double div_sol(Point A, Point B, Point C, Point D, double dist) {
	Point mid_AB   = (A + B)      / 2;
	Point left_AB  = (A + mid_AB) / 2;
	Point right_AB = (mid_AB + B) / 2;
	
	double ld, rd, md;
	md = div_con(mid_AB  , C, D, dist);
	ld = div_con(left_AB , C, D, dist);
	rd = div_con(right_AB, C, D, dist);

	if (md == 0 || abs((dist - md)) <= 1e-30) return md;
	dist = md;

	if (ld < rd)
		return div_sol(A, mid_AB, C, D, dist); // Come B
	else
		return div_sol(mid_AB, B, C, D, dist); // Come A
}

int main(void) {
	ifstream inFile;
	ofstream outFile;
	Point pnt[4];
	int i = 0;

	inFile.open(INFILE);
	if (inFile.is_open()) {
		int x, y, z;
		while (inFile >> x >> y >> z) {
			pnt[i  ].x = x;
			pnt[i  ].y = y;
			pnt[i++].z = z;
		}
	}
	inFile.close();

	double ans = div_sol(pnt[0], pnt[1], pnt[2], pnt[3], DBL_MAX);
	double b = ans - round(ans);

	outFile.open(OUTFILE);
	if (outFile.is_open()) {
		if (b <= 0.00000001) outFile << round(ans);
		else outFile << ceil(ans);
	}
	outFile.close();

	return 0;
}