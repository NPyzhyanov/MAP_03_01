#include <vector>
#include <future>

#include "find_min.h"

int find_min(const std::vector<double>::iterator &begin, const std::vector<double>::iterator &end, std::promise<int> prom)
{
    if (begin == end - 1)
    {
        prom.set_value(0);
        return 0;
    }
    
    double min_elem = *begin;
    int min_index = 0;
    
    for (auto it = begin + 1; it != end; it++)
    {
        if (*it < min_elem)
        {
            min_elem = *it;
            min_index = it - begin;
        }
    }
    
    prom.set_value(min_index);
    return min_index;
}
