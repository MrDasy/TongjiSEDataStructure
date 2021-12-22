// 2052313 周长赫
// T3

#include <cstdlib>
#include <functional>
#include <iostream>
#include <stdexcept>
namespace Sky{
    template<typename T>
    struct Vector2{
        T x,y;
        inline Vector2 operator+(const Vector2 &tar)const{
            return Vector2<T>{x+tar.x,y+tar.y};
        }
        inline bool operator==(const Vector2 &tar)const{
            return x==tar.x&&y==tar.y;
        }
    };//二维向量

    template<typename T>
    std::ostream &operator<<(std::ostream &out,const Vector2<T> &data){
        out<<'('<<data.x<<','<<data.y<<')';
        return out;
    }//重载输出

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

    //地图类
    class RoadMap{
    public:
        using Position=Vector2<int>;//位置向量
        static constexpr Position EmptyPosition{-1,-1};

        explicit RoadMap(int size=10);//构造函数 默认大小10
        ~RoadMap();

        inline int &operator[](const Position &pos){
            return board[pos.x][pos.y];
        }
        inline int GetSize()const{return size;}
        inline bool Check(const Position &pos){
            return pos.x>=0&&pos.y>=0&&pos.x<size&&pos.y<size
                && board[pos.x][pos.y]==0;
        }
    private:
        int **board;
        int size;
    };

    RoadMap::RoadMap(int size):size(size){
        board=new int*[size]{};
        for(int i=0;i<size;++i)
            board[i]=new int[size]{};
        for(int i=0;i<size;++i)
            for(int j=0;j<size;++j)
                board[i][j]=rand()%4==0;
        board[0][0]=board[size-1][size-1]=0;
    }

    RoadMap::~RoadMap(){
        for(int i=0;i<size;++i)
            delete[] board[i];
        delete[] board;
    }
}

#include <ctime>
#include <iomanip>
using namespace std;
using RMap=Sky::RoadMap;
using Pos=RMap::Position;
using Queue=Sky::Queue<Pos>;
void Prompt(){
    cout<<"\
**********************************\n\
  T3 迷宫地图 2052313 周长赫\n\
**********************************\n\
    "<<endl;
}
void Hang(){
    //cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<endl<<"按任意键继续..."<<endl;
    cin.get();
}
void ShowMap(RMap *const rmap){
    static char statMatch[]{'_','X','o'};
    cout<<"[当前地图]"<<endl;
    cout<<"（_代表空格 X代表墙壁 o代表选择的路径）"<<endl;
    int size=rmap->GetSize();
    cout<<"    ";
    for(int i=0;i<size;++i)
        cout<<setw(4)<<i<<"列";
    cout<<endl;
    for(int i=0;i<size;++i){
        cout<<setw(2)<<i<<"行";
        for(int j=0;j<size;++j)
            cout<<setw(4)<<statMatch[(*rmap)[Pos{i,j}]]<<"  ";
        cout<<endl;
    }
    cout<<"起点：(0,0); 终点：("<<(size-1)<<','<<(size-1)<<')'<<endl;
}
Pos **FindRoad(RMap *const rmap){
    static Pos movVecs[]{Pos{1,0},Pos{-1,0},Pos{0,1},Pos{0,-1}};
    int size=rmap->GetSize();
    Pos dst{size-1,size-1};
    Pos empty{-1,-1};
    Pos **visited=new Pos*[size];
    for(int i=0;i<size;++i)
        visited[i]=new Pos[size];
    for(int i=0;i<size;++i)
        for(int j=0;j<size;++j)
            visited[i][j]=empty;
    Queue q;
    q.Push(Pos{0,0});
    while(!q.IsEmpty()){
        Pos now=q.Pop();
        if(now==dst)
            return visited;
        for (const Pos &mv : movVecs){
            Pos &&tar=now+mv;
            if(rmap->Check(tar)&&visited[tar.x][tar.y]==empty)
                q.Push(tar),
                visited[tar.x][tar.y]=now;
        }
    }
    return nullptr;
}
void PrintRoute(const Pos now,RMap *const rmap,Pos **visited){
    if(now.x||now.y){
        PrintRoute(visited[now.x][now.y],rmap,visited);
        cout<<"->";
    }
    (*rmap)[now]=2;
    cout<<now;
}
int main(){
    srand(time(0));
    Prompt();
    RMap *rmap;
    while(true){
        rmap=new RMap(7);
        ShowMap(rmap);
        cout<<"是否重新生成地图？(y/N)：";
        if(cin.get()=='y'){
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            continue;
        }
        break;
    }
    Pos **visited;
    if((visited=FindRoad(rmap))){
        cout<<"寻路完毕"<<endl;
        cout<<"路径：";
        PrintRoute(Pos{6,6},rmap,visited);
        cout<<endl;
        ShowMap(rmap);
    }else{
        cout<<"寻路失败，没有通路！"<<endl;
    }
    Hang();
    return 0;
}