#include "bigint4.hpp"
#include <sstream>

// ---- helpers ------------

void bigint::normalize() {
    unsigned int i = 0; 
    
    while (i < val.size() -  1 && val[i] == '0')
        i++;
    val.erase(0, i);
}
 
int bigint::compare(const bigint& other) const {
    if (val.size() > other.val.size())
        return 1;
    if (val.size() < other.val.size())
        return -1;
    if (val > other.val)
        return 1;
    if (val < other.val)
        return -1;
    return 0;
}

std::ostream& operator<<(std::ostream& os, const bigint& obj) {
    return os << obj.get_val();
}

bigint operator+(const bigint& lhs, const bigint& rhs) {
    bigint res(lhs);
    res += rhs;
    return res;
}

//  ---------- end helpers ------------

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
    std::string result;
    std::string v2 = other.val;
    unsigned int size1 = val.size();
    unsigned int size2 = v2.size();
    int carry = 0;

    while (carry > 0 || size1 > 0 || size2 > 0) {
        int sum = carry;
        if (size1 > 0)
            sum += val[--size1] - '0';
        if (size2 > 0)
            sum += v2[--size2] - '0';
        result.insert(result.begin(), (sum % 10) + '0');
        carry = sum / 10;
    }
    val = result;
    normalize();
    return *this;
}

bigint& bigint::operator++() {
    *this = *this + bigint(1);
    return *this;
}
    
bigint bigint::operator++(int) {
    bigint temp(*this);
    ++(*this);
    return temp;
}

//local helper
static unsigned int to_uint(std::string str) {
    unsigned int num = 0;
    for (unsigned int i = 0; i < str.size(); i++)
        num = num * 10 + (str[i] - '0');
    return num;
}

// 42 << 3 == 42000
bigint bigint::operator<<(const bigint& other) const {
    unsigned int shift;
    bigint res(*this);

    if (val == "0" || other.val == "0")
        return *this;
    shift = to_uint(other.val);
    res.val.append(shift, '0');
    return res;
}
    
bigint& bigint::operator<<=(const bigint& other) {
    *this = * this << other;
    return *this;
}

//1337 >> 2 == 13
bigint bigint::operator>>(const bigint& other) const {
    unsigned int shift = to_uint(other.val);
    bigint res(*this);

    if (res.val == "0" || shift == 0)
        return res;
    
    if (res.val.size() - 1 < shift)
        res.val = "0";
    else
        res.val.erase(res.val.size() - shift);
        // 1234 >> 3 = (4 - 3) = 1: erase from i=1
    return res;
}

bigint& bigint::operator>>=(const bigint& other) {
    *this = *this >> other;
    return *this;
}

bool bigint::operator>(const bigint& other) const {
    return (compare(other) > 0);
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
