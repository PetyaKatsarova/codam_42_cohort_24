/**
 Each line in this file must use the following format: "date | value".
• A valid date will always be in the following format: Year-Month-Day.
• A valid value must be either a float or a positive integer, between 0 and 1000.
You must use at least one container in your code to validate this exercise. You should handle possible errors with an appropriate error message.
*/

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

BitcoinExchange::BitcoinExchange() {
    std::cout << "default constr\n";
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _db(other._db) { std::cout << "Cpy constr\n"; }

BitcoinExchange::~BitcoinExchange() {
    std::cout << "destruction\n";
    // no clean up needed: std::map destructor handles it
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        // std::map assignment(automatic deep cpy)
        _db = other._db;
    }
    return *this;
}

bool BitcoinExchange::openFile(std::ifstream& file, const std::string& filename) {
    file.open(filename);
    if (!file.is_open()) {
        std::cerr << "Err: could not open file\n";
        return false;
    }
    return true;
}

/**
 * expected date format: 2022-03-16
 * init std::string 3 ways:
 * // 2. Constructor syntax
std::string msg("Invalid date");

// 3. Uniform initialization (C++11+)
std::string msg{"Invalid date"};
 */
bool BitcoinExchange::isValidDate(const std::string& dateStr) const {
	std::string msg = "Ups, invalid date\n";
	// str.len = 10
	if (dateStr.length() != 10 || dateStr[4] != '-' && dateStr[7] != '-')
		return (std::cerr << msg, false);

	// if str[0] - 3 >= 1970 and < curr.date
	// str[5] && 6 >= 1 <+ 12
	// str[8] && 9 >= 1 <= 31 oh.. and depending on the month: 30, 31, 28, 29.... 

	return true;
}

/**
 * doesnt protect for invalid inputs(if wrong date format, etc)
 */
void BitcoinExchange::loadDb(const std::string& filename) {
    std::ifstream file;
    if (!openFile(file, filename)) return;
    std::string line;
    std::getline(file, line); // skip header(title): data, exchange_rate
    while (std::getline(file, line)) {
        size_t pos = line.find(',');
        if (pos == std::string::npos) continue; // it was already validated

        std::string date = line.substr(0, pos);
        float rate = std::stof(line.substr(pos+1));
        _db[date] = rate;
        // temp for debug:
        std::cout << "_db[" << date << "]=" << rate << std::endl;
    }
    file.close();
}

// void BitcoinExchange::processInput(const std::string* filename) {
//     std::ifstream file;
//     if (!file.is_open()) {
//         std::cerr << "Err: could not open file\n";
//         return ;
//     }
// }