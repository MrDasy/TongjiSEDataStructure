//
// Created by MrDas on 2021/12/22.
//

#include <functional>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <stdexcept>
#include <iostream>

namespace Sky{

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
        if(length==0)
            return nullptr;
        index=(index%length+length)%length;
        Node *now=head;
        while(index--)
            now=now->next;
        return now;
    }

    template<typename T>
    bool SingleCircularLinkedList<T>::Append(const T &data){
        Node *now=new Node{data, nullptr};
        if(!length)
            head=now;
        else
            this->at(-1)->next=now;
        now->next=head;
        ++length;
        return true;
    }

    template<typename T>
    bool SingleCircularLinkedList<T>::Insert(int index, const T &data){
        if(length==0) {
            head = new Node{data, head};
            return true;
        }
        index=(index%length+length)%length;
        Node *now=new Node{data, this->at(index)};
        this->at(index-1)->next=now;
        if(index==0)
            head=now;
        ++length;
        return true;
    }

    template<typename T>
    bool SingleCircularLinkedList<T>::Remove(const int index){
        if(length==0)
            return false;
        Node *tmp=this->at(index);
        if(length>1)
            this->at(index-1)->next=tmp->next;
        delete tmp;
        --length;
        return true;
    }

    template<typename T>
    using LList=LinkedList<T>;
    template<typename T>
    using SCLList=SingleCircularLinkedList<T>;
}

using namespace std;
using EFunc=Sky::ErgodicFunction<int>;
using YFList=Sky::SCLList<int>;
void Hang(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<endl<<"按任意键继续..."<<endl;
    cin.get();
}
int main(){
    YFList List;
    List.Append(2);
    cout<<List[-2];
    Hang();
}