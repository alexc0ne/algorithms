#include "BigInt.h"
#include <string>
#include <algorithm>
#include <sstream>



BigInt::BigInt() : sign_(Sign::NON_NEGATIVE), v_({0}) {}
BigInt::BigInt(const BigInt & other) : sign_(other.sign_), v_(other.v_) {}


BigInt::BigInt(const std::string & s)
{
    // todo: --> check if:
    //                     every char is between 0 and 9 except maybe s[0]
    //                     len > 0
    //
    // later can be implemented using factory-method

    sign_ = (s[0] == '-') ? Sign::NEGATIVE : Sign::NON_NEGATIVE;

    // todo: --> fix if s appears to be a negative number

    v_.reserve(s.size());
    for (auto it = s.rbegin(); it != s.rend(); ++it) v_.push_back(*it - '0');
}


BigInt::BigInt(int64_t i)
{
    sign_ = i >= 0 ? Sign::NON_NEGATIVE : Sign::NEGATIVE;

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
    if (this->sign_ == Sign::NEGATIVE) ss << "-";
    for (auto it = v_.rbegin(); it != v_.rend(); ++it) ss << *it;

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