/*
 ①图定义
 ②表头定义
 ③邻接点定义
 ④边定义
 */

#include "iostream"
using namespace std;

#define MaxVertexNum 10
typedef int Vertex;
typedef int WeightType;
typedef int DataType;

bool Visited[MaxVertexNum]={false};

//边的定义（纯定义数据，而后赋值，非链表）
typedef struct ENode{
    //数据域
    Vertex V1,V2;
    WeightType Weight;
}*Edge;

//邻接顶点的定义（Graph->Nv个头结点连出去的链表，连接的点是与它邻接的顶点）
typedef struct AdjVNode{
    //数据域
    Vertex AdjV;
    WeightType Weight;
    //指针域
    struct AdjVNode *Next;
}*AdjVN;

//表头结点的定义（Graph->Nv条链表的头结点连成一列）
typedef struct VNode{
    //数据域
    DataType Data;
    //指针域
    AdjVN FirstEdge;
}AdjList[MaxVertexNum];

typedef struct GNode{
    int Nv;
    int Ne;
    AdjList G;
}*LGraph;

LGraph BuildGraph();
LGraph CreateGraph(int n);
void InsertGraph(LGraph Graph,Edge E);
void DFS(LGraph Graph,Vertex V);
void Visit(Vertex V);

int main(){
    LGraph Graph=BuildGraph();
    DFS(Graph,2);
}

LGraph BuildGraph(){
    int Nv;
    cout<<"请输入顶点个数"<<endl;
    cin>>Nv;
    LGraph Graph=CreateGraph(Nv);
    
    cout<<"请输入边数"<<endl;
    cin>>Graph->Ne;
    if(Graph->Ne){
        Edge E=new ENode;
        for(int i=0;i<Graph->Ne;i++){
            cout<<"请输入顶点1，顶点2，边权重"<<endl;
            cin>>E->V1>>E->V2>>E->Weight;
            InsertGraph(Graph,E);
        }
    }
    
    return Graph;
}

LGraph CreateGraph(int n){
    LGraph Graph=new GNode;
    Graph->Nv=n;
    Graph->Ne=0;
    
    return Graph;
}

void InsertGraph(LGraph Graph,Edge E){
    AdjVN NewNode=new AdjVNode;
    NewNode->AdjV=E->V2;
    NewNode->Weight=E->Weight;
    
    AdjVN p=Graph->G[E->V1].FirstEdge;//FirstEdge相当于头结点的Next
    NewNode->Next=p;
    p->Next=NewNode;
}

void DFS(LGraph Graph,Vertex V){
    AdjVN P;
    
    Visit(V);
    P=Graph->G[V].FirstEdge;
    for(P;P;P=P->Next){
        if(!Visited[P->AdjV]){
            DFS(Graph, P->AdjV);
        }
    }
}

void Visit(Vertex V){
    cout<<"Vertex "<<V<<"is Visited!!!"<<endl;
    Visited[V]=true;
}
