#include <vector>
#include <future>
#include <map>

#include "sort_vector.h"
#include "find_min.h"
#include "determine_concurency.h"

void sort_vector(std::vector<double> &V)
{
    const unsigned int allowed_concurency = determine_concurency();
    
    unsigned int unsorted_left = V.size();
    unsigned int first_unsorted = 0;
    
    while (unsorted_left > 1)
    {
        const unsigned int algo_concurency = (unsorted_left >= allowed_concurency ? allowed_concurency : unsorted_left);
        const unsigned int one_thread_size = unsorted_left / algo_concurency;
        
        std::vector<std::future<int>> ft_min_indexes;
        std::vector<std::future<int>> F(algo_concurency);
        
        std::multimap<double, int> min_elements;
        
        for (unsigned int th = 0; th < algo_concurency; th++)
        {
            auto th_begin = V.begin() + first_unsorted + th * one_thread_size;
            auto th_end = (th == (algo_concurency - 1) ? V.end() : (th_begin + one_thread_size));
            
            std::promise<int> prom_min_index;
            ft_min_indexes.push_back(prom_min_index.get_future());
            
            F.at(th) = std::async(std::launch::async, find_min, th_begin, th_end, std::move(prom_min_index));
        }
        
        for (unsigned int th = 0; th < algo_concurency; th++)
        {
            int index = first_unsorted + ft_min_indexes.at(th).get() + th * one_thread_size;
            min_elements.insert(std::make_pair(V.at(index), index));
        }
        
        int min_elem_index = std::get<1>(*(min_elements.begin()));
        
        double tmp = V.at(first_unsorted);
        V.at(first_unsorted) = V.at(min_elem_index);
        V.at(min_elem_index) = tmp;
        
        unsorted_left--;
        first_unsorted++;
    }
}
