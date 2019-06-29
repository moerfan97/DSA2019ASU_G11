#include <iostream>
#include<iomanip>
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <functional>

using namespace std;
   
int main ()
{
int v,e;
int a,b,c;
cin>>v>>e;

vector <vector<int>> m (v);



for(int i=0;i<e;i++)
{
	cin>>a>>b>>c;
	m[a].push_back(b);
	m[b].push_back(a);
}

for(int i=0;i<v;i++)
{
	cout<<m[i].size()<<"\n";
}
	return 0;
}
