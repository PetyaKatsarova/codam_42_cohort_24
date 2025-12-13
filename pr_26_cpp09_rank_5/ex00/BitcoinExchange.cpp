#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream> // ifstream: input means not copyable only pass by &
#include <sstream>
#include <string>
#include <ctime>
#include <cctype>  // for std::isdigit()

BitcoinExchange::BitcoinExchange() {
    std::cout << "default constr\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) { std::cout << "Cpy constr\n"; }

BitcoinExchange::~BitcoinExchange() {
    std::cout << "destruction\n"; // std::map destructor frees/manages mem
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _db = other._db; // std::map assignment(automatic deep cpy)
    }
    return *this;
}

/* stream types:
std::ifstream - input (read) from file
std::ofstream - output (write) to file
std::fstream - both read and write

Once you read a file stream, the position is at the end. You'd need to reset it each time.
*/
bool BitcoinExchange::openFile(std::ifstream& file, const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Err: could not open file\n";
        return false;
    }
    return true;
}

// check if string is all digits and pos 4 && 7 == '-'
bool BitcoinExchange::initDateValidate(const std::string& dateStr) const {
		std::string msg = "Ups, invalid format date: yyyy-mm-dd\n";

	if (dateStr.length() != 10 || dateStr[4] != '-' || dateStr[7] != '-')
		return (std::cerr << msg, false);

	for (size_t i = 0; i < 10; i++) {
		if (i == 4 || i == 7) continue;
		if (!std::isdigit(dateStr[i])) {
			return (std::cerr << msg, false);
		}
	}
	return true;
}

// expected date format: 2022-03-16
bool BitcoinExchange::isValidDate(const std::string& dateStr) const {
	if (!BitcoinExchange::initDateValidate(dateStr))
		return false;

	int year  = std::stoi(dateStr.substr(0, 4));
	int month = std::stoi(dateStr.substr(5, 2));
	int day   = std::stoi(dateStr.substr(8, 2));

	std::tm tm = {};
    tm.tm_year = year - 1900;  // years is since 1900
    tm.tm_mon = month - 1;     // months since January (0-11)
    tm.tm_mday = day;
    
    // mktime validates and normalizes the date
    std::time_t timestamp = std::mktime(&tm);
    if (timestamp == -1)
        return (std::cerr << "Error: bad input => " << dateStr << "\n", false);
    
    // Check if date was normalized (invalid dates get adjusted)
    if (tm.tm_year != year - 1900 || tm.tm_mon != month - 1 || tm.tm_mday != day)
        return (std::cerr << "Error: bad input => " << dateStr << "\n", false);
    
    // Check Bitcoin era + not future
    std::time_t now = std::time(nullptr);
    if (year < 2009 || timestamp > now) {
        return (std::cerr << "Error: date out of range\n", false);
	}
	return true;
}

// a float or a positive integer, between 0 and 1000
// 2025-11-29,47115.93
/**
int x = 42;             -> 4 bytes, whole numbers: -2,147,483,648 to 2,147,483,647
float f = 3.14;         -> 4 bytes, decimals: ±3.4e38 (7 digits precision)
double d = 3.14159265;  -> 8 bytes, decimals: ±1.7e308 (15 digits precision)
 */
bool BitcoinExchange::isDotorDigit(const std::string& strPrice) const {
	 if (strPrice.empty())
        return (std::cerr << "Error: empty value.\n", false);
    
	bool isDot		= false;
	bool isDigit	= false;
	size_t start	= 0;

	if (strPrice[0] == '-')
		start = 1; // they want for -num diff err msg
	for (size_t i = start; i < strPrice.length(); i++) {
		if (std::isdigit(strPrice[i])) {
			isDigit = true;
		} else if (strPrice[i] == '.') {
			if (isDot) {
				return (std::cerr << "Error: bad input => " << strPrice << "\n", false);
			}
			isDot = true;
		} else 
			return (std::cerr << "Error: bad input => " << strPrice << "\n", false);
	}
	if (!isDigit) {
		return (std::cerr << "Error: bad input => " << strPrice << "\n", false);
	}

	return true;
}

bool BitcoinExchange::isValidPrice(const std::string& strPrice) const {
	if (!BitcoinExchange::isDotorDigit(strPrice))
		return false;
	
	try {
		float val = std::stof(strPrice);
		if (val < 0)
			return (std::cerr << "Error: not a positive number.\n", false);
        if (val > 1000)
            return (std::cerr << "Error: too large a number.\n", false);
        return true;
	} catch(...) {
		return (std::cerr << "Error: bad input => " << strPrice << "\n", false);
	}
}

bool BitcoinExchange::validateLineInput(const std::string& line) const {
	if (line.empty()) return (std::cout << "Empty line\n", false);
	if (line.length() < 14) {
		std::cout << "Missing space or | between date and price\n";
		return (false);
	}
	std::string dateStr = line.substr(0, 10);
	if (line[10] != ' ' || line[11] != '|' || line[12] != ' ') {
		std::cerr << "Missing space or | between date and price\n";
		return (false);
	}
	if (!BitcoinExchange::isValidDate(dateStr))
		return (false);
	std::string priceStr = line.substr(13); // till the end all
	// trim end white spaces
	size_t trimmedEnd = priceStr.find_last_not_of(" \t\n\r");
	if (trimmedEnd != std::string::npos)
		priceStr = priceStr.substr(0, trimmedEnd + 1);

	if (!BitcoinExchange::isValidPrice(priceStr))
		return (false);
	return true;
}

/**
 * doesnt protect for invalid inputs(if wrong date format, etc)
 */
//void BitcoinExchange::loadDb(const std::string& filename) {
//    std::ifstream file;
//    if (!openFile(file, filename)) return; // err msg in func
	
//    std::string line;
//    std::getline(file, line); // skip header(title): data, exchange_rate
//    while (std::getline(file, line)) {
//        size_t pos = line.find(',');
//        if (pos == std::string::npos) continue; // it was already validated

//        std::string date = line.substr(0, pos);
//        float rate = std::stof(line.substr(pos+1));
//        _db[date] = rate;
//        // temp for debug:
//        std::cout << "_db[" << date << "]=" << rate << std::endl;
//    }
//    file.close();
//}

 void BitcoinExchange::processInput(const std::string& filename) const {
    std::ifstream file;
	if (!openFile(file, filename)) return;

	std::string line;
	std::getline(file, line); // skip header
	while (std::getline(file, line)) {
	if (BitcoinExchange::validateLineInput(line))
		std::cout << line << "\n";
	}
	file.close();
 }