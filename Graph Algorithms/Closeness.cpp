#include <iostream>
#include<iomanip>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#define INF 1e9
using namespace std;
  
// iPair ==>  Integer Pair 
typedef pair<int, int> iPair; 
  
// This class represents a directed graph using 
// adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // In a weighted graph, we need to store vertex 
    // and weight pair for every edge 
    list< pair<int, int> > *adj; 
  
public: 
    Graph(int V);  // Constructor 
  
    // function to add an edge to graph 
    void addEdge(int u, int v, int w); 
  
    // prints shortest path from s 
    vector<int> shortestPath(int s); 

	vector<int> numberOfShortestpathes(int s);
}; 
  
// Allocates memory for adjacency list 
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<iPair> [V]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    adj[u].push_back(make_pair(v, w)); 
    adj[v].push_back(make_pair(u, w)); 
} 
   
vector<int> Graph::shortestPath(int src) 
{ 
    // Create a priority queue to store vertices that 
    // are being preprocessed.
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
  
    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    vector<int> dist(V, INF); 
  
    // Insert source itself in priority queue and initialize 
    // its distance as 0. 
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
  
    /* Looping till priority queue becomes empty (or all 
      distances are not finalized) */
    while (!pq.empty()) 
    { 
        // The first vertex in pair is the minimum distance 
        // vertex, extract it from priority queue. 
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        int u = pq.top().second; 
        pq.pop(); 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            //  If there is shorted path to v through u. 
            if (dist[v] > dist[u] + weight) 
            { 
                // Updating distance of v 
                dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    } 
  
	
	return dist;
} 

vector<int> Graph::numberOfShortestpathes(int src)
{
	 // Create a priority queue to store vertices that 
    // are being preprocessed. 
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
  
    // Create a vector for distances and initialize all 
    // distances as infinite (INF) 
    vector<int> dist(V, INF); 
	vector<int> counter(V,1);
	vector<int> visited(V,0);
  
    // Insert source itself in priority queue and initialize 
    // its distance as 0. 
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
  
    /* Looping till priority queue becomes empty (or all 
      distances are not finalized) */
    while (!pq.empty()) 
    { 
        // The first vertex in pair is the minimum distance 
        // vertex, extract it from priority queue. 
        // vertex label is stored in second of pair (it 
        // has to be done this way to keep the vertices 
        // sorted distance (distance must be first item 
        // in pair) 
        int u = pq.top().second; 
        pq.pop(); 
  
        // 'i' is used to get all adjacent vertices of a vertex 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            // Get vertex label and weight of current adjacent 
            // of u. 
            int v = (*i).first; 
            int weight = (*i).second; 
  
            //  If there is shorted path to v through u. 
            if ((dist[v] > dist[u] + weight)&&(counter[u]>0)) 
            { 
                // Updating distance of v 
                dist[v] = dist[u] + weight; 
				counter[v] = counter[u];
                pq.push(make_pair(dist[v], v)); 
            } 
			else if(dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight; 
                pq.push(make_pair(dist[v], v));
			}
			else if(dist[v] == dist[u] + weight)
			{
				counter[v]+=1;
			}
        } 
    } 
  
	return counter;
	
}

int VectorSum(vector<int> x)
{
	int sum=0;
	for (int i = 0; i < x.size(); i++)
			sum+=x[i];
	return sum;
}

void main ()
{
	int V ,m; 
	int a,b,c;
	vector<int> X;
	cin>>V>>m;
	float *C=new float[V];
    Graph g(V);

	for (int i = 0; i < m; i++)
	{
		cin>>a>>b>>c;
		g.addEdge(a,b,c);
	}

	/// this section for closeness

	for (int i = 0; i < V; ++i) 
	{
		int sum=0;
		X=g.shortestPath(i);
		sum=VectorSum(X);
		C[i]=float(V-1)/sum;
		cout<<setprecision(7)<<C[i]<<endl;
	}
	
}
