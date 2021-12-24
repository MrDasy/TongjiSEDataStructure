//
// Created by MrDas on 2021/12/23.
//

#ifndef SSEDATASTRUCTURE_DATASTRUCTURES_HPP
#define SSEDATASTRUCTURE_DATASTRUCTURES_HPP

#include <functional>
#include <utility>
#include <stdexcept>
#include <algorithm>
namespace Sky{
    namespace DataStructure{
        //遍历函数 类型
        template<typename T>
        using ErgodicFunction=std::function<void(const T &data)>;
        //二维向量
        template<typename T>
        struct Vector2{
            T x,y;
            //重载二维向量加法
            Vector2 operator+(const Vector2 &tar)const;
            //重载二维向量等于
            bool operator==(const Vector2 &tar)const;
        };
        //单向链表
        template<typename T>
        class LinkedList{
        protected:
            //节点类型
            struct Node{
                T data;
                Node *next;
            };

            int length;
            Node *head;

            virtual Node *at(int index)const;
        public:
            class Iterator{
            private:
                Node *target;//迭代器指向目标
                int ord;
                int length;
            public:
                Iterator(Node *target,int ord,int length):target(target),ord(ord),length(length){}
                T &operator*()const;
                Iterator &operator++();
                bool operator!=(const Iterator &itr)const;
            };

            inline LinkedList():length(0),head(nullptr){};
            virtual ~LinkedList();

            inline Iterator begin(){return Iterator{head,0,length};};
            inline Iterator end(){return Iterator{nullptr,length,length};};
            //在末尾连接
            virtual bool Append(const T &data);
            //在第index个元素前插入
            virtual bool Insert(int index, const T &data);
            //删除节点
            virtual bool Remove(int index);
            //修改节点
            virtual bool Modify(int index, const T &data);
            //查询节点
            virtual const T &operator[](int index)const;
            //遍历 根据每个数据执行func
            virtual void Ergodic(const ErgodicFunction<T> &func)const;
            //查询长度
            inline int Length()const{
                return this->length;
            }
        };
        //单向循环链表
        template<typename T>
        class SingleCircularLinkedList:public LinkedList<T>{
        protected:
            using Node=typename LinkedList<T>::Node;
            using Iterator=typename LinkedList<T>::Iterator;

            Node *at(int index)const override;
        public:
            bool Append(const T &data) override;
            bool Insert(int index, const T &data) override;
            bool Remove(int index) override;
        };
        //队列
        template<typename T>
        class Queue{
        public:
            struct Node{
                T data;
                Node *prev,*next;
            };
            Queue():length(0),front(nullptr),tail(nullptr){}
            ~Queue();
            //获取队尾元素
            T Top()const;
            //元素出队
            T Pop();
            //元素入队
            void Push(const T &data);
            //判断是否为空
            inline bool IsEmpty()const{return length==0;}
        private:
            Node *front,*tail;
            int length;
        };
        //动态扩容数组
        template<typename T>
        class DynamicArray{
        private:
            int capacity;
            int currentSize;
            T *data;

            T &explore(int index);
        public:
            inline T *begin()const {return data;}
            inline T *end()const {return data+currentSize;}

            const static int LIMIT=1<<20;
            explicit DynamicArray(int initialSize=8);
            ~DynamicArray();

            T &operator[](int index);
            T &operator[](int index)const;
            void Append(const T &tar);
            inline int Length()const {return currentSize;}
            inline int Capacity()const {return capacity;}
        };
        //图
        class Graph{
        public:
            //边类
            struct Edge{
                int from,to,length;
                //取反边
                Edge operator~()const;
                bool operator>(const Edge &tar)const;
            };
            //迭代器类 用于访问某个点的所有边
            class Iterator{
            public:
                Iterator(const DynamicArray<int> &nextSet,const DynamicArray<Edge> &edgeSet,int nowOrd)
                :nextSet(nextSet),edgeSet(edgeSet),nowOrd(nowOrd){}
                Iterator &operator++();
                bool operator!=(const Iterator &tar)const;
                Edge &operator*()const;
            private:
                const DynamicArray<int> &nextSet;
                const DynamicArray<Edge> &edgeSet;
                int nowOrd;
            };
            struct NodeAgency{
                const DynamicArray<int> &headSet;
                const DynamicArray<int> &nextSet;
                const DynamicArray<Edge> &edgeSet;
                int nodeOrd;
                inline Iterator begin(){return Iterator{nextSet,edgeSet,headSet[nodeOrd]};}
                inline Iterator end(){return Iterator{nextSet,edgeSet,0};}
            };
            inline explicit Graph(int initialSize=10):nodeCnt(initialSize){edgeSet.Append(Edge{0,0,0});}
            void AddEdge(int from,int to,int length=0);
            void AddEdge(const Edge &edge);
            NodeAgency operator[](int nodeIndex)const;
            inline int CountNode()const {return nodeCnt;}
            inline int CountEdge()const {return edgeSet.Length();}
        protected:
            int nodeCnt;
            DynamicArray<Edge> edgeSet;
            DynamicArray<int> headSet,nextSet;
        };
        //树
        class Tree: public Graph{
        public:
            explicit Tree(int nodeSize,int root=1):Graph(nodeSize),root(root){}
            inline int GetRoot()const{return root;}
        protected:
            int root;
        };
        //并查集
        class DisjointSet{
        public:
            explicit DisjointSet(int size);
            void Merge(int tarA,int tarB);
            bool Check(int tarA,int tarB);
        private:
            int find(int tar);
            DynamicArray<int> checkSet;
        };

        DisjointSet::DisjointSet(const int size){
            for(int i=size;i;--i)
                checkSet[i]=i;
        }

