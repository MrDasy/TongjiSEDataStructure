// 2052313 周长赫
// T5

#include <iostream>

namespace Sky{
    class Graph{
    public:
        struct Edge{
            int from,to;
            long length;
            inline Edge operator~()const{ //取反边
                return Edge{to,from,length};
            }
        };

    private:
    };

    std::istream &operator>>(std::istream &in,Graph::Edge &tar){
        int f,t,v;
        in>>f>>t>>v;
        tar=Graph::Edge{f,t,v};
        return in;
    }
}