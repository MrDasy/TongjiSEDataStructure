//
// Created by MrDas on 2021/12/24.
//

#ifndef SSEDATASTRUCTURE_ALGORITHMS_HPP
#define SSEDATASTRUCTURE_ALGORITHMS_HPP
#include "DataStructures.hpp"

namespace Sky{
    namespace Algorithm{
    //比较器
    template<typename T>
    struct Comparator{
        virtual bool operator()(const T &tarA,const T &tarB)const=0;
    };
    //从小到大
    template<typename T>
    struct Greater:Comparator<T>{
        inline bool operator()(const T &tarA,const T &tarB)const{
            return tarA<tarB;
        }
    };
    //从大到小
    template<typename T>
    struct Less:Comparator<T>{
        inline bool operator()(const T &tarA,const T &tarB)const{
            return tarA>tarB;
        }
    };
    //快速排序
    template <typename T>
    void Quicksort(DataStructure::DynamicArray<T> &array,const int start,const int end,
                   const Comparator<T> &comparator=Greater<T>{}){
        int p=start;
        for(int i=start;i<end;++i)
            if(comparator(array[i],array[end]))
                std::swap(array[i],array[p++]);
        std::swap(array[p],array[end]);
        if (start<p-1)
            Quicksort(array,start,p-1);
        if(p+1<end)
            Quicksort(array,p+1,end);
    }
    }
}


#endif //SSEDATASTRUCTURE_ALGORITHMS_HPP
