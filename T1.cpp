// 2052313 周长赫
// T1

#include "DataStructures.hpp"
#include <iostream>
namespace Sky{
    struct StudentInfo{
        friend std::istream &operator>>(std::istream &in,StudentInfo &tar);
        friend std::ostream &operator<<(std::ostream &out,const StudentInfo &tar);

        char name[20];//姓名
        int id;//学号
        bool sex;//男true女false
        short age;//年龄
        char category[20];//报考类别
    };
    std::istream &operator>>(std::istream &in,StudentInfo &tar){
        char sex[20];
        in>>tar.id
        >>tar.name;
        in>>sex;
        tar.sex=(std::strcmp(sex,"男")==0);
        in>>tar.age
        >>tar.category;
        return in;
    }
    std::ostream &operator<<(std::ostream &out,const StudentInfo &tar){
        out<<tar.id<<' '
        <<tar.name<<' '
        <<(tar.sex?"男":"女")<<' '
        <<tar.age<<' '
        <<tar.category;
        return out;
    }
}
/*主程序实现*/
using namespace std;
using Info=Sky::StudentInfo;
using InfoList=Sky::DataStructure::LList<Info>;
using EFunc=Sky::DataStructure::ErgodicFunction<Info>;
void Prompt(){
    cout<<"\
**********************************\n\
  T1 考试报名系统 2052313 周长赫\n\
**********************************\n\
    "<<endl;
}
void Hang(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<endl<<"按任意键继续..."<<endl;
    cin.get();
}
void ShowHelp(){
    cout<<"\
[操作指南]\n\
> 位置从零开始，\n\
> 0 ~ (n-1) 分别表示第1至第n条信息，\n\
> -1 ~ -n 表示倒数第1至第n条信息\n\
0：退出程序\n\
1：在指定位置前插入信息\n\
2：删除指定位置的信息\n\
3：查找第一个学号为指定值的信息\n\
4：修改指定位置的信息\n\
5：输出表内所有信息\n\
    "<<endl;
}
void BuildDataSheet(InfoList &infoList){
    int num;
    Info tmp;
    cout<<"[首先请建立考生信息系统]"<<endl;
    cout<<"请输入考生人数：";
    cin>>num;
    cout<<"请输入每位考生的信息："<<endl;
    cout<<"学号 姓名 性别（男/女） 年龄 报考类别"<<endl;
    while(num--){
        cin>>tmp;
        infoList.Append(tmp);
    }
    cout<<"[考生信息系统建立完毕]"<<endl;
}
void Operate(InfoList &infoList){
    int operOrd,targetId;
    bool found{};
    Info infoFound{};

    EFunc findFunc=[&found,&infoFound,&targetId](const Info &data){
        if(found)return;
        if(data.id==targetId){
            found= true;
            infoFound=data;
        }
    };
    EFunc printFunc=[](const Info &data){
        cout<<data<<endl;
    };

    ShowHelp();
    cout<<"[开始操作]"<<endl;
    while(true) {
        cout << "请选择您要进行的操作：";
        cin >> operOrd;
        switch (operOrd) {
            case 0:
                return;
            case 1: {
                int ord;
                Info tmp;
                cout << "请输入您要插入的位置：";
                cin >> ord;
                cout << "请输入考生的信息：" << endl;
                cout << "学号 姓名 性别（男/女） 年龄 报考类别" << endl;
                cin >> tmp;
                cout << (infoList.Insert(ord, tmp) ? "插入成功" : "插入失败，请检查输入的信息") << endl;
            }
                break;
            case 2: {
                int ord;
                cout << "请输入您要删除的位置：";
                cin >> ord;
                Info tmp;
                try {
                    tmp = infoList[ord];
                } catch (std::out_of_range &e) {
                    cout << "删除失败，输入位置非法" << endl;
                    break;
                }
                infoList.Remove(ord);
                cout << "被删除考生的信息为：" << endl;
                cout << tmp << endl;
                cout << "删除成功" << endl;
            }
                break;
            case 3:{
                cout << "请输入您要查找的学号：";
                cin >> targetId;
                found=false;
                infoList.Ergodic(findFunc);
                if(found){
                    cout<<"查找成功，考生信息为："<<endl;
                    cout<<infoFound<<endl;
                }else
                    cout << "查找失败，未找到指定学号考生" << endl;
            }
                break;
            case 4:{
                int ord;
                cout << "请输入您要修改的位置：";
                cin >> ord;
                Info tmp;
                try{
                    tmp = infoList[ord];
                }catch (std::out_of_range &e) {
                    cout << "修改失败，输入位置非法" << endl;
                    break;
                }
                cout << "当前考生的信息：" << endl;
                cout<<tmp<<endl;
                cout << "请输入修改后考生的信息：" << endl;
                cout << "学号 姓名 性别（男/女） 年龄 报考类别" << endl;
                cin>>tmp;
                infoList.Modify(ord,tmp);
                cout << "修改成功" << endl;
            }
                break;
            case 5:
                infoList.Ergodic(printFunc);
                cout<<"共"<<infoList.Length()<<"名考生"<<endl;
                cout << "输出完毕" << endl;
                break;
            default:
                cout<<"未知操作数，请仔细参阅操作指南！"<<endl;
                ShowHelp();
                break;
        }
        cout << endl;
    }
}

int main(){
    InfoList infoList;
    Prompt();
    BuildDataSheet(infoList);
    Operate(infoList);
    Hang();
    return 0;
}