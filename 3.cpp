//Tiago Menezes
//Pedro Carreiro
//g++ -std=c++17 -Wall -Wextra -O2 new.cpp -lm	

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <regex>
using namespace std;

//-----Input Read-----
int n = 0;
int connections = 0;
int questions = 0;
int s = 0;
int t = 0;
int d = 0;

//-----Questions Answers-----
int qa1 = 0;
int qa2 = 0;
int qa3 = 0;
int qa4 = 0;

//-----Strongly Connected Components-----

//Adjacency Matrix
int adj[1000][1000] = {0};

//Depth First Search Tree And Lowest
int dfs[1000] = {-1};
int low[1000] = {-1};

//Stack For Nodes and Bool To Know If Node Is In Stack
stack<int> stck;
bool inStack[1000] = {false};

//Answers For Strongly Connected Components
vector<vector<int>> ways;

//Counter For DFS And Low
int counter = 0;

//Strongly Connect Component Functions
void sccHelper(int v){
    
    dfs[v] = counter;
    low[v] = counter;
    counter++;
    stck.push(v);
    inStack[v] = true;

    for (int i = 0; i < n; i++)
    {
        if (adj[v][i] > 0)
        {
            if (dfs[i] == -1)
            {   
                sccHelper(i);
                low[v] = min(low[v],low[i]);
            }
            if (inStack[i] == true)
            {
                low[v] = min(low[v],dfs[i]);
            }
        }
    }

    vector<int> w;
    int c = 0;

    if (low[v] == dfs[v] )
    {   
        int k;
        do
        {
            k = stck.top();
            w.push_back(k);
            inStack[k] = false;
            stck.pop();
            c++;
        } while (k != v);
        
        if (w.size() > 1 )
        {
            ways.push_back(w);
            if (int(w.size()) > qa2)
            {
                qa2 = int(w.size());
            }           
        }  

    }
}

void scc(){ 
    //Reset Variables
    ways.clear();
    counter = 0;
    qa1 = 0;
    qa2 = 0;

    //Solve Problem
    for (int i = 0; i < n; i++)
    {
        if (dfs[i] == -1)
        {   
            sccHelper(i);         
        } 
    }
    qa1 = int(ways.size());
}


//-----Kruskal Algorithm (MST)-----

//Structures
class set{
public:
    int parent;
    int rank;
};

class edge{
public:
    int origin;
    int dest;
    int value;

bool operator < (const edge& a) const{
    return (value < a.value);
}
};

vector<set> sets;
vector<edge> edges;

//Find Set Root
int find(int a){

    if (sets.at(a).parent != a)
    {
        sets.at(a).parent = find(sets.at(a).parent);
    }
    return sets.at(a).parent;
    
}

//Link Two Sets
void link(int a, int b){

    if (sets.at(a).rank > sets.at(b).rank)
    {
        sets.at(b).parent = a;
    }

    else
    {
        sets.at(a).parent = b;
    }

    if (sets.at(a).rank == sets.at(b).rank)
    {
        sets.at(b).rank++;
    }

}

void unite(int a, int b){
    link(find(a),find(b));
}

//Make Set For Each Node
void make(int v){

    for (int i = 0; i < v; i++)
    {
        set s;
        s.parent = i;
        s.rank = 0;
        sets.push_back(s);
    }

}

//Check If Node Is In Subgraph
int inSubgraph(int v, int subgraph){
    
    for (int i = 0; i < int(ways.at(subgraph).size()); i++)
    {
        if (ways.at(subgraph).at(i) == v)
        {   
            //In subgraph
            return 1;
        }
    }
    
    //Not In Sub Graph
    return 0;
}

//Create Edges For Subgraph
void createEdges(int subgraph){

    for (int i = 0; i < int(ways.at(subgraph).size()); i++)
    {
        edge ed;
        ed.origin = ways.at(subgraph).at(i);
        for (int j = 0; j < n; j++)
        {
            if (adj[ed.origin][j] > 0 && adj[j][ed.origin] == 0 && inSubgraph(j,subgraph))
            {
                ed.value = adj[ed.origin][j];
                ed.dest = j;
                edges.push_back(ed);
            }
            if (adj[ed.origin][j] == 0 && adj[j][ed.origin] > 0 && inSubgraph(j,subgraph))
            {
                ed.value = adj[j][ed.origin];
                ed.dest = j;
                edges.push_back(ed);
            }
            if (adj[ed.origin][j] > 0 && adj[j][ed.origin] > 0 && inSubgraph(j,subgraph))
            {
                ed.value = min(adj[ed.origin][j],adj[j][ed.origin]);
                ed.dest = j;
                edges.push_back(ed);
            }
            
        }
        
    }

}

//Kruskal Algorithm
void kruskalHelper(){
    int t = 0;
    make(n);
    sort(edges.begin(),edges.end());

    for (int i = 0; i < int(edges.size())-1; i++)
    {
        if (find(edges.at(i).origin) != find(edges.at(i).dest))
        {
            t += edges.at(i).value;
            unite(edges.at(i).origin,edges.at(i).dest);
        }
        
    }
    
    qa4 += t;
    if (t > qa3)
    {
        qa3 = t;
    }
    
}

void kruskal(){
    
    for (int i = 0; i < int(ways.size()); i++)
    {
        edges.clear();
        sets.clear();
        createEdges(i);
        kruskalHelper();
    }
    
}

//-----Main Function And Questions Treatment----

//Questions Treatment
void q1(){
    scc();
    printf("%d\n",qa1);
    qa1 = 0;
    qa2 = 0;
    qa3 = 0;
    qa4 = 0;
    
}
void q2(){
    scc();
    printf("%d %d\n",qa1,qa2);
    qa1 = 0;
    qa2 = 0;
    qa3 = 0;
    qa4 = 0;
}
void q3(){
    scc();
    kruskal();
    printf("%d %d %d\n",qa1,qa2,qa3);
    qa1 = 0;
    qa2 = 0;
    qa3 = 0;
    qa4 = 0;
}
void q4(){
    scc();
    kruskal();
    printf("%d %d %d %d\n",qa1,qa2,qa3,qa4);
    qa1 = 0;
    qa2 = 0;
    qa3 = 0;
    qa4 = 0;
}

//Main Function
int main(){
    int testCases = 0;
    scanf("%d",&testCases);

    for (int i = 0; i < testCases; i++)
    {         
        scanf("%d",&n); scanf("%d",&connections); scanf("%d",&questions);

        for (int k = 0; k < n; k++)
        {
            low[k] = -1;
            dfs[k] = -1;
            inStack[k] = false;
            for (int j = 0; j < n; j++)
            {
                adj[k][j] = 0;
            }
        }

        for (int j = 0; j < connections; j++)
        {
            scanf("%d",&s); scanf("%d",&t); scanf("%d",&d);
            adj[s-1][t-1] = d;
        }

        //CALL SOLVER
        if (questions == 1)
        {
            q1();
        }
        if (questions == 2)
        {
            q2();
        }
        if (questions == 3)
        {
            q3();
        }
        if (questions == 4)
        {
            q4();
        }

    }
    return 0;
}
