#include "BigInt.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>



Sign revert(Sign sign)
{
    if (sign == Sign::NON_NEGATIVE) return Sign::NEGATIVE;
    return Sign::NON_NEGATIVE;
}

void BigInt::trimZeros()
{
    auto it = v_.rbegin();
    for ( ; it != v_.rend(); ++it)
    {
        if (*it != 0)
            break;
    }

    size_t diff = v_.rend() - it;

    if (diff != 0)
        v_.resize(diff);
    else
    {
        sign_ = Sign::NON_NEGATIVE;
        v_ = {0};
    }
}


BigInt::BigInt() : sign_(Sign::NON_NEGATIVE), v_({0}) {}
BigInt::BigInt(const BigInt & other) = default;


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


BigInt & BigInt::operator = (const BigInt & other)
{
    if (this != &other)
    {
        sign_ = other.sign_;
        v_ = other.v_;
    }

    return *this;
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


bool BigInt::operator == (const BigInt & other) const
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

bool BigInt::operator != (const BigInt & other) const
{
    return !(*this == other);
}
//===================  operator + and auxiliary methods  ===================================

void BigInt::add(const BigInt & other)
{
    if (other.size() > size())
        v_.resize(other.size(), 0);

    auto this_begin = v_.begin();
    auto other_begin = other.v_.begin();
    for ( ; other_begin != other.v_.end(); ++other_begin, ++this_begin)
    {
        *this_begin += *other_begin;
    }

    int16_t carry = 0;
    for (auto & i : v_)
    {
        i += carry;
        carry = i / 10;
        i %= 10;
    }
    if (carry != 0) v_.push_back(carry);
}

void BigInt::subtract(const BigInt & other)
{
    auto this_begin = v_.begin();
    auto other_begin = other.v_.begin();
    for ( ; other_begin != other.v_.end(); ++other_begin, ++this_begin)
    {
        *this_begin -= *other_begin;
    }

    if (size() > 1)
    {
        for (size_t i = 0; i + 1 < size(); ++i)
        {
            if (v_[i] < 0)
            {
                v_[i] += 10;
                v_[i + 1] -= 1;
            }
        }

        trimZeros();
    }
}

const BigInt & BigInt::operator += (const BigInt & other)
{
    if (sign_ == other.sign_)
    {
        add(other);
        return *this;
    }

    // sign_ != other.sign_
    if (!abs_this_less_abs(other)) subtract(other);
    else
    {
        BigInt tmp {*this};
        *this = other;
        subtract(tmp);
    }

    return *this;
}

BigInt BigInt::operator + (const BigInt & other)
{
    BigInt res(*this);

    res += other;
    res.trimZeros();

    return res;
}

//===================  operator - and auxiliary methods  ===================================

const BigInt & BigInt::operator -= (const BigInt & other)
{
    if (sign_ != other.sign_)
    {
        add(other);
        return *this;
    }

    // sign_ == other.sign_
    if (!abs_this_less_abs(other)) subtract(other);
    else
    {
        BigInt tmp {*this};
        *this = other;
        subtract(tmp);
        sign_ = revert(sign_);
    }

    return *this;
}

BigInt BigInt::operator - (const BigInt & other)
{
    BigInt res(*this);

    res -= other;
    res.trimZeros();

    return res;
}

//===== operator * and auxiliary methods  ========================================================

BigInt BigInt::mul(size_t n) const
{
    BigInt res;

    std::vector<int16_t> zeros(n, 0);
    zeros.insert(zeros.end(), v_.begin(), v_.end());

    res.v_ = zeros;
    return res;
}

BigInt BigInt::div(size_t n) const
{
    if (n >= size())
        return {0};

    BigInt res;
    res.v_ = {v_.begin() + n, v_.end()};

    return res;
}

BigInt BigInt::mod(size_t n) const
{
    if (n > size()) n = size();

    BigInt res;
    res.v_ = {v_.begin(), v_.begin() + n};

    return res;
}

BigInt karatsuba(const BigInt & left, const BigInt & right)
{
    if (left < 129 and right < 129)
        return {
                std::stoi(left.toString()) *
                std::stoi(right.toString())
    };

    // n = max(len(left), len(right))
    // x = 10^(n/2) * a + b
    // a = x / 10^(n/2)
    // b = x % 10^(n/2)

    // left * right = 10^n * (a1 * a2) + 10^(n/2) * (a1 * b2 + a2 * b2) + b1 * b2
    // left * right = 10^n * p + 10^(n/2) * (r - p - q) + q

    // p = a1 * a2
    // r = (a1 + b1) * (a2 + b2)
    // q = b1 * b2

    size_t n = std::max(left.size(), right.size());
    if (n % 2 == 1) ++n;
    size_t n_halved = n/2;

    BigInt a1 = left.div(n_halved);
    BigInt b1 = left.mod(n_halved);

    BigInt a2 = right.div(n_halved);
    BigInt b2 = right.mod(n_halved);

    BigInt p = karatsuba(a1, a2);
    BigInt r = karatsuba(a1 + b1, a2 + b2);
    BigInt q = karatsuba(b1, b2);

    return p.mul(n) + (r - p - q).mul(n_halved) + q;
}


const BigInt & BigInt::operator *= (const BigInt & other)
{
    if (*this == 0 or other == 0)
    {
        *this = 0;
        return *this;
    }

    Sign sign = (sign_ == other.sign_) ? Sign::NON_NEGATIVE : Sign::NEGATIVE;

    *this = karatsuba(this->abs(), other.abs());

    sign_ = sign;

    return *this;
}

BigInt BigInt::operator * (const BigInt & other)
{
    BigInt res(*this);

    res *= other;
    res.trimZeros();

    return res;
}
//================================================================================================

bool BigInt::operator < (const BigInt & other) const
{
    if (sign_ == Sign::NEGATIVE and other.sign_ == Sign::NON_NEGATIVE) return true;
    if (sign_ == Sign::NON_NEGATIVE and other.sign_ == Sign::NEGATIVE) return false;
    if (sign_ == Sign::NON_NEGATIVE and other.sign_ == Sign::NON_NEGATIVE) return abs_this_less_abs(other);
    if (sign_ == Sign::NEGATIVE and other.sign_ == Sign::NEGATIVE) return !abs_this_less_abs(other);
}

bool BigInt::abs_this_less_abs(const BigInt & other) const
{
    if (size() == other.size())
    {
        auto it_this = v_.rbegin();
        auto it_other = other.v_.rbegin();
        for ( ; it_this != v_.rend(); ++it_this, ++it_other)
        {
            if (*it_this < *it_other) return true;
            if (*it_this > *it_other) return false;
        }
        return false;
    }
    return size() < other.size();
}

BigInt BigInt::abs() const
{
    BigInt res(*this);
    if (res.sign_ == Sign::NEGATIVE) res.sign_ = Sign::NON_NEGATIVE;

    return res;
}

std::ostream & operator << (std::ostream & out, const BigInt & n)
{
    out << n.toString();
    return out;
}

std::istream & operator>>(std::istream & is, BigInt & n)
{
    std::string s;
    is >> s;

    n = BigInt(s);
    return is;
}
