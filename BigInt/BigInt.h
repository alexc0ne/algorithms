#pragma once
#include <vector>
#include <string>


enum class Sign
{
    NEGATIVE,
    NON_NEGATIVE
};


class BigInt
{
public:

    BigInt();                                       // default ctor
    BigInt(const std::string &);                    // string ctor
    BigInt(int64_t);                                // int ctor
    BigInt(const BigInt &);                         // copy ctor

    BigInt & operator = (const BigInt &);           // operator =

    size_t size() const;                            // get size
    std::string toString() const;                   // string from BigInt

    bool operator == (const BigInt &) const;        // operator ==
    bool operator < (const BigInt &) const;         // operator <

    const BigInt & operator += (BigInt &);    // operator +=
    BigInt operator + (BigInt &);             // operator +

private:

    Sign sign_;                                     // sign of number
    std::vector<int16_t> v_;                        // stores single digits, last digit in v_[0]

    void trimZeros();                               // {3,0,1,0,0,0} --> {3,0,1}, but {0,...,0} --> {0}
    bool abs_less_comparison(const BigInt &other) const;      // returns abs(this) < abs(other))
    void add(BigInt &);                             // add two numbers with the same sign, e.g. -6 and -11
    void complement(BigInt &);                      // -(189,89), complement of 89 is 911, then +(189,911) = 1|100
    void swap(BigInt &);                            // swaps this and other
};


// ======== auxiliary functions =============================================================================
std::ostream & operator << (std::ostream &, const BigInt &);    // operator <<
