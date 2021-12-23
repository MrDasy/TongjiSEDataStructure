// 2052313 周长赫
// T2

#include "DataStructures.hpp"
#include <iostream>
#include <iomanip>
using namespace std;
namespace Sky{
    struct YFData{
        int totalNum; //初始人数
        int startOrd; //开始序号
        int deadOrd; //报到deadOrd的人出局
        int finalNum; //最终剩余人数
    };
}
using EFunc=Sky::DataStructure::ErgodicFunction<int>;
using YFList=Sky::DataStructure::SCLList<int>;
using Data=Sky::YFData;

void Prompt(){
    cout<<"\
********************************************\n\
  T2 约瑟夫生者死者游戏 2052313 周长赫\n\
********************************************\n\
    "<<endl;
}
void Hang(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<endl<<"按任意键继续..."<<endl;
    cin.get();
}
bool CheckData(const Data &data){
    return (data.totalNum|data.finalNum|data.deadOrd|data.startOrd)>0
        && data.totalNum>data.finalNum
        && data.totalNum>=data.startOrd
        && data.startOrd>0;
}
void GetData(Data &data){
    cout<<"[规则介绍]"<<endl;
    cout<<"现有N人排成一圈，自第S人开始报数，报M的人出局，再由下一人重新开始报数，直至剩K人为止。"<<endl;
    cout<<endl;
    while(true){
        cout<<"[读入数据]"<<endl;
        cout<<"请输入总人数N：";
        cin>>data.totalNum;
        cout<<"请输入游戏开始位置S：";
        cin>>data.startOrd;
        cout<<"请输入死亡数字M：";
        cin>>data.deadOrd;
        cout<<"请输入目标人数K：";
        cin>>data.finalNum;
        if(CheckData(data)){
            cout<<"数据读入完毕！"<<endl;
            break;
        }
        cout<<"数据读入失败，请检查各数值..."<<endl;
    }
}
void Compute(const Data &data){
    YFList List;
    int nowOrd{data.startOrd-1};
    for(int i=1;i<=data.totalNum;++i)
        List.Append(i);
    cout<<"[游戏开始]"<<endl;
    for(int i=1;i<=data.totalNum-data.finalNum;++i){
        nowOrd+=data.deadOrd-1;
        nowOrd%=List.Length();
        cout<<"第"<<i<<"个淘汰的人是："<<setw(3)<<List[nowOrd]<<endl;
        List.Remove(nowOrd);
    }

    int nlCnt=0;
    EFunc printFunc=[&nlCnt](const int &data){
        cout<<setw(3)<<data<<((++nlCnt)%5?' ':'\n');
    };
    cout<<"[游戏结束]"<<endl;
    cout<<"最后剩下"<<setw(3)<<data.finalNum<<"人，分别为："<<endl;
    List.Ergodic(printFunc);
}

int main(){
    Prompt();
    Data data{};
    GetData(data);
    Compute(data);
    Hang();
    return 0;
}