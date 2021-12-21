// 2052313 周长赫
// T1

#include <functional>
#include <stdexcept>
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
        in>>tar.id>>tar.name;
        char sex[4];
        in>>sex;
        tar.sex=(std::strcmp(sex,"男")==0);
        in>>tar.age>>tar.category;
        return in;
    }
    std::ostream &operator<<(std::ostream &out,const StudentInfo &tar){

        return out;
    }


    template<typename T>
    class LinkedList{
    public:
        //节点类型
        struct Node{
            T data;
            Node *next;
        };
        //打印函数类型
        using PrintFunction=std::function<void(const T &data)>;
        //默认打印函数
        static PrintFunction defaultPrintFunc;

        LinkedList():length(0),head(nullptr){};
        virtual ~LinkedList();
        //在末尾连接
        bool Append(const T &data);
        //在第index个元素前插入
        bool Insert(int index, const T &data);
        //删除节点
        bool Remove(int index);
        //修改节点
        bool Modify(int index, const T &data);
        //查询节点
        const T &operator[](int index)const;
        //查询长度
        inline const int Length()const{
            return length;
        }
        //打印
        void Print(const PrintFunction &func=defaultPrintFunc)const;
    private:
        Node *at(int index)const;
        int length;
        Node *head;
    };

    template<typename T>
    typename LinkedList<T>::PrintFunction LinkedList<T>::defaultPrintFunc{[](const T &data){
        std::cout<<data<<std::endl;
    }};

    template<typename T>
    LinkedList<T>::~LinkedList(){
        Node *now{head},*tmp;
        while(now){
            tmp=now;
            now=now->next;
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
            head=new Node{data,head};
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
    void LinkedList<T>::Print(const LinkedList::PrintFunction &func)const{
        Node *tar=head;
        while(tar){
            func(tar->data);
            tar = tar->next;
        }
    }

}

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using Info=Sky::StudentInfo;
using List=Sky::LinkedList<Info>;
int main(){
    List infoList;

}