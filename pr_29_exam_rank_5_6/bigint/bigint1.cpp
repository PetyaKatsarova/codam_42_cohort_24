#include "bigint1.hpp"
#include <sstream>
#include <algorithm>

// ------- helpers -----------
std::ostream& operator<<(std::ostream& os, const bigint& obj) {
    return (os << obj.get_val());
}

bigint operator+(const bigint& lhs, const bigint& rhs) {
    bigint temp(lhs);
    temp += rhs;
    return temp;
}

void bigint::normalize() {
    unsigned int i = 0;
    while (val[i] == '0' && val.size() - 1 > i) 
        i++;
    val.erase(0, i); // == val = val.susbstr(i);
}

std::size_t bigint::to_size_t() {
  std::size_t result = 0;
  for (unsigned int i = 0; i < val.size(); i++)
    result = result * 10 + (val[i] - '0');
  return result;
}

int bigint::compare(const bigint& other) const {
  std::string v2 = other.get_val();
  unsigned int v1_size = val.size();
  unsigned int v2_size = v2.size();
  if (v1_size > v2_size)
    return 1;
  if (v1_size < v2_size)
    return -1;
  if (val > v2)
    return 1;
  if (val < v2)
    return 1;
  return 0;
}

    // ----------- end helpers -------------

bigint::bigint() : val("0") {}

bigint::bigint(unsigned int n) : val() {
    std::stringstream ss;
    ss << n;
    val = ss.str();
}

bigint::bigint(const bigint& other) : val(other.val) {}

bigint& bigint::operator=(const bigint& other) {
    if (this != &other) {
        val = other.val;
    }
    return *this;
}

bigint::~bigint() {}

std::string bigint::get_val() const { return val; }

bigint& bigint::operator+=(const bigint& other) {
    std::string v1 = val;
    std::string v2 = other.val;
    std::string result;
    int         v1_size = v1.size();
    int         v2_size= v2.size();
    int         carry = 0;

    if (other.val == "0")
        return *this;
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
bigint bigint::operator<<(unsigned int n) const {
  bigint temp(*this);

  if (n == 0 || temp.val == "0")
    return temp;
  temp.val.append(n, '0');
  return temp;
}

bigint& bigint::operator<<=(unsigned int n) {
  *this = *this << n;
  return *this;
}

// 1337 >> 2 == 13
bigint  bigint::operator>>(const bigint& other) const {
    bigint temp(*this);
    unsigned int shift = 0;

    if (temp.val == "0") return temp;
    // other.val into usigined int
    for (unsigned int i = 0; i < other.val.size(); i++)
        shift = shift * 10 + (other.val[i] - '0');
    if (shift == 0 || shift >= temp.val.size())
      temp.val = "0";
    else {
      temp.val.erase(temp.val.size() - shift);
    }

    return temp;
}
  
bigint& bigint::operator>>=(const bigint& other) {
    *this = *this >> other;
    return *this;
}
 


 bool bigint::operator<(const bigint& other) const {
    return compare(other) < 0;
 }

bool bigint::operator>=(const bigint& other) const {
    return compare(other) >=0;
}

bool bigint::operator<=(const bigint& other) const {
    return compare(other) <=0;
}
     
bool bigint::operator==(const bigint& other) const {
    return compare(other) == 0;
}

bool bigint::operator!=(const bigint& other) const {
    return compare(other) != 0;
}