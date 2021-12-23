// 2052313 周长赫
// T4

#include "Containers.hpp"
#include <iostream>
using namespace std;
using Sky::Container::Graph;
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
int main(){
    Prompt();

    Hang();
    return 0;
}