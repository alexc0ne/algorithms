#include "BigInt.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>


void BigInt::updateIfNull()
{
    for (const auto & item : v_)
        if (item != 0)
            return;

    sign_ = Sign::NON_NEGATIVE;
    v_ = {0};
}


BigInt::BigInt() : sign_(Sign::NON_NEGATIVE), v_({0}) {}
BigInt::BigInt(const BigInt & other) : sign_(other.sign_), v_(other.v_) {}


BigInt::BigInt(const std::string & s)
{
    // s is supposed to be here a valid string of type: "-yx..x" or "yx..x"
    // where y is in [1-9]
    //       x is in [0-9]
    // todo: --> parse an s for validity
    // todo: --> after parsing the string create separately an object in a (?) factory method

    auto s_rend = s.rend();
    if (s[0] == '-')
    {
        sign_ = Sign::NEGATIVE;
        --s_rend;
    }
    else
        sign_ = Sign::NON_NEGATIVE;

    v_.reserve(s_rend - s.rbegin());
    for (auto it = s.rbegin(); it != s_rend; ++it)
        v_.push_back(*it - '0');
}


BigInt::BigInt(int64_t i)
{
    sign_ = i >= 0 ? Sign::NON_NEGATIVE : Sign::NEGATIVE;
    i = std::abs(i);

    do
    {
        v_.push_back(i % 10);
        i /= 10;
    }
    while (i != 0);
}


std::string BigInt::toString() const
{
    std::stringstream ss;

    if (this->sign_ == Sign::NEGATIVE)
        ss << "-";
    for (auto it = v_.rbegin(); it != v_.rend(); ++it)
        ss << *it;

    return ss.str();
}

size_t BigInt::size() const
{
    return v_.size();
}


bool BigInt::operator == (const BigInt & other)
{
    if (this->sign_ == other.sign_)
        if (this->size() == other.size())
        {
            for (size_t i = 0; i < size(); ++i)
                if (v_[i] != other.v_[i])
                    return false;

            return true;
        }

    return false;
}


const BigInt & BigInt::operator += (const BigInt &)
{
    // todo
    return *this;
}

BigInt BigInt::operator + (const BigInt & other)
{
    BigInt res(*this);

    res += other;
    res.updateIfNull();

    return res;
}

std::ostream & operator << (std::ostream & out, const BigInt & bi)
{
    out << bi.toString();
    return out;
}
