// 2052313 周长赫
// T4

#include "DataStructures.hpp"
#include <iostream>
using namespace std;
using Sky::DataStructure::Tree;
using DSet=Sky::DataStructure::DisjointSet;
void Prompt(){
    cout<<"\
**********************************\n\
  T8 电网建设造价模拟系统 2052313 周长赫\n\
**********************************\n\
    "<<endl;
}
void Hang(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<endl<<"按任意键继续..."<<endl;
    cin.get();
}
void Operate(){
    int nodeNum;
    cout<<"[读入数据]"<<endl;
    cout<<"请输入节点个数：";
    cin>>nodeNum;
    Tree tree(nodeNum,1);
    DSet dset(nodeNum);

}
int main(){
    Prompt();
    Operate();
    Hang();
    return 0;
}