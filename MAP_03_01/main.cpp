#include <string>
#include <vector>
#include <random>
#include <algorithm>

#include "print_vector.h"
#include "sort_vector.h"

int main()
{
    //std::vector<double> V { 58,0.6,111111,876,-3,0.58,17,23,-11,-0.58,1.25,23,27,14,153,48,536,212,2,-18,248,349,-0,15 };
    const size_t size = 50;
    const double max_value = 100.0;
    
    std::vector<double> V(size);
    std::mt19937 gen;
    std::uniform_real_distribution<double> dist(-max_value, max_value);
    std::generate(V.begin(), V.end(), [&] () {return dist(gen);});
    
    print_vector(V, "Initial vector:\n");
    
    sort_vector(V);
    
    print_vector(V, "\nSorted vector:\n");
    
    return 0;
}
