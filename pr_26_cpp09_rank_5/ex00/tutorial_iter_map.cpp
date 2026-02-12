#include <iostream>
#include <map>

/**
 *  RAII = Resource Acquisition Is Initialization
	C++ programming idiom where resource lifetime is tied to object lifetime.
	EXAMPLE: dont need to close file, distructor wil
 */

// in the dbFile where we get the date: it is in ascending order: going down the list:
// will always have a bigger date
/*
iter map: first; key, second: val
for (std::map<std::string, float>::const_iterator it = _db.begin(); 
     it != _db.end(); ++it) {
    std::string dbDate = it->first;   // The key (date)
    float price = it->second;          // The value (price)
    ...
}
*/

// O(n) slower than with db.lower_bound(date) O(log n)
std::string getClosestDate(std::string date, std::map<std::string, float>& db) {
	std::string closestDate = "";
	
	for (std::map<std::string, float>::const_iterator it = db.begin(); it != db.end(); ++it) {
		if (it->first == date)
			return it->first;
		if (it->first < date)
			closestDate = it->first; // keep closest smaller date: because maps are sorted
	}
	return closestDate;
}

// more efficient binary search: O(log n)
std::string getClosestDatebond(const std::string& date, std::map<std::string, float>& db) {
    if (db.empty()) { return ""; }
	// find first el >= date(binary search: O(log n))
	std::map<std::string, float>::const_iterator it = db.lower_bound(date);
	if (it != db.end() && it->first == date) {
		return it->first;
	}
	if (it == db.begin()) {
		return ""; // date is the lowest in the list
	}
	// move back 1 to get closest lower date
	--it;
	return it->first;
}

std::string getSameDate(std::string date, std::map<std::string, float>& db) {
	std::string closestDate;
	// date here is the key
	if (db.find(date) != db.end()) {
		return date; 
	} else {
		std::cout << "no == date\n";
	}
	return closestDate; // cpy the str, refernce: no good idea: will dangle after func returns	
}

int main() {
	std::cout << "tra la la....\n";
	std::map<std::string, float> db = {
		{"2009-12-12",0},
		{"2011-01-04",0.3},
		{"2011-01-06",0.3},
		{"2011-01-10",0.33},
		{"2011-01-13",0.42},
		{"2011-01-16",0.4},
		{"2011-01-19",0.35},
		{"2012-03-05",5.04},
		{"2012-03-08",4.99},
		{"2012-03-11",4.98},
		{"2012-03-14",5.45},
		{"2012-03-17",5.4},
		{"2012-03-20",4.95},
		{"2012-03-23",4.81},
		{"2012-01-11", 4.2}
	};
	db.insert(std::make_pair("2011-01-03", 0.32));

	std::cout << "getSameDate('2012-03-20', db) = " << getSameDate("2012-03-20", db) << std::endl;
	std::cout << "getClosestDate('2012-03-16', db) = " << getClosestDate("2012-03-16", db) << std::endl;
	return 0;
}