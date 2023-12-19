#include <iostream>
#include <string>
#include <vector>

#include "print_vector.h"

void print_vector(const std::vector<double> &V, std::string message)
{
    std::cout << message;
    
    for (auto it = V.begin(); it != V.end(); it++)
    {
        std::cout << (*it) << " ";
    }
    
    std::cout << std::endl;
}
