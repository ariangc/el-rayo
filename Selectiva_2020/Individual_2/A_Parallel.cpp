/*
	A - Connecting Graph
	Approach: Parallel Binary Search
*/

//When I wrote this only God and I knew what it is
//Now, only The_Blitz knows...
#pragma GCC optimize ("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define sz(x) int(x.size())
#define pb push_back
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> ii;

const int N = 1e5 + 2;

struct UnionFind{
	int p[N];
	int find(int u){ return (p[u] != p[p[u]] ? p[u] = find(p[u]) : p[u]);}
	void merge(int u, int v){
		int pu = find(u), pv = find(v);
		if(pu != pv) p[pu] = pv;
	}
	int connected(int u, int v){ return find(u) == find(v);}
	void init(int n){ for(int i = 1; i <= n; ++ i) p[i] = i; }
}uf;

struct Query{
	int t, u, v;
};

int low[N], high[N];
queue<int> tocheck[N];

int main(){
	fastio;
	int t; cin >> t;
	while(t --){
		int n, m; cin >> n >> m;
		vector<Query> q;
		for(int i = 0; i < m; ++ i){
			int t, u, v; cin >> t >> u >> v;
			q.pb({t, u, v});
		}
		for(int i = 0; i < m; ++ i){
			low[i] = -1, high[i] = i + 1;
		}
		for(int it = 0; it < 20; ++ it){
			for(int i = 0; i < m; ++ i){
				if(q[i].t == 2 && low[i] + 1 != high[i]){
					int mid = (low[i] + high[i]) / 2;
					tocheck[mid].push(i);
				}
			}
			uf.init(n);
			for(int i = 0; i < m; ++ i){
				if(q[i].t == 1) uf.merge(q[i].u, q[i].v);
				while(!tocheck[i].empty()){
					int pos = tocheck[i].front(); tocheck[i].pop();
					if(uf.connected(q[pos].u, q[pos].v)) high[pos] = i;
					else low[pos] = i;
				}
			}
		}
		for(int i = 0; i < m; ++ i){
			if(q[i].t == 1) continue;
			if(high[i] == i + 1) cout << -1 << endl;
			else cout << high[i] + 1 << endl;
		}
	}
	return 0;
}


