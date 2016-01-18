#include <string>

#ifndef SEGMENT
#define SEGMENT
//represents a segment of the street
class segment {
public:
	segment(int &s, int &e, int sn, int en, double l, std::string URL){
		startHouse = s;
		endHouse = e;
		startNode = sn;
		endNode = en;
		length = l;
		url = URL;
	}
	
	//check if a number is in a part of a street
	bool contains(int &num){
		return num >= startHouse && num <= endHouse;
	}

	double distanceToHouse(int start, int end, int houseNumber) {
		return 0.0;
	}

	int startHouse;	//beginning number on the segement
	int endHouse;	//ending number on the segment
	int startNode;
	int endNode;
	int node;
	double length;	//length of segment in miles
	std::string url;

};

#endif
