#ifndef BITCOIN_EXCHANGE_HEADER
#define BITCOIN_EXCHANGE_HEADER

#include <map>
#include <string>

class BitcoinExchange {
    std::map<std::string, float> _db;

	bool 		initDateValidate(const std::string& dateStr) const;
    bool 		isValidDate(const std::string& dateStr) const;
	bool 		isDotorDigit(const std::string& strPrice) const;
    bool		isValidPrice(const std::string& strPrice) const;
    static bool	openFile(std::ifstream& file, const std::string& filename); // because doesnt use member var
	std::string	getClosestDate(std::ifstream& dbFileStream, std::string& date) const;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        BitcoinExchange& operator=(const BitcoinExchange& other);

		bool validateLineInput(const std::string& filename) const;
        void printResult(const std::string& filename, const std::string& filename2) const;
};

#endif