#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream> // ifstream: input means not copyable only pass by &
#include <sstream>
#include <string>
#include <ctime> // std::tm tm {} struct date/time
#include <cctype>  // for std::isdigit()

BitcoinExchange::BitcoinExchange(const std::string& filename) {
    loadDb(filename); // exception propagate to main
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) {}

BitcoinExchange::~BitcoinExchange() {
   // std::cout << "destruction\n"; // std::map destructor frees/manages mem
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
void BitcoinExchange::openFile(std::ifstream& file, const std::string& filename) {
    file.open(filename);
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file");
}

// assume all input in filename.csv is valid(data,float)
// Dynamic memory allocated with new or by containers
void BitcoinExchange::loadDb(const std::string& filename) {
	std::ifstream	inputFile;
	openFile(inputFile, filename); // propage exception to catch in main

	std::string		line;
	std::getline(inputFile, line); // skip header

	while (std::getline(inputFile, line)) {
		if (line.empty()) continue;

		size_t pos = line.find(',');
		if (pos == std::string::npos) continue;

		std::string date = line.substr(0, pos);
		float val = std::stof(line.substr(pos + 1));
		_db[date] = val; // heap: std::map manages heap internally
	}
	//inputFile.close(); no need, destructor does it
}

// check if string is all digits and pos 4 && 7 == '-'
bool BitcoinExchange::initDateValidate(const std::string& dateStr) const {
		std::string msg = "Error: invalid format date: yyyy-mm-dd\n";

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
// std::stoi can throw exception:invalid_argument, out_of_range
bool BitcoinExchange::isValidDate(const std::string& dateStr) const {
	if (!initDateValidate(dateStr))
		return false;

	try {
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

		std::time_t now = std::time(nullptr);
		if (year < 2009 || timestamp > now) {
			return (std::cerr << "Error: date out of range\n", false);
		}
		return true;
	} catch(const std::exception&) {
		return (std::cerr << "Error: bad input => " << dateStr << "\n", false);
	}
}

bool BitcoinExchange::isValidFloat(const std::string& strValue) const {
	if (strValue.empty()) {
		return (std::cerr << "Error: empty value.\n", false);
	}
	try {
		size_t pos = 0;
		float val = std::stof(strValue, &pos); // pos should be == str.len if valid float
		// check if entire str was consumed, no trailing garbage
		if (pos != strValue.length()) {
			return (std::cerr << "Error: bad input => " << strValue << "\n", false);
		}
		if (val < 0)
			return (std::cerr << "Error: not a positive number.\n", false);
        if (val > 1000)
            return (std::cerr << "Error: too large a number.\n", false);
        return true;
	} catch(const std::invalid_argument&) {
		return (std::cerr << "Error: bad input => " << strValue << "\n", false);
	} catch(const std::out_of_range&) {
		return (std::cerr << "Error: too large a number.\n", false);
	}
}

// validate given externally .csv file line by line: format: 2012-01-11 | 2.22
bool BitcoinExchange::validateLineInput(const std::string& line) const {
	if (line.empty()) return (std::cout << "Empty line\n", false);
	if (line.length() < 14) {
		std::cerr << "Error: bad input => " << line << "\n";
		return (false);
	}
	std::string dateStr = line.substr(0, 10);
	if (line[10] != ' ' || line[11] != '|' || line[12] != ' ') {
		std::cerr << "Error: bad input => " << line << "\n";
		return (false);
	}
	if (!isValidDate(dateStr))
		return (false);
	std::string strValue = line.substr(13); // till the end all
	// trim end white spaces
	size_t trimmedEnd = strValue.find_last_not_of(" \t\n\r");
	if (trimmedEnd != std::string::npos)
		strValue = strValue.substr(0, trimmedEnd + 1);

	if (!BitcoinExchange::isValidFloat(strValue))
		return (false);
	return true;
}

float BitcoinExchange::getClosestDatePrice(const std::string& date) const {
	if (_db.empty()) {
        std::cerr << "Error: database is empty\n";
        return -1;
    }
    
	std::map<std::string, float>::const_iterator it = _db.lower_bound(date);
	if (it != _db.end() && it->first == date) {
		return it->second; // return val
	}
	if (it == _db.begin()) {
		std::cerr << "Error: no data available for this date\n";
		return -1; // no == or lower match or???? todo
	}
	--it; // move 1 back to get closest lower/not bigger
	return it->second;
}

/*
display on the standard output the result of the value multiplied
by the exchange rate according to the date indicated in your database.
If the date used in the input does not exist in your DB then you
must use the closest date contained in your DB. Be careful to use the
lower date and not the upper one.
*/

 void BitcoinExchange::printResult(const std::string& filename) const {
    std::ifstream inputFile;
	openFile(inputFile, filename); // let exception propagate

	std::string line;
	std::getline(inputFile, line); // skip header

	while (std::getline(inputFile, line)) {
		if (validateLineInput(line)) {
			std::string date = line.substr(0, 10);
			std::string valueStr = line.substr(13);

			size_t trimmedEnd = valueStr.find_last_not_of(" \t\n\r");
			if (trimmedEnd != std::string::npos)
				valueStr = valueStr.substr(0, trimmedEnd + 1);
			
			float inputVal = std::stof(valueStr);
			float exchangeRate = getClosestDatePrice(date);
			if (exchangeRate >= 0)
				std::cout << date << " => " << inputVal << " = " << inputVal * exchangeRate << "\n";
		}
	}
 }