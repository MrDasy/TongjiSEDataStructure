// 2052313 周长赫
// T2

#include <functional>
#include <stdexcept>

namespace Sky{
    struct YFData{
        int totalNum; //初始人数
        int startOrd; //开始序号
        int deadOrd; //报到deadOrd的人出局
        int finalNum; //最终剩余人数
    };
    //遍历函数 类型
    template<typename T>
    using ErgodicFunction=std::function<void(const T &data)>;

    template<typename T>
    class LinkedList{
    public:
        //节点类型
        struct Node{
            T data;
            Node *next;
        };

        LinkedList():length(0),head(nullptr){};
        virtual ~LinkedList();
        //在末尾连接
        virtual bool Append(const T &data);
        //在第index个元素前插入
        virtual bool Insert(int index, const T &data);
        //删除节点
        virtual bool Remove(int index);
        //修改节点
        bool Modify(int index, const T &data);
        //查询节点
        const T &operator[](int index)const;
        //查询长度
        inline int Length()const{
            return length;
        }
        //遍历 根据每个数据执行func
        void Ergodic(const ErgodicFunction<T> &func)const;

    protected:
        virtual Node *at(int index)const;
        int length;
        Node *head;
    };

    template<typename T>
    LinkedList<T>::~LinkedList(){
        Node *tar=head,*tmp;
        for(int i=length;i;--i){
            tmp=tar;
            tar=tar->next;
            delete tmp;
        }
    }

    template<typename T>
    bool LinkedList<T>::Append(const T &data){
        Node *now=new Node{data, nullptr};
        if(!length)
            head=now;
        else
            this->at(-1)->next=now;
        ++length;
        return true;
    }

    template<typename T>
    bool LinkedList<T>::Insert(const int index, const T &data){
        if(index==0||index==-length)
            head=new Node{data, nullptr};
        else{
            Node *tar;
            if(!(tar=this->at(index-1)))
                return false;
            tar->next=new Node{data,tar->next};
        }
        ++length;
        return true;
    }

    template<typename T>
    bool LinkedList<T>::Remove(const int index){
        Node *tar;
        if(!(tar=this->at(index)))
            return false;
        if(tar==head)
            head=head->next;
        else
            this->at(index-1)->next=tar->next;
        delete tar;
        --length;
        return true;
    }

    template<typename T>
    bool LinkedList<T>::Modify(const int index, const T &data){
        Node *tar;
        if(!(tar=this->at(index)))
            return false;
        tar->data=data;
        return true;
    }

    template<typename T>
    typename LinkedList<T>::Node *LinkedList<T>::at(const int index) const{
        if(index>=length||index<-length)
            return nullptr;
        if(index>=0){
            Node *now=head;
            for(int i=0;i<index;++i)
                now=now->next;
            return now;
        }else
            return this->at(length+index);
    }

    template<typename T>
    const T &LinkedList<T>::operator[](const int index) const{
        Node *tar;
        if(!(tar = this->at(index))){ throw std::out_of_range("Illegal Position."); }
        return tar->data;
    }

    template<typename T>
    void LinkedList<T>::Ergodic(const ErgodicFunction<T> &func) const {
        Node *tar=head;
        for(int i=length;i;--i){
            func(tar->data);
            tar=tar->next;
        }
    }

    template<typename T>
    class SingleCircularLinkedList:public LinkedList<T>{
    public:
        bool Append(const T &data) override;
        bool Insert(int index, const T &data) override;
        bool Remove(int index) override;
    private:
        Node *at(int index)const override;
    };

    template<typename T>
    typename SingleCircularLinkedList<T>::Node *SingleCircularLinkedList<T>::at(int index) const{
        if(this->length==0)
            return nullptr;
        index=(index%this->length+this->length)%this->length;
        Node *now=head;
        while(index--)
            now=now->next;
        return now;
    }

    template<typename T>
    bool SingleCircularLinkedList<T>::Append(const T &data){
        Node *now=new Node{data, nullptr};
        if(!this->length)
            head=now;
        else
            this->at(-1)->next=now;
        now->next=head;
        ++this->length;
        return true;
    }

    template<typename T>
    bool SingleCircularLinkedList<T>::Insert(int index, const T &data){
        if(this->length==0) {
            head = new Node{data, head};
            return true;
        }
        index=(index%this->length+this->length)%this->length;
        Node *now=new Node{data, this->at(index)};
        this->at(index-1)->next=now;
        if(index==0)
            this->head=now;
        ++this->length;
        return true;
    }

    template<typename T>
    bool SingleCircularLinkedList<T>::Remove(const int index){
        if(this->length==0)
            return false;
        Node *tmp=this->at(index);
        if(this->length>1)
            this->at(index-1)->next=tmp->next;
        if(tmp==this->head)
            this->head=tmp->next;
        delete tmp;
        --this->length;
        return true;
    }

    template<typename T>
    using LList=LinkedList<T>;
    template<typename T>
    using SCLList=SingleCircularLinkedList<T>;
}

#include <iostream>
#include <iomanip>
using namespace std;
using EFunc=Sky::ErgodicFunction<int>;
using YFList=Sky::SCLList<int>;
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