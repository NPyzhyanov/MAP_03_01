#include <thread>

#include "determine_concurency.h"

unsigned int determine_concurency()
{
    unsigned int hardware_concurency = std::thread::hardware_concurrency();
    
    if (hardware_concurency < 2) //         1
    {
        return 1; //                        1
    }
    else if (hardware_concurency < 8) //        2   3   4   5   6   7   
    {
        return hardware_concurency - 1; //      1   2   3   4   5   6
    }
    else if (hardware_concurency < 32) //                               8   9   10  11  12  13  ... 30  31
    {
        return (hardware_concurency * 3) / 4; //                        6   6   7   8   9   9   ... 22  23
    }
    
    return 24;
}
