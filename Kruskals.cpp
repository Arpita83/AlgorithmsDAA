#include<iostream>
#include<vector>
#include<algorithm>
#include<time.h>

#define edge pair<int,int>

using namespace std;

class graph
{
        vector <pair<int,edge>> G;
        vector <pair<int,edge>> T;
        int *parent;
        int v;
    public:
        graph(int v);
        void addEdge(int u,int v,int w);
        int findSet(int i);
        void unionSet(int u,int v);
        void kruskal();
        void print();    
};

graph::graph(int v)
{
    parent = new int[v];
    int i;
    for(i=0;i<v;i++)
     {
       parent[i]=i; 
     }

    G.clear();
    T.clear(); 
}

void graph::addEdge(int u,int v,int w)
{
  G.push_back(make_pair(w,edge(u,v)));  
}

int graph::findSet(int i)
{
  if(i==parent[i])
    {
      return i;  
    }  
  else
    {
      return findSet(parent[i]);  
    }  
}

void graph::unionSet(int u,int v)
{
  parent[u] = parent[v];  
}

void graph::kruskal()
{
  int i,urep,vrep;
  sort(G.begin(),G.end());

  for(i=0;i<G.size();i++)
    {
      urep = findSet(G[i].second.first);
      vrep = findSet(G[i].second.second);

      if(urep!=vrep)
        {
          T.push_back(G[i]);
          unionSet(urep,vrep);  
        }  
    }  
}

void graph::print()
{
  cout << "Edge  : "<< "Weight" << endl;
  for (int i = 0; i < T.size(); i++)
   {
    cout << T[i].second.first << " - " << T[i].second.second << " : "<< T[i].first<<endl;  
   }
}

int main()
{
  clock_t start,end;

  start = clock();
  graph g(6);
  g.addEdge(0, 1, 4);
  g.addEdge(0, 2, 4);
  g.addEdge(1, 2, 2);
  g.addEdge(1, 0, 4);
  g.addEdge(2, 0, 4);
  g.addEdge(2, 1, 2);
  g.addEdge(2, 3, 1);
  g.addEdge(2, 5, 2);
  g.addEdge(2, 4, 4);
  g.addEdge(3, 2, 3);
  g.addEdge(3, 4, 3);
  g.addEdge(4, 2, 4);
  g.addEdge(4, 3, 3);
  g.addEdge(5, 2, 2);
  g.addEdge(5, 4, 3);
  
  g.kruskal();
  end = clock();
  g.print(); 
  double totaltime = double(end-start) / double (CLOCKS_PER_SEC);
  cout<<endl<<"Execution Time : "<<totaltime<<endl;  
  
  return 0;  
}