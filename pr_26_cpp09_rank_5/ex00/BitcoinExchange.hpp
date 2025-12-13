#ifndef BITCOIN_EXCHANGE_HEADER
#define BITCOIN_EXCHANGE_HEADER

#include <map>
#include <string>

class BitcoinExchange {
    std::map<std::string, float> _db;

	bool initDateValidate(const std::string& dateStr) const;
    bool isValidDate(const std::string& dateStr) const;
	bool isDotorDigit(const std::string& strPrice) const;
    bool isValidPrice(const std::string& strPrice) const;
    // float getRate(cosnt std::string& date) const;
    static bool openFile(std::ifstream& file, const std::string& filename); // because doesnt use member var

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        BitcoinExchange& operator=(const BitcoinExchange& other);

		bool validateLineInput(const std::string& filename) const;
        //void loadDb(const std::string& filename);
        void processInput(const std::string& filename) const;
};

#endif