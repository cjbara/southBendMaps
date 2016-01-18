#include <string>

class side {
public:
	side(bool o, std::string &name){
		parity = o;
		street = name;
	}
	bool operator==(const side &s) const {
		return s.parity == parity && s.street == street;
	}
	
	bool parity; 
	std::string street;

};

namespace std {

template<>
struct hash<side> {
	std::size_t operator()( const side& S) const {
		using std::hash;
		using std::string;
		using std::size_t;

		return (std::hash<string>()(S.street) ^ S.parity);
	}
};

}
