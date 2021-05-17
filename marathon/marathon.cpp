#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_map>
#include <deque>

using namespace std;
#define INPUT  "marathon.inp"
#define OUTPUT "marathon.out"

multimap<char, pair<char, int>> adj;
deque<char> BFS;
unordered_map<char, bool> visited;
map<char, int> dist;
set<char> visit;
string route;
string ans;
int vertexNumber;
int edgeNumber;
int ansSize;
int routeSize;

void addEgde(char s, char e, int d) {
	adj.insert({ s, {e, d} });
	adj.insert({ e, {s, d} });
}

void input() {
	ifstream inputFile;

	inputFile.open(INPUT);
	if (inputFile.is_open()) {
		inputFile >> vertexNumber >> edgeNumber;
		for (int i = 0; i < edgeNumber; i++) {
			char start;
			char end;
			int distance;
			inputFile >> start >> end >> distance;
			addEgde(start, end, distance);
		}
	}
}

void distance_init() {
	multimap<char, pair<char, int>>::iterator it;
	for (it = adj.begin(); it != adj.end(); ++it) {
		dist[it->first] = 100;
	}

	dist['a'] = 0;
}

void distance_calc(char source) {
	auto k = adj.equal_range(source); // a
	BFS.push_back(source);
	int setSize = 0;
	char next = BFS.front();

	while (setSize < vertexNumber) {
		if (visit.find(next) == visit.end()) {
			visit.insert(next);
			k = adj.equal_range(next);
			for (auto n = k.first; n != k.second; ++n) {
				if (visit.find(n->second.first) == visit.end()) {
					BFS.push_back(n->second.first);
				}

				if (dist[n->second.first] > dist[next] + n->second.second) {
					dist[n->second.first] = dist[next] + n->second.second;
				}
			}
		}

		setSize = visit.size();
		if (!BFS.empty()) {
			next = BFS.front();
			BFS.pop_front();
		}
	}

	visit.clear();
}

void DFS(char s, int sum) {
	auto range = adj.equal_range(s);
	route.push_back(s);

	int temp;
	char next;
	routeSize = route.size();
	ansSize = ans.size();
	if (sum + dist[s] <= 42) {
		for (auto neighbor = range.first; neighbor != range.second; ++neighbor) {
			next = neighbor->second.first;
			if (visited[next] == false) {
				temp = sum;
				temp += neighbor->second.second;
				if (next != 'a' && temp < 42) {
					visited[next] = true;
					DFS(next, temp);
				} else if (next == 'a' && temp == 42) {
					if (routeSize > ansSize)
						ans = route;
					else if (routeSize == ansSize && route < ans)
						ans = route;
				}
			}
		}
	}

	route.pop_back();
	visited[s] = false;
	return;
}

void output() {
	ofstream outFile;
	int ansSize = ans.size();

	outFile.open(OUTPUT);
	if (outFile.is_open()) {
		outFile << ansSize << endl;
		for (int i = 0; i < ansSize; i++) {
			outFile << ans[i] << " ";
		}
	}
}

int main(void) {
	input();
	distance_init();
	distance_calc('a');
	DFS('a', 0);
	output();

	return 0;
}