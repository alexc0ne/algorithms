#include "ext_gcd.h"



// solves a * x + b * y = gcd(a, b)
// returns {x, y, gcd(a, b)}
// here is supposed that a >= 0, b >= 0
::tuple ext_gcd(Int a, Int b)
{
    if (b == 0) return {1, 0, a};

    ::tuple next = ext_gcd(b, a % b);

    // gcd(a, b) = d = gcd(b, a % b)
    // ax + by = d = bx' + (a%b)y'
    // x = y'
    // y = x' - (a/b)*y'
    return {
        next.y_,
        next.x_ - (a / b) * next.y_,
        next.gcd_
    };
}

