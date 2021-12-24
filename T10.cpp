// 2052313 周长赫
// T10

#include "DataStructures.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <ctime>
#include <functional>
using namespace std;
using namespace Sky;
using Array=DataStructure::DynamicArray<int>;
using Part=DataStructure::Partition;
void Prompt(){
    cout<<"\
**********************************\n\
  T10 排序算法比较 2052313 周长赫\n\
**********************************\n\
    "<<endl;
}
void Hang(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<endl<<"按任意键继续..."<<endl;
    cin.get();
}
void Print(const Array &array){
    for(int ele : array)
        cout<<ele<<' ';
    cout<<endl;
}
void GetData(Array &data){
    int numCnt;
    cout<<"输入随机数的个数：";
    cin>>numCnt;
    for(int i=0;i<numCnt;++i)
        data.Append(rand()%100000000);
}
int main(){
    srand(time(0));
    Prompt();
    Array data,dataCopy;
    GetData(data);
    clock_t timer;
    cout<<"冒泡排序："<<endl;
    dataCopy=data;
    timer=clock();
    cout<<Algorithm::BubbleSort(dataCopy)<<endl;
    cout<<"耗时："<<(double)(clock()-timer)/CLOCKS_PER_SEC<<"秒"<<endl<<endl;

    cout<<"选择排序："<<endl;
    dataCopy=data;
    timer=clock();
    cout<<Algorithm::SelectionSort(dataCopy)<<endl;
    cout<<"耗时："<<(double)(clock()-timer)/CLOCKS_PER_SEC<<"秒"<<endl<<endl;

    cout<<"插入排序："<<endl;
    dataCopy=data;
    timer=clock();
    cout<<Algorithm::InsertionSort(dataCopy)<<endl;
    cout<<"耗时："<<(double)(clock()-timer)/CLOCKS_PER_SEC<<"秒"<<endl<<endl;

    cout<<"希尔排序："<<endl;
    dataCopy=data;
    timer=clock();
    cout<<Algorithm::ShellSort(dataCopy)<<endl;
    cout<<"耗时："<<(double)(clock()-timer)/CLOCKS_PER_SEC<<"秒"<<endl<<endl;

    cout<<"快速排序："<<endl;
    dataCopy=data;
    timer=clock();
    cout<<Algorithm::QuickSort(dataCopy)<<endl;
    cout<<"耗时："<<(double)(clock()-timer)/CLOCKS_PER_SEC<<"秒"<<endl<<endl;

    cout<<"堆排序："<<endl;
    dataCopy=data;
    timer=clock();
    cout<<Algorithm::HeapSort(dataCopy)<<endl;
    cout<<"耗时："<<(double)(clock()-timer)/CLOCKS_PER_SEC<<"秒"<<endl<<endl;

    cout<<"归并排序："<<endl;
    dataCopy=data;
    timer=clock();
    cout<<Algorithm::MergeSort(dataCopy)<<endl;
    cout<<"耗时："<<(double)(clock()-timer)/CLOCKS_PER_SEC<<"秒"<<endl<<endl;




    Hang();
    return 0;
}