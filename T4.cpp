// 2052313 周长赫
// T4

#include <cstdio>
void Prompt(){
    printf("\
**********************************\n\
  T4 N皇后问题 2052313 周长赫\n\
**********************************\n\
\n");
}
void Hang(){
    printf("按任意键继续...\n");
    getchar();
    getchar();
}

int queenNum{};//皇后总数
int *selected;
bool *columnCheck{nullptr},//列试错
    *leftAxisCheck{nullptr},//正对角线试错
    *rightAxisCheck{nullptr};//反对角线试错
bool **check{nullptr};//试错简化数组
int solutionCnt{};
void DataInit(){
    printf("[规则介绍]\n\
现有NxN的棋盘，放入N个皇后，要求所有皇后不在同一行同一列同一斜线上。\n\
请输入皇后的数量：");
    scanf_s("%d",&queenNum);
    columnCheck=new bool[queenNum]{};
    leftAxisCheck=new bool[queenNum<<1]{};
    rightAxisCheck=new bool[queenNum<<1]{};
    check=new bool*[]{columnCheck,leftAxisCheck,rightAxisCheck};
    selected=new int[queenNum]{};
}
void PrintSolution(){
    for(int i=0;i<queenNum;++i){
        for(int j=0;j<selected[i];++j)
            printf("_ ");
        printf("* ");
        for(int j=selected[i]+1;j<queenNum;++j)
            printf("_ ");
        putchar('\n');
    }
}
void Solve(int row){
    if(row==queenNum){
        ++solutionCnt;
        PrintSolution();
        putchar('\n');
        return;
    }
    for(int column=0;column<queenNum;++column){
        int t1=row-column+queenNum,t2=row+column;
        if(!check[0][column]
           &&!check[1][t1]
           &&!check[2][t2]){
            check[0][column]=check[1][t1]=check[2][t2]=true;
            selected[row]=column;
            Solve(row+1);
            check[0][column]=check[1][t1]=check[2][t2]=false;
        }
    }
}
int main(){
    Prompt();
    DataInit();
    printf("解法（_代表空格 *代表皇后）：\n");
    Solve(0);
    printf("解法数量：%d\n",solutionCnt);
    Hang();
    return 0;
}
