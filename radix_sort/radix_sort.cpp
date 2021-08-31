/*

    radix_sort:

    this implementation works only for the arrays,
    that contain ONLY non-negative numbers!

*/



#include <vector>
using std::vector;
using vvi = std::vector<std::vector<int>>;



int get_nth_bit(int n, int bit)
{
    // bit >= 0
    while (bit)
    {
        n /= 10;
        --bit;
    }

    return n % 10;        
}



void count_sort(vector<int> & v, int bit)
{
    vvi cnt(10);

    for (int item : v)
        cnt[get_nth_bit(item, bit)].push_back(item);

    int idx = 0;
    for (int i = 0; i < cnt.size(); ++i)
        for (int j = 0; j < cnt[i].size(); ++j)
        {
            v[idx] = cnt[i][j];
            ++idx;
        }
}



void radix_sort(vector<int> & v, int max_num_len)
{
    for (int i = 0; i < max_num_len; ++i)
        count_sort(v, i);
}

