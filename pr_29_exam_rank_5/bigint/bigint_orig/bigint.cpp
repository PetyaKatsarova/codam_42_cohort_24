#include "bigint.hpp"
#include <sstream>

bigint::bigint() : value("0") {}

bigint::bigint(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	value = ss.str();
}

bigint::bigint(const bigint& other)
{
	value = other.value;
}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		value = other.value;
	return *this;
}

void bigint::removeLeadingZeros()
{
	while (value.size() > 1 && value[0] == '0')
		value.erase(0, 1);
}

bigint bigint::operator+(const bigint& other) const
{
	std::string a = value;
	std::string b = other.value;
	std::string result;

	int i = a.size() - 1;
	int j = b.size() - 1;
	int carry = 0;

	while (i >= 0 || j >= 0 || carry)
	{
		int sum = carry;

		if (i >= 0)
			sum += a[i--] - '0';

		if (j >= 0)
			sum += b[j--] - '0';

		result.insert(result.begin(), (sum % 10) + '0');
		carry = sum / 10;
	}

	bigint res;
	res.value = result;
	return res;
}

bigint bigint::operator+(unsigned int n) const
{
	return *this + bigint(n);
}

bigint& bigint::operator+=(const bigint& other)
{
	*this = *this + other;
	return *this;
}

bigint& bigint::operator++()
{
	*this += bigint(1);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint tmp(*this);
	++(*this);
	return tmp;
}

bigint bigint::operator<<(unsigned int shift) const
{
	bigint res(*this);

	if (res.value != "0")
		res.value.append(shift, '0');

	return res;
}

bigint& bigint::operator<<=(unsigned int shift)
{
	*this = *this << shift;
	return *this;
}

bigint bigint::operator>>(const bigint& shift) const
{
	unsigned int s = 0;

	for (size_t i = 0; i < shift.value.size(); i++)
		s = s * 10 + (shift.value[i] - '0');

	bigint res(*this);

	if (s >= res.value.size())
		res.value = "0";
	else
		res.value.erase(res.value.size() - s);

	res.removeLeadingZeros();
	return res;
}

bigint& bigint::operator>>=(const bigint& shift)
{
	*this = *this >> shift;
	return *this;
}

bool bigint::operator<(const bigint& other) const
{
	if (value.size() != other.value.size())
		return value.size() < other.value.size();
	return value < other.value;
}

bool bigint::operator>(const bigint& other) const
{
	return other < *this;
}

bool bigint::operator<=(const bigint& other) const
{
	return !(*this > other);
}

bool bigint::operator>=(const bigint& other) const
{
	return !(*this < other);
}

bool bigint::operator==(const bigint& other) const
{
	return value == other.value;
}

bool bigint::operator!=(const bigint& other) const
{
	return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const bigint& n)
{
	os << n.value;
	return os;
}