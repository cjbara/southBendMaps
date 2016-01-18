#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

#include "street_map.hpp"

using namespace std;

street_map::street_map (const string &filename) {
	// Fill in your code here.
	ifstream file;
	file.open(filename);

	//input all sides and segments into the unordered map
	string streetName;
	int parity;
	int rangeStart, rangeEnd;
	int startNode, endNode;
	float length;
	string NorR, URL;
	file >> NorR >> ws;
	while(!file.eof()){
		if(NorR == "N:") {
			getline(file, streetName);
		} else if(NorR == "R:") {
			file >> parity >> rangeStart >> rangeEnd >> startNode >> endNode >> length >> ws;
			getline(file, URL);

			//add these values to the graph
			g.addEdge(startNode, endNode, length, streetName);

		//PG4 and part 1
			//create new segment and side to use
			side s(parity, streetName);
			segment seg(rangeStart, rangeEnd, startNode, endNode, length, URL);

			//add these two to the map using push back for the vector
			streets[s].push_back(seg);

		} else if(NorR == "E:") {
			file >> startNode >> endNode >> length >> ws;
			getline(file, URL);

			//add these values to the graph
			g.addEdge(startNode, endNode, length, streetName);

		//PG4 and part 1
			//create new segment and side to use
			side s(parity, streetName);
			segment seg(rangeStart, rangeEnd, startNode, endNode, length, URL);

			//add these two to the data structure using push back for the vector
			streets[s].push_back(seg);
		}
		file >> NorR >> ws;
	}

	file.close();
}

bool street_map::geocode(const string &address, int &u, int &v, float &pos) {
	//parse the address into a specific stream
	stringstream ss;
	ss.str(address);

	//stores address into this variable
	string addr;

	//stores number into this variable
	int number;
	string street;
	ss >> number;
	getline(ss, addr);
	addr.erase(0,1);

	//find which side the address is on and store it in s
	bool flag = false;

	if(number % 2){ //on odd side of street
		flag = true;
	}
	side s(flag, addr);

	//check all of the values in streets[s], which is a vector
	flag = false;

	vector<segment>::iterator it = streets[s].begin();
	for(; it != streets[s].end(); ++it){
		if(it->contains(number)) {
			//if found, make the flag true, and sotre the url into url variable
			flag = true;
			u = it->startNode;
			v = it->endNode;
			pos = (it->length) * (number - it->startHouse) / (it->endHouse - it->startHouse +2);
		}
	}

	return flag;

}

bool street_map::route3(int source, int target, float &distance) {
	//Implement Dijkstra's Algorithm on the member g
	return route4(source, -1, 0, target, -1, 0, distance);
}

bool street_map::route4(int su, int sv, float spos, int tu, int tv, float tpos, float &distance) {
	vector<pair<string, float>> steps;
	return g.dijkstra(su, sv, spos, tu, tv, tpos, distance, steps);
}

bool street_map::route(int su, int sv, float spos, int tu, int tv, float tpos, vector<pair<string, float>> &steps) {
	float distance;
	return g.dijkstra(su, sv, spos, tu, tv, tpos, distance, steps);
}