        void DisjointSet::Merge(int tarA,int tarB){
            checkSet[find(tarA)]=checkSet[find(tarB)];
        }

        int DisjointSet::find(int tar){
            return tar==checkSet[tar]?tar:(checkSet[tar]=find(checkSet[tar]));
        }

        bool DisjointSet::Check(int tarA,int tarB){
            return find(tarA)==find(tarB);
        }

        Graph::Iterator &Graph::Iterator::operator++(){
            nowOrd=nextSet[nowOrd];
            return *this;
        }

        bool Graph::Iterator::operator!=(const Graph::Iterator &tar) const{
            return tar.nowOrd!=this->nowOrd;
        }

        Graph::Edge &Graph::Iterator::operator*() const{
            return edgeSet[nowOrd];
        }

        void Graph::AddEdge(int from,int to,int length){
            edgeSet.Append(Edge{from,to,length});
            nextSet[edgeSet.Length()-1]=headSet[from];
            headSet[from]=edgeSet.Length()-1;
            nodeCnt=std::max(std::max(from,to),nodeCnt);
        }

        Graph::NodeAgency Graph::operator[](int nodeIndex) const{
            if(nodeIndex<=0||nodeIndex>nodeCnt)
                throw std::out_of_range("Index out of range!");
            return NodeAgency{headSet,nextSet,edgeSet,nodeIndex};
        }

    void Graph::AddEdge(const Graph::Edge &edge){
        this->AddEdge(edge.from,edge.to,edge.length);
    }

    Graph::Edge Graph::Edge::operator~() const{
            return Edge{to,from,length};
        }

    bool Graph::Edge::operator>(const Graph::Edge &tar) const{
        return this->length>tar.length;
    }

    template<typename T>
        Vector2<T> Vector2<T>::operator+(const Vector2 &tar) const{
            return Vector2<T>{x+tar.x,y+tar.y};
        }
        template<typename T>
        bool Vector2<T>::operator==(const Vector2 &tar) const{
            return x==tar.x&&y==tar.y;
        }
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
                head=new Node{data, head};
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
        T &LinkedList<T>::Iterator::operator*() const{
            return this->target->data;
        }

        template<typename T>
        typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator++(){
            if(this->ord<this->length){
                ++this->ord;
                this->target=this->target->next;
            }else
                throw std::out_of_range("Iterator out of range!");
            return *this;
        }

        template<typename T>
        bool LinkedList<T>::Iterator::operator!=(const LinkedList::Iterator &itr) const{
            return this->ord!=itr.ord;
        }
        /*单向循环链表*/

        template<typename T>
        typename SingleCircularLinkedList<T>::Node *SingleCircularLinkedList<T>::at(int index) const{
            if(this->length==0)
                return nullptr;
            index=(index%this->length+this->length)%this->length;
            Node *now=this->head;
            while(index--)
                now=now->next;
            return now;
        }

        template<typename T>
        bool SingleCircularLinkedList<T>::Append(const T &data){
            Node *now=new Node{data, nullptr};
            if(!this->length)
                this->head=now;
            else
                this->at(-1)->next=now;
            now->next=this->head;
            ++this->length;
            return true;
        }

        template<typename T>
        bool SingleCircularLinkedList<T>::Insert(int index, const T &data){
            if(this->length==0) {
                this->head = new Node{data, this->head};
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
        T Queue<T>::Top() const{
            return tail->data;
        }

        template<typename T>
        T Queue<T>::Pop(){
            if(length==0)
                throw std::out_of_range("No element remain!");
            T res=tail->data;
            if(length==1){
                delete tail;
                front=tail=nullptr;
            }else{
                tail=tail->prev;
                delete tail->next;
                tail->next=nullptr;
            }
            --length;
            return res;
        }

        template<typename T>
        void Queue<T>::Push(const T &data){
            if(length==0){
                front=tail=new Node{data,nullptr,nullptr};
            }else{
                front->prev=new Node{data,nullptr,front};
                front=front->prev;
            }
            ++length;
        }

        template<typename T>
        Queue<T>::~Queue(){
            Node *now=front,*tmp;
            for(int i=0;i<length;++i){
                tmp=now;
                now=now->next;
                delete tmp;
            }
        }
        template<typename T>
        DynamicArray<T>::DynamicArray(int size):capacity(size),currentSize(0){
            data=new T[capacity]{};
        }
        template<typename T>
        DynamicArray<T>::~DynamicArray(){
            delete[] data;
        }
        template<typename T>
        T &DynamicArray<T>::explore(const int index){
            if(index<0)
                throw std::out_of_range("Index out of range!");
            if(index>=currentSize){
                if(index>=capacity){
                    if(index>LIMIT)
                        throw std::overflow_error("Index overflowed!");
                    capacity=index+(index>>1);
                    T *tmp=new T[capacity]{};
                    std::copy(data,data+currentSize,tmp);
                    delete[] data;
                    data=tmp;
                }
                currentSize=index+1;
            }
            return data[index];
        }

        template<typename T>
        T &DynamicArray<T>::operator[](const int index){
            return explore(index);
        }

        template<typename T>
        void DynamicArray<T>::Append(const T &tar){
            explore(currentSize)=tar;
        }

        template<typename T>
        T &DynamicArray<T>::operator[](int index) const{
            if(index<0||index>=currentSize)
                throw std::out_of_range("Index out of range!");
            return data[index];
        }

        template<typename T>
        using LList=LinkedList<T>;
        template<typename T>
        using SCLList=SingleCircularLinkedList<T>;
    }
}

#endif //SSEDATASTRUCTURE_DATASTRUCTURES_HPP
