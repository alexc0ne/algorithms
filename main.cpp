#include <iostream>
#include "Output.h"
#include <vector>
#include "Timer.h"
#include "quick_sort.h"
using namespace std;



int main()
{
    vector<int> v;
    v.reserve(20'000'001);
    int random;

    for (int i = 0; i < 20'000'000; ++i)
    {
        random = get_random_in_range(0, 1000);
        v.push_back(random);
    }
    {
        Timer t;
        quick_sort(v);
    }

    for (int i = 0; i + 1 < v.size(); ++i)
    {
        if (v[i] > v[i + 1])
        {
            cout << v[i] << endl << v[i+1] << endl;
            break;
        }
    }

    return 0;
}

