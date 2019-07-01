#include <iostream>
#include<iomanip>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <fstream>
#include <string>
#define INF 1e9
using namespace std;

// iPair ==>  Integer Pair 
typedef pair<int, int> iPair;

typedef pair<int, iPair> mPair;

typedef pair<int, pair<int, pair<int, int>>> kPair;
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
	list <int> *uadj;
	// function to add an edge to graph 
	void addEdge(int u, int v, int w);
	//
	void addEdge(int a, int b);
	//
	// prints shortest path from s 
	vector<int> shortestPath(int s);
	int degreeOfCentrality(int src);

	//
	vector<vector<iPair>>getParents(int src);

	int numOfnodesInSP(vector<vector<iPair>> parents, int src, int des, int node);

	pair<vector<int>, vector<int>> numberOfShortestpathes(int s);
	//
//	vector<int> numberOfShortestpathes(int s);
};

// Allocates memory for adjacency list 
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<iPair>[V];
	uadj = new list<int>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
	uadj[u].push_back(v);
	uadj[v].push_back(u);
}
void Graph::addEdge(int a, int b)
{
	uadj[a].push_back(b);
	uadj[b].push_back(a);
}
int Graph::numOfnodesInSP(vector<vector<iPair>> parents, int src, int des, int node)
{
	int counts = 0;
	for (int i = 0; i < parents[des].size(); i++)
	{
		int parent = parents[des][i].second;
		int secParent = parents[des][i].first;
		while (parent != src)
		{
			if (parent == node)
			{
				counts++;
				break;
			}
			parent = secParent;
			secParent = parents[secParent][0].second;
		}
	}
	return counts;
}
vector<vector<iPair>> Graph::getParents(int src) {
	priority_queue < kPair, vector<kPair>, greater<kPair> > nodes_q;

	// Create d and p arrays
	vector<int> d(V, INF);
	vector<vector<iPair>> p(V);

	nodes_q.push(make_pair(0, make_pair(src, make_pair(src, src))));
	int prev_dis = INF;
	while (!nodes_q.empty()) {
		kPair cur_p = nodes_q.top();
		nodes_q.pop();
		int cur_node = cur_p.second.first;
		int cur_parent_node = cur_p.second.second.second;
		int cur_parentOfParent_node = cur_p.second.second.first;
		int cur_dis = cur_p.first;

		/*if (d[cur_node] != INF)
			continue;
			//numberOfShortestpathes(src).second[cur_node] >1
			*/
		if (cur_dis <= d[cur_node])
		{
			d[cur_node] = cur_dis;
			p[cur_node].push_back(make_pair(cur_parentOfParent_node, cur_parent_node));
		}
		// Add the nodes connected to current one
		list< pair<int, int> >::iterator i;
		for (i = adj[cur_node].begin(); i != adj[cur_node].end(); ++i)
		{
			int next_node = (*i).first;
			int weight = (*i).second;
			if (d[next_node] != INF)
				continue;
			nodes_q.push(make_pair((cur_dis + weight), make_pair(next_node, make_pair(cur_parent_node, cur_node))));
		}
		prev_dis = cur_dis;
	}
	return  p;
}
pair<vector<int>, vector<int>> Graph::numberOfShortestpathes(int src)
{
	// Create a priority queue to store vertices that 
   // are being preprocessed.
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

	// Create a vector for distances and initialize all 
	// distances as infinite (INF) 
	vector<int> dist(V, INF);
	vector<int> counter(V, 1);

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
			if ((dist[v] > dist[u] + weight) && (counter[u] > 0))
			{
				// Updating distance of v 
				dist[v] = dist[u] + weight;
				counter[v] = counter[u];
				pq.push(make_pair(dist[v], v));
			}
			else if (dist[v] > dist[u] + weight)
			{
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
			else if (dist[v] == dist[u] + weight)
			{
				counter[v] += 1;
			}
		}
	}

	return make_pair(dist, counter);

}

int Graph::degreeOfCentrality(int src)
{
	return uadj[src].size();
}

vector<int> Graph::shortestPath(int src)
{
	// Create a priority queue to store vertices that 
	// are being preprocessed.
	priority_queue< iPair, vector <iPair>, greater<iPair> > pq;

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



int VectorSum(vector<int> x)
{
	int sum = 0;
	for (int i = 0; i < x.size(); i++)
		sum += x[i];
	return sum;
}

int main()
{
	int V, m;
	int a, b, c;
	int l;
	vector<int> X;
	//cin>>V>>m;

	ifstream myfile;
	string line;

	myfile.open("input.txt", ios::in);

	if (myfile.is_open())
	{
		getline(myfile, line);
		string temp = "";
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ' ') break;
			temp += line[i];
		}
		V = stoi(temp);
		string temp2 = "";
		for (int i = temp.length() + 1; i < line.length(); i++)
		{
			if (line[i] == ' ' || line[i] == 13 || line[i] == '\0') break;
			temp2 += line[i];
		}
		m = stoi(temp2);
	}
	float *C = new float[V];
	Graph g(V);
	vector <vector<int>> ml(V);
	cout << V << " " << m << endl;

	while (getline(myfile, line))
	{
		string temp = "";
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] == ' ') break;
			temp += line[i];
		}
		a = stoi(temp);
		string temp2 = "";

		for (int i = temp.length() + 1; i < line.length(); i++)
		{
			if (line[i] == ' ') break;
			temp2 += line[i];
		}
		b = stoi(temp2);
		string temp3 = "";

		for (int i = temp2.length() + temp.length() + 2; i < line.length(); i++)
		{
			if (line[i] == ' ' || line[i] == 13 || line[i] == '\0') break;
			temp3 += line[i];
		}
		c = stoi(temp3);
		cout << a << " " << b << " " << c << endl;
		ml[a].push_back(b);
		ml[b].push_back(a);
		g.addEdge(a, b, c);
	}

	cout << "///////////////////Degree Centrality//////////////////////" << endl;

	for (int i = 0; i < V; i++)
	{
		l = ml[i].size();
		cout << i << "\t" << l << "\n";
	}

	cout << "///////////////////Closeness//////////////////////" << endl;
	/// this section for closeness

	for (int i = 0; i < V; ++i)
	{
		int sum = 0;
		X = g.shortestPath(i);
		sum = VectorSum(X);
		C[i] = float(V - 1) / sum;
		cout << i << "\t" << setprecision(7) << C[i] << endl;
	}
	cout << "//////////////////////betwenness///////////////////" << endl;
	for (int node = 0; node < V; node++)
	{
		double ans = 0;
		for (int src = 0; src < V - 1; src++)
		{
			vector<vector<iPair>> parents = g.getParents(src);
			for (int des = src + 1; des < V; des++)
			{
				if (node != src && node != des)
					ans += (double)g.numOfnodesInSP(parents, src, des, node) / g.numberOfShortestpathes(src).second[des];
			}
		}
		std::cout << std::setprecision(12) << std::fixed;
		cout << ans << "\n";
	}
	system("pause");
	return 0;
}
