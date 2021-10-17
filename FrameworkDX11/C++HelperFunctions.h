#pragma once
#include <random>
#include<iostream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

namespace RandomGen {
   
    //randome int
    template<typename T>
    T random(T range_from, T range_to) {
        std::random_device   rand_dev;
        std::mt19937                        generator(rand_dev());
        std::uniform_int_distribution<T>    distr(range_from, range_to);
        return distr(generator);
    }
    //randome float,double
    template<typename T>
    T randomFloat(T range_from, T range_to) {
        std::random_device   rand_dev;
        std::mt19937                        generator(rand_dev());
        std::uniform_real_distribution<T>    distr(range_from, range_to);
        return distr(generator);
    }

    
}

namespace ListHelpers {
  
   //remove data from vector
    template<typename T>
    bool RemoveFromVector(vector<T>* List, T *ToRemove) {
        vector<T>::iterator iter = List->begin();
        while (iter != List->end()) {
            if (*iter == *ToRemove) {
                iter = List->erase(iter);
                return true;
            }
            else
            {
                ++iter;
            }
        }
        return false;
    }
    //remove data from MutiMap
    template<typename FirstType, typename SecondType>
    bool RemoveFromMutiMap(std::multimap<FirstType, SecondType> *Map, SecondType *ToRemove) {
        std::multimap<FirstType, SecondType> ::iterator iter = Map->begin();
        while (iter != Map->end()) {
            if (iter->second == *ToRemove) {
                iter = Map->erase(iter);
            }
            else
            {
                ++iter;
            }
        }
        return true;
    }





}


