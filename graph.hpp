#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

class node {
public:
	node();
	node(int current, int from, float dist);
	bool operator<(const node &other) const;

	int currentNode;
	int fromNode;
	float distance = 0;

};

class graph {
public:
	map<int, set<int> > edges;
	map<int, map<int, float> > edgeLen;
	map<int, map<int, string> > edgeName;
	
	void addNode(int n);
	void addEdge(int start, int end, float e, string s);
	float getDist(int node1, int node2);
	string getStreet(int node1, int node2);
	bool dijkstra(int su, int sv, float spos, int tu, int tv, float tpos, float &distance, vector<pair<string, float>> &steps);
	void route(map<int, node> &marked, vector<pair<string, float>> &steps, node &u, int su, int sv, float spos, int tu, int tv, float tpos);

};
