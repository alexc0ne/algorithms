#pragma once
#include <vector>
#include <string>


enum class Sign
{
    NEGATIVE,
    NON_NEGATIVE
};

Sign revert(Sign);


class BigInt
{
public:

    BigInt();                                             // default ctor
    BigInt(const std::string &);                          // string ctor
    BigInt(int64_t);                                      // int ctor
    BigInt(const BigInt &);                               // copy ctor

    BigInt & operator = (const BigInt &);                 // operator =

    size_t size() const;                                  // get size
    std::string toString() const;                         // string from BigInt

    BigInt abs() const;                                   // returns abs(this)
    BigInt mod(size_t) const;                             // returns this % 10^n
    BigInt div(size_t) const;                             // returns this / 10^n
    BigInt mul(size_t) const;                             // returns this * 10^n

    bool operator == (const BigInt &) const;              // operator ==
    bool operator != (const BigInt &) const;              // operator !=
    bool operator < (const BigInt &) const;               // operator <

    const BigInt & operator += (const BigInt &);          // operator +=
    BigInt operator + (const BigInt &);                   // operator +
    const BigInt & operator -= (const BigInt &);          // operator -=
    BigInt operator - (const BigInt &);                   // operator -
    const BigInt & operator *= (const BigInt &);          // operator *=
    BigInt operator * (const BigInt &);                   // operator *

private:

    Sign sign_;                                           // sign of number
    std::vector<int16_t> v_;                              // stores single digits, last digit in v_[0]

    void trimZeros();                                     // {3,0,1,0,0,0} --> {3,0,1}, but {0,...,0} --> {0}
    bool abs_this_less_abs(const BigInt &other) const;    // returns abs(this) < abs(other))
    void add(const BigInt &);                             // add two numbers with the same sign, e.g. -6 and -11, or 0 and 7
    void subtract(const BigInt &);                        // subtract numbers with property: abs(this) > abs(other)
};


// ======== auxiliary functions =============================================================================
std::ostream & operator << (std::ostream &, const BigInt &);    // operator <<
std::istream & operator >> (std::istream &, BigInt &);    // operator >>
BigInt karatsuba(const BigInt &, const BigInt &);

