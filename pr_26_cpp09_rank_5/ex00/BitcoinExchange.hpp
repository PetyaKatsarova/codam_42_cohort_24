#ifndef BITCOIN_EXCHANGE_HEADER
#define BITCOIN_EXCHANGE_HEADER

#include <map>
#include <string>

class BitcoinExchange {
    std::map<std::string, float> _db;

    // bool isValidDate(const std::string& date) const;
    // bool isValidVal(const std::string& date) const;
    // float getRate(cosnt std::string& date) const;
    bool openFile(std::ifstream& file, const std::string& filename);

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        BitcoinExchange& operator=(const BitcoinExchange& other);

        void loadDb(const std::string& filename);
        // void processInput(const std::string& filename);
};

#endif