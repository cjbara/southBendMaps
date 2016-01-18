#include "graph.hpp"
#include <cmath>
#include <algorithm>
using namespace std;

node::node(){

}

node::node(int current, int from, float dist){
	currentNode = current;
	fromNode = from;
	distance = dist;
}

bool node::operator<(const node &other) const {
	return distance > other.distance;
}

void graph::addEdge(int start, int end, float e, string s){
	edges[start].insert(end);
	edges[end].insert(start);
	
	edgeLen[start][end] = e;
	edgeLen[end][start] = e;

	edgeName[start][end] = s;
	edgeName[end][start] = s;
}

float graph::getDist(int node1, int node2){
	return edgeLen[node1][node2];
}
	
string graph::getStreet(int node1, int node2){
	return edgeName[node1][node2];
}
	
bool graph::dijkstra(int su, int sv, float spos, int tu, int tv, float tpos, float &distance, vector<pair<string, float>> &steps) {
	//Implement Dijkstra's Algorithm on the member g
	steps.clear();
	//check if they are on the same street
	if(su == tu && sv == tv){ //on same street, return distance between them
		distance = abs(spos - tpos);
		steps.push_back(make_pair(getStreet(su, sv), distance));
		return true;
	}
	priority_queue<node> frontier;
	map<int, node> marked;
	node n1(su, sv, spos);
	frontier.push(n1);
	if(sv != -1){
		node n2(sv, su, getDist(su, sv) - spos);
		frontier.push(n2);
	}
	while(frontier.size() > 0) {
		node u = frontier.top();
		frontier.pop();
		if(marked.count(u.currentNode) == 0){
			marked.insert(make_pair(u.currentNode, u));
			if(tv == -1){
				if(u.currentNode == tu){
					distance = u.distance;
					return true;
				}
			} else {
				if(u.currentNode == tu){
					distance = u.distance + tpos;
					route(marked, steps, u, su, sv, spos, tu, tv, tpos);
					return true;
				} else if(u.currentNode == tv){
					distance = u.distance + getDist(tu, tv) - tpos;
					route(marked, steps, u, su, sv, spos, tu, tv, tpos);
					return true;
				}
			}
			//traverse the node's edges
			set<int>::iterator it;
			for(it=edges[u.currentNode].begin(); it != edges[u.currentNode].end(); ++it){
				//if it's not already in the marked
				if(marked.count(*it) == 0){
					int n1=*it, n2=u.currentNode;
					node v(n1, n2, getDist(n2, n1) + u.distance);
					frontier.push(v);
				}
			}
		}			
	}
	return false;
}

void graph::route(map<int, node> &marked, vector<pair<string, float>> &steps, node &u, int su, int sv, float spos, int tu, int tv, float tpos){
	//construct the route starting from the last marked node u
	int current = u.currentNode;
	int prev = u.fromNode;
	node n;
	//initialize steps to prevent a segfault in the while loop
	steps.push_back(make_pair(getStreet(current, prev), getDist(current, prev)));
	current = prev;
	n = marked[current];
	prev = n.fromNode;

	//add each segment to the directions (steps)
	while(!(prev == su && current == sv) && !(prev == sv && current == su)) {
		if(getStreet(current, prev) == steps.back().first){
			steps.back().second += getDist(current, prev);
		} else {
			steps.push_back(make_pair(getStreet(current, prev), getDist(current, prev)));
		}
		current = prev;
		n = marked[current];
		prev = n.fromNode;
	}

	//This accounts for the first segment from the starting point until node su or sv
	if(prev == su){
		if(getStreet(current, prev) == steps.back().first){
			steps.back().second += (getDist(current, prev) - spos);
		} else {
			steps.push_back(make_pair(getStreet(current, prev), getDist(current, prev) - spos));
		}
	} else { 
		if(getStreet(current, prev) == steps.back().first){
			steps.back().second += spos;
		} else {
			steps.push_back(make_pair(getStreet(current, prev), spos));
		}
	}
	
	//since each node just kept the previous node, we must
	//reverse the order of the vector to get correct driving instructions
	reverse(steps.begin(), steps.end());

	//This accounts for the last segment between tu and tv
	if(u.currentNode == tu){
		if(getStreet(tu, tv) == getStreet(u.currentNode, u.fromNode)){
			steps.back().second += tpos;
		} else {
			steps.push_back(make_pair(getStreet(tu, tv), tpos));
		}
	} else {
		if(getStreet(tu, tv) == getStreet(u.currentNode, u.fromNode)){
			steps.back().second += (getDist(tu, tv) - tpos);
		} else {
			steps.push_back(make_pair(getStreet(tu, tv), getDist(tu,tv) - tpos));
		}
	}

}
