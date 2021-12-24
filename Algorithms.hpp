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
            virtual bool operator()(const T &tarA,const T &tarB) const = 0;
        };

        //大于
        template<typename T>
        struct Greater:Comparator<T>{
            inline bool operator()(const T &tarA,const T &tarB) const{
                return tarA>tarB;
            }
        };

        //小于
        template<typename T>
        struct Less:Comparator<T>{
            inline bool operator()(const T &tarA,const T &tarB) const{
                return tarA<tarB;
            }
        };
        //冒泡排序
        template<typename T>
        int BubbleSort(DataStructure::DynamicArray <T> &array,
                        const Comparator<T> &comparator=Greater<T>{}){
            int len=array.Length(),swapCnt{};
            for(int i=0,flg;i<len-1;++i){
                flg=0;
                for(int j=0;j<len-i-1;++j)
                    if(comparator(array[j],array[j+1])){
                        std::swap(array[j],array[j+1]);
                        flg=1;
                        ++swapCnt;
                    }
                if(!flg) break;
            }
            return swapCnt;
        }

        //选择排序
        template<typename T>
        int SelectionSort(DataStructure::DynamicArray <T> &array,
                           const Comparator<T> &comparator=Greater<T>{}){
            int len=array.Length(),swapCnt{};
            for(int i=0,tar;i<len-1;++i){
                tar=i;
                for(int j=i+1;j<len;++j)
                    if(comparator(array[tar],array[j]))
                        tar=j,++swapCnt;
                if(tar!=i){
                    std::swap(array[i],array[tar]);
                    //++swapCnt;
                }
            }
            return swapCnt;
        }
        //插入排序
        template<typename T>
        int InsertionSort(DataStructure::DynamicArray <T> &array,
                           const Comparator<T> &comparator=Greater<T>{}){
            int len=array.Length(),swapCnt{};
            for(int i=0,tar;i<len-1;++i){
                tar=i;
                while(tar>=0&&comparator(array[tar],array[i+1]))
                    --tar;
                if(tar!=i){
                    array.SwapPartition(DataStructure::Partition{i+1,i+1},
                                        DataStructure::Partition{tar+1,i});
                    swapCnt+=i-tar;
                }
            }
            return swapCnt;
        }
        //希尔排序
        template<typename T>
        int ShellSort(DataStructure::DynamicArray <T> &array,
                          const Comparator<T> &comparator=Greater<T>{}){
            int len=array.Length(),swapCnt{};
            for(int gap=len>>1;gap;gap>>=1){
                for(int i=0;i<gap;i++){
                    for(int j=i+gap,tmp,tar;j<len;j=j+gap){
                        tar=j-gap,tmp=array[j];
                        while(tar>=0&&array[tar]>tmp){
                            array[tar+gap]=array[tar];
                            ++swapCnt;
                            tar-=gap;
                        }
                        array[tar+gap]=tmp;
                    }
                }
            }
            return swapCnt;
        }
        //快速排序
        template<typename T>
        int QuickSort(DataStructure::DynamicArray <T> &array,
                      const int _start=-1,const int _end=-1,
                      const Comparator<T> &comparator=Greater<T>{}){
            int start=(~_start)?_start:0,
            end=(~_end)?_end:(array.Length()-1);

            int p=start-1,swapCnt{};
            T tmp=array[end];
            for(int i=start;i<end;++i)
                if(comparator(tmp,array[i])){
                    std::swap(array[i],array[++p]);
                    ++swapCnt;
                }
            if(p+1!=end){
                std::swap(array[p+1],array[end]);
                ++swapCnt;
            }
            if(start<p)
                swapCnt+=QuickSort(array,start,p,comparator);
            if(p+2<end)
                swapCnt+=QuickSort(array,p+2,end,comparator);
            return swapCnt;
        }
        //堆排序
        template<typename T>
        int HeapSort(DataStructure::DynamicArray <T> &array,
                      const Comparator<T> &comparator=Greater<T>{}){
            int swapCnt{};
            DataStructure::Heap<T,Greater<T> > heap;
            for(const T &dat : array)
                swapCnt+=heap.Push(dat);
            for(T &dat : array)
                dat=heap.Pop(&swapCnt);
            return swapCnt;
        }
        //归并排序
        template<typename T>
        int MergeSort(DataStructure::DynamicArray <T> &array,
                     T *tmpData=nullptr,
                     const int _start=-1,const int _end=-1,
                     const Comparator<T> &comparator=Greater<T>{}){
            int start=_start,end=_end,
                mid=(start+end)>>1;
            bool flg=false;
            if(!tmpData){
                start=0,end=array.Length()-1;
                tmpData=new T[array.Length()];
                flg=true;
            }
            if(start>=end)
                return 0;
            int swapCnt{};
            swapCnt+=MergeSort(array,tmpData,start,mid,comparator)
                    +MergeSort(array,tmpData,mid+1,end,comparator);

            int ptrL=start,ptrR=mid+1,tmpPtr=start;
            while(ptrL<=mid&&ptrR<=end)
                tmpData[tmpPtr++]=comparator(array[ptrL],array[ptrR])
                            ?array[ptrR++]
                            :array[ptrL++];
            while(ptrL<=mid)
                tmpData[tmpPtr++]=array[ptrL++];
            while(ptrR<=end)
                tmpData[tmpPtr++]=array[ptrR++];
            std::copy(tmpData+start,tmpData+end+1,&(array[start]));
            swapCnt+=end-start+1;
            if(flg) delete[] tmpData;
            return swapCnt;
        }
    }
}

#endif //SSEDATASTRUCTURE_ALGORITHMS_HPP
