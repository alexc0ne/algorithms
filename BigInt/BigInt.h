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
    BigInt();                                   // default ctor
    BigInt(const std::string &);                // string ctor
    BigInt(int64_t);                            // int ctor
    BigInt(const BigInt &);                     // copy ctor

    size_t size() const;                        // get size
    std::string toString() const;               // string from BigInt

    bool operator == (const BigInt &);          // operator ==

private:
    Sign sign_;                                 // sign of number
    std::vector<int16_t> v_;                    // stores single digits, last digit in v_[0]
};

