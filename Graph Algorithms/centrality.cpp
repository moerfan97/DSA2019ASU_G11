#include <iostream>
#include<iomanip>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

using namespace std;
   
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
	// unweighted gragh for centraility
	list <int> *uadj;
  
public: 
    Graph(int V);  // Constructor 
  
    // function to add an edge to graph 
   
	  void addEdge(int a, int b);
  
	  //degree of centality
	   int degreeOfCentrality(int s);
}; 
  
// Allocates memory for adjacency list 
Graph::Graph(int V) 
{ 
    this->V = V;  
	  uadj =new list<int> [V];
} 
  
void Graph::addEdge(int a, int b)
{
	uadj[a].push_back(b); 
	uadj[b].push_back(a); 
}


int Graph::degreeOfCentrality(int src)
{
	return uadj[src].size();
}

void main ()
{
	int V ,m; 
	int a,b;
	cin>>V>>m;
  Graph g(V);

	//for unweighted graph
	for (int i = 0; i < m; i++)
	{
		cin>>a>>b;
		g.addEdge(a,b);
	}
	/// this section for degree of centrality

	for (int i=0; i < V; i++)
	{
		a=g.degreeOfCentrality(i);
		cout<<i<<"\t"<<a<<"\n";
	}
	
}
