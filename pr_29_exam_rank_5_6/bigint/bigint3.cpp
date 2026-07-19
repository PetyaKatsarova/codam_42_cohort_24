#include "bigint3.hpp"
#include <sstream>

// ------- helpers ----------------
int bigint::compare(const bigint& other) const {
    if (val.size() > other.val.size())
        return 1;
    if (val.size() < other.val.size())
        return -1;
    if (val >  other.val)
        return 1;
    if (val <  other.val)
        return -1;
    return 0;
}
        
void bigint::normalize() {
    int i = 0;
    while (val.size() - 1 > 0 && val[i] == '0')
        i++; // -1 is to leave first 0!
    if (val.size() > 1)
        val.erase(0, i);
}

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
    return os << obj.get_val();
}

bigint operator+(const bigint& lhs, const bigint& rhs) {
    bigint temp(lhs);
    temp += rhs;
    return temp;
}

// ----------- end helpers -----------
    
bigint::bigint() : val("0") {}

bigint::bigint(unsigned int n) {
    std::stringstream ss;
    ss << n;
    val = ss.str();
}

bigint::bigint(const bigint& other) : val(other.val) {}

bigint& bigint::operator=(const bigint& other) {
    if (this != &other)
        val = other.val;
    return *this;
}

bigint::~bigint() {}

std::string bigint::get_val() const { return val; }

bigint& bigint::operator+=(const bigint& other) {
    int carry = 0;
    unsigned int v2_size = other.val.size();
    unsigned int v1_size = val.size();
    std::string result;
    std::string v1 = val;
    std::string v2 = other.val;

    while (carry || v1_size > 0 || v2_size > 0) {
        int sum = carry;
        if (v1_size > 0)
            sum += v1[--v1_size] - '0';
        if (v2_size > 0)
            sum += v2[--v2_size] - '0';
        result.insert(result.begin(), (sum % 10) + '0');
        carry = sum / 10;            
    }
    val = result;
    normalize();
    return *this;
}

bigint& bigint::operator++() {
    *this += bigint(1);
    return *this;
}

bigint bigint::operator++(int) {
    bigint temp(*this);
    ++(*this);
    return temp;
}

// 42 << 3 == 42000
bigint bigint::operator<<(unsigned int shift) const {
    bigint temp(*this);

    if (temp.val == "0" || shift == 0)
        return temp;
    temp.val.append(shift, '0');
    return temp;
}
    
bigint& bigint::operator<<=(unsigned int shift) {
    *this = *this << shift;
    return *this;
}

// 1337 >> 2 == 13
bigint bigint::operator>>(const bigint& other) const {
    bigint temp(*this);
    unsigned int shift = 0;

    if (temp.val == "0")
        return temp;
    for (unsigned int i = 0; i < other.val.size(); i++)
        shift = shift * 10 + (other.val[i] - '0');
    if (shift >= temp.val.size())
        temp.val = "0";
    else
        temp.val.erase(temp.val.size() - shift);
    return temp;    
}
    
bigint& bigint::operator>>=(const bigint& other) {
    *this = *this >> other;
    return *this;
}

bool bigint::operator>(const bigint& other) const {
    return compare(other) > 0;
}

bool bigint::operator<(const bigint& other) const {
    return (compare(other) < 0);
}

bool bigint::operator>=(const bigint& other) const {
    return (compare(other) >= 0);
}

bool bigint::operator<=(const bigint& other) const {
    return (compare(other) <= 0);
}

bool bigint::operator==(const bigint& other) const {
    return (compare(other) == 0);
}

bool bigint::operator!=(const bigint& other) const {
    return (compare(other) != 0);
}