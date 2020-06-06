/*
	G - Fairy
	Approach: DFS, DP on Trees, Ciclos
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

vector<int> adj[N];
map<ii, int> edgeMap;
int odd[N], even[N];
int edge_odd[N], edge_even[N];
int dfs_time[N];
int total_odd;
int vis[N];

void dfs(int u, int pai = -1, int curtime = 0){
	vis[u] = 1; dfs_time[u] = curtime;
	for(int v: adj[u]){
		if(v == pai) continue;
		if(vis[v] == 0){
			dfs(v, u, curtime + 1);
			odd[u] += odd[v];
			even[u] += even[v];
		}
		else if(vis[v] == 1){
			int eid = edgeMap[ii(min(u, v), max(u, v))];
			int length = dfs_time[u] - dfs_time[v] + 1;
			if(length % 2) odd[u] ++, total_odd ++, edge_odd[eid] = 1;
			else even[u] ++, edge_even[eid] = 1;
		}
		else{
			int length = dfs_time[v] - dfs_time[u] + 1;
			if(length % 2) odd[u] --;
			else even[u] --;
		}
	}
	if(pai != -1){
		int eid = edgeMap[ii(min(u, pai), max(u, pai))];
		edge_odd[eid] = odd[u];
		edge_even[eid] = even[u];
	}
	vis[u] = 2;
}

vector<int> ans;

int main(){
	fastio;
	int n, m; cin >> n >> m;
	for(int i = 0; i < m; ++ i){
		int a, b; cin >> a >> b;
		a --; b -- ;
		if(a > b) swap(a, b);
		edgeMap[ii(a, b)] = i;
		adj[a].pb(b); adj[b].pb(a);
	}
	for(int i = 0; i < n; ++ i){
		if(!vis[i]) dfs(i);
	}
	if(total_odd == 0){
		for(int i =0 ; i < m; ++ i) ans.pb(i + 1);
	}
	else{
		for(int i = 0; i < m; ++ i){
			if(edge_odd[i] == total_odd && edge_even[i] == 0) ans.pb(i + 1);
		}
	}
	cout << sz(ans) << endl;
	for(int i = 0; i < sz(ans); ++ i) cout << ans[i] << " \n"[i==sz(ans)-1];
	return 0;
}


