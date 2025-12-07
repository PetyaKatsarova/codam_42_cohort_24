#ifndef BITCOIN_EXCHANGE_HEADER
#define BITCOIN_EXCHANGE_HEADER

class BitcoinExchange {

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        ~BitcoinExchange();

        BitcoinExchange& operator=(const BitcoinExchange& other);
}

#endif