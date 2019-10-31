#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
typedef pair<int,pi> pj;
void addedge(vector <pair<int,int> > adj[],int u,int v,int wt)
{
	pi pair1;
	adj[u].push_back(make_pair(v,wt));
}
long DIJI(vector <pi > adj[],int v,priority_queue<pj, vector<pj>, greater<pj> > pq,int sink)
{
	int dist[v];
	for(int i=0;i<v;i++)
	dist[i]=100000;
	dist[0]=0;
	int visit[v]={0};
	//printf("\n%d",v);
	pq.push(make_pair(0,make_pair(0,0)));
	for(int i=0;i<v;i++)
	{
		while(visit[pq.top().second.first])
		{
		pq.pop();
		}
		int x = pq.top().first;
		int y = pq.top().second.first;
		pq.pop();
		visit[y]=1;
		for(int j=0;j<adj[y].size();j++)
		{			
			if(!visit[adj[y][j].first])
			{
			if(adj[y][j].second+dist[y]<dist[adj[y][j].first])
			{
			pq.push(make_pair(adj[y][j].second+dist[y],make_pair(adj[y][j].first,y)));
			dist[adj[y][j].first]=adj[y][j].second+dist[y];
			}
			}
		}
	}
	return dist[sink];
}
void addedge_new(vector <pj > plan[],int wt,int i,int u,int v)
{
	plan[i].push_back(make_pair(wt,make_pair(u,v)));
}
void find_planar(vector <pi > adj[],int v,int e,int f)
{
	vector<pj > plan[f];
	int i,j,k,t,l,a,b,flag=0,index=0;
	for(i=0;i<v;i++)
	{
		for(j=0;j<adj[i].size();j++)
		{
			if(adj[i][j].second!=-1)
			{
				addedge_new(plan,adj[i][j].second,index,i,adj[i][j].first);
				adj[i][j].second=-1;
				a=adj[i][j].first;b=i;flag=0;
				while(1)
				{
					k=a;l=b;
					for(t=0;t<adj[k].size();t++)
					{
						if(adj[k][t].first==l)
						{
							if(adj[k][(t+1)%adj[k].size()].second==-1)
							{
								flag=1;
								break;
							}
							addedge_new(plan,adj[k][(t+1)%adj[k].size()].second,index,k,adj[k][(t+1)%adj[k].size()].first);
							adj[k][(t+1)%adj[k].size()].second=-1;
							break;
						}
					}
					if(flag==1)
					{
					index++;
					break;
					}
					a=adj[k][(t+1)%adj[k].size()].first;
					b=k;
				}
			}
		}	
	}
	int c,d,sf=0,sink;
	flag=0;
	vector<pi > fin[f];
	for(i=0;i<f;i++)
	{
		for(j=0;j<plan[i].size();j++)
		{
			a=plan[i][j].second.first;
			b=plan[i][j].second.second;
			if(plan[i][j].first==0 && sf!=1 && b!=0)
			{
				sf=1;
				sink=b;
			}
			for(c=0;c<f;c++)
			{
				for(d=0;d<plan[c].size();d++)
				{
					if(plan[c][d].second.first==b && plan[c][d].second.second==a)
					{
						if(plan[i][j].first!=0)
						addedge(fin,i,c,plan[i][j].first);
						flag=1;
						break;
					}
				}
				if(flag==1)
				{
					flag=0;
					break;
				}
			}
		}
	}
	printf("Dual Graph\n");
	for(i=0;i<f;i++)
	{
		printf("%d : ",i);
		for(j=0;j<fin[i].size();j++)
		{
			printf("%d %d ",fin[i][j].first,fin[i][j].second);
		}
		printf("\n");	
	} 
	priority_queue<pj, vector<pj>, greater<pj> > pq;
	printf("Maximum flow : %d",DIJI(fin,f,pq,sink));
}
int main()
{
	//int v=4,e=6;
	int v=5,e=6;
	int f = e-v+2;
	vector<pi > adj[v];
	priority_queue<pj, vector<pj>, greater<pj> > pq;
	/*addedge(adj,0,1,7);	//To check for Toy graph
	addedge(adj,0,3,5);
	addedge(adj,0,2,0);
	addedge(adj,1,0,7);
	addedge(adj,1,2,9);
	addedge(adj,1,3,3);
	addedge(adj,3,2,2);
	addedge(adj,3,0,5);
	addedge(adj,3,1,3);
	addedge(adj,2,0,0);
	addedge(adj,2,3,2);
	addedge(adj,2,1,9);*/
	
	addedge(adj,0,1,3);
	addedge(adj,0,3,7);
	addedge(adj,0,2,0);
	addedge(adj,1,0,3);
	addedge(adj,1,2,4);
	addedge(adj,2,1,4);
	addedge(adj,2,0,0);
	addedge(adj,2,4,10);
	addedge(adj,3,0,7);
	addedge(adj,3,4,9);
	addedge(adj,4,3,9);
	addedge(adj,4,2,10);
	find_planar(adj,v,e,f);	
}
