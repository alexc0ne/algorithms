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

    size_t size() const;                            // get size
    std::string toString() const;                   // string from BigInt

    bool operator == (const BigInt &);              // operator ==
    //bool operator < (const BigInt &);               // operator ==
    //bool operator <= (const BigInt &);              // operator ==
    //bool operator > (const BigInt &);               // operator ==
    //bool operator >= (const BigInt &);              // operator ==
    //bool operator != (const BigInt &);              // operator ==


    const BigInt & operator += (const BigInt &);    // operator +=
    BigInt operator + (const BigInt &);

private:

    Sign sign_;                                     // sign of number
    std::vector<int16_t> v_;                        // stores single digits, last digit in v_[0]

    // perhaps make this method over
    // from updateIfNull() to trimIfNull()    // {3,0,1,0,0,0} -- > {3,0,1}
    void updateIfNull();                            // {0,...,0} --> {0}
};


std::ostream & operator << (std::ostream &, const BigInt &);    // operator <<

