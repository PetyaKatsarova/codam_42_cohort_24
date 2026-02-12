#ifndef BITCOIN_EXCHANGE_HEADER
#define BITCOIN_EXCHANGE_HEADER

#include <map> // unique key(if dup: replaces with last one), auto sorts on key
#include <string>

class BitcoinExchange {
	
		std::map<std::string, float> _db;

		bool 		initDateValidate(const std::string& dateStr) const;
		bool 		isValidDate(const std::string& dateStr) const;
		bool		isValidFloat(const std::string& strValue) const;
		static void	openFile(std::ifstream& file, const std::string& filename); // because doesnt use member var
		float		getClosestDatePrice(const std::string& date) const;
		void		loadDb(const std::string& filename);

    public:
        BitcoinExchange(const std::string& filename);
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        BitcoinExchange& operator=(const BitcoinExchange& other);

		bool 	validateLineInput(const std::string& filename) const;
        void	printResult(const std::string& filename) const;
};

#endif