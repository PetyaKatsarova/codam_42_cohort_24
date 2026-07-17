

#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
    private:
        std::string val;

        int compare(const bigint& other) const;
        void normalize();

    public:
        bigint();
        bigint(unsigned int n);
        bigint(const bigint& other);
        bigint& operator=(const bigint& other);
        ~bigint();

        std::string get_val() const;

        bigint& operator+=(const bigint& other);
        bigint& operator++();
        bigint operator++(int);

        bigint operator<<(unsigned int shift) const;
        bigint& operator<<=(unsigned int shift);
        bigint operator>>(const bigint& other) const;
        bigint& operator>>=(const bigint& other);

        bool operator>(const bigint& other) const;
        bool operator<(const bigint& other) const;
        bool operator>=(const bigint& other) const;
        bool operator<=(const bigint& other) const;
        bool operator==(const bigint& other) const;
        bool operator!=(const bigint& other) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& obj);

bigint operator+(const bigint& lhs, const bigint& rhs);

#endif