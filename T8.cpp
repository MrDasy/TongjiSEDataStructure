// 2052313 周长赫
// T4

#include "DataStructures.hpp"
#include "Algorithms.hpp"
#include <iostream>
using namespace std;
using Sky::DataStructure::Tree;
using DSet=Sky::DataStructure::DisjointSet;
using Edge=Tree::Edge;
using EdgeArray=Sky::DataStructure::DynamicArray<Edge>;
using EdgeQueue=Sky::DataStructure::Queue<Edge>;
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
istream &operator>>(istream &in,Edge &edge){
    in>>edge.from>>edge.to>>edge.length;
    return in;
}
int nodeNum,edgeNum;
void GetData(EdgeArray &edgeArray){
    cout<<"[读入数据]"<<endl;
    cout<<"请输入节点个数：";
    cin>>nodeNum;
    cout<<"请输入边条数：";
    cin>>edgeNum;
    cout<<"请输入每一条边：\n（起点 端点 权值）"<<endl;
    Edge tmpEdge;
    for(int i=0;i<edgeNum;++i){
        cin>>tmpEdge;
        edgeArray.Append(tmpEdge);
    }
    Sky::Algorithm::Quicksort(edgeArray,0,edgeNum-1);
}
void PrintTree(const Tree &tree){
    EdgeQueue q;
    bool *visited=new bool[tree.CountNode()+1]{};
    q.Push(Edge{-1,tree.GetRoot(),-1});
    int nowNode;
    do{
        nowNode=q.Pop().to;
        for(const Edge &edge : tree[nowNode]){
            printf("(%d=[%d]=>%d ",edge.from,edge.length,edge.to);
            q.Push(edge);
        }
    }while(!q.IsEmpty());
}
bool Kruskal(const EdgeArray &edgeArray){
    DSet dset(nodeNum);
    Tree tree(nodeNum,1);
    for(const Edge &edge : edgeArray)
        if(!dset.Check(edge.from,edge.to)){
            dset.Merge(edge.from,edge.to);
            tree.AddEdge(edge);
        }
    if(tree.CountEdge()==nodeNum-1){
        PrintTree(tree);
        return true;
    }
    return false;
}
int main(){
    Prompt();
    EdgeArray edgeArray;
    GetData(edgeArray);
    Hang();
    return 0;
}