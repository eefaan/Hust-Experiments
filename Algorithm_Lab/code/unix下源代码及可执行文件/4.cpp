/* problem: Floyd-Warshall */
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

//max of int
const int INF=100000;
//max size of graph
const int N=10;

int v_num,e_num;
int Graph[N][N];
int Weight[N][N];
int Pi[N][N];

int initial_graph(string filename){
    //initial here
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            Pi[i][j]=-1;
            if(i==j)Graph[i][j]=0;
            else Graph[i][j]=INF;
        }
    }
    //read file
    ifstream in(filename);
    if(!in){
        cout<<"not exist such file!";
        return -1;
    }
    in>>v_num>>e_num;

    //make Graph
    for(int k=0;k<e_num;k++){
        int i,j,weight;
        in>>i>>j>>weight;
        Graph[i][j]=weight;
    }
    //make Pi
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(i!=j && Graph[i][j]<INF) Pi[i][j]=i;
            else Pi[i][j]=-1;
        }
    }
    return 0;
}

void floyd_warshall(){
    for(int k=0;k<v_num;k++){
        for(int i=0;i<v_num;i++){
            for(int j=0;j<v_num;j++){
                if(Graph[i][j]>Graph[i][k]+Graph[k][j]){
                    Graph[i][j]=Graph[i][k]+Graph[k][j];
                    Pi[i][j]=Pi[k][j];
                }
            }
        }
    }
    return;
}

void print_path(int i,int j){
    if(i==j){
        cout<<i;
    }
    else if(Pi[i][j]==-1){
        cout<<"\nno path from "<<i<<" to "<<j<<endl;
    }
    else{
        print_path(i,Pi[i][j]);
        cout<<"->"<<j;
    }
}

void print_all(){
    int i,j;
    for(i=0;i<v_num;i++){
        for(j=0;j<v_num;j++){
            if(Graph[i][j]!=INF && i!=j){
                cout<<"点"<<i<<"到点"<<j<<"的最短距离为:"<<Graph[i][j];
                cout<<"  路径为:";
                print_path(i,j);
                cout<<endl;
            }
            else if(i!=j){
                cout<<"点"<<i<<"到点"<<j<<"没有可达路径"<<endl;
            }
        }
    }
    return;
}

void test_graph(){
    for(int i=0;i<v_num;i++){
        for(int j=0;j<v_num;j++){
            if (Graph[i][j]==INF)
                cout<<"# ";
            else
                cout<<Graph[i][j]<<' ';
        }
        cout<<'\n';
    }
    cout<<'\n';

    for(int i=0;i<v_num;i++){
        for(int j=0;j<v_num;j++){
            cout<<Pi[i][j]<<' ';
        }
        cout<<'\n';
    }
    return ;
}

int main(void){
    string filename("./graph.txt");
    if (initial_graph(filename)==-1) return 0;
    // test_graph();
    floyd_warshall();
    print_all();
    // test_graph();
    return 0;
}
