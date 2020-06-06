/*
	C - Archaeology
	Approach: Arboles, LCA
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

vector<ii> adj[N];
int st[N], en[N];
int p[N][18];
ll dist[N];
ll ans = 0;
int gid = 0;

bool above(int u, int v){
	if(u == -1) return true;
	return st[u] <= st[v] && en[u] >= en[v];
}

int lca(int u, int v){
	if(above(u, v)) return u;
	if(above(v, u)) return v;
	for(int i = 17; i >= 0; -- i) if(!above(p[u][i], v)) u = p[u][i];
	return p[u][0];
}

void dfs(int u, int pai = -1){
	st[u] = gid ++; p[u][0] = pai;
	for(int i = 1; i < 18; ++ i) if(p[u][i - 1] != -1) p[u][i] = p[p[u][i - 1]][i - 1];
	for(ii vv: adj[u]){
		int v = vv.ff;
		ll w = vv.ss;
		if(v != pai){
			dist[v] = dist[u] + w;
			dfs(v, u);
		}
	}
	en[u] = gid ++;
}

set<ii> foo;

ll getPath(int u, int v){
	ll res = dist[u] + dist[v] - 2 * dist[lca(u, v)];
	//printf("%d %d %d %lld\n", u, v, lca(u, v), res);
	return res;
}

void remNode(int u){
	ii par = {st[u], u};
	foo.erase(par);
	if(sz(foo) == 0) return;
	if(sz(foo) == 1){
		ans -= 2 * getPath(par.ss, (*foo.begin()).ss);
		return;
	}
	set<ii>::iterator p = foo.lower_bound(par);
	set<ii>::iterator lp, rp;
	if(p == foo.end()) rp = foo.begin(), p --, lp = p;
	else if(p == foo.begin()) rp = p, p = foo.end(), p --, lp = p;
	else rp = p, p --, lp = p;

	ans -= getPath((*lp).ss, par.ss) + getPath((*rp).ss, par.ss) - getPath((*lp).ss, (*rp).ss);
}

void addNode(int u){
	//for(auto x: foo) printf("%d(%d) ", x.ss, x.ff);
	//printf("\n");
	ii par = {st[u], u};
	//printf("Entra: %d(%d)\n", par.ss, par.ff);
	if(foo.empty()){
		foo.insert(par);
		return;
	}
	if(sz(foo) == 1){
		ans += 2 * getPath(par.ss, (*foo.begin()).ss);
		foo.insert(par);
		return;
	}
	set<ii>::iterator p = foo.lower_bound(par);
	set<ii>::iterator lp, rp;
	if(p == foo.end()) rp = foo.begin(), p --, lp = p;
	else if(p == foo.begin()) rp = p, p = foo.end(), p --, lp = p;
	else rp = p, p --, lp = p;
	ans += getPath((*lp).ss, par.ss) + getPath((*rp).ss, par.ss) - getPath((*lp).ss, (*rp).ss);
	foo.insert(par);
}

int main(){
	fastio;
	int n; cin >> n;
	for(int i = 0; i < n - 1; ++ i){
		int a, b, w; cin >> a >> b >> w;
		adj[a].pb({b, w}); adj[b].pb({a, w});
	}
	memset(p, -1, sizeof(p));
	dfs(1);
	//cout << "Construi como un campeon: " << lca(3, 5) << endl;
	int q; cin >> q;
	while(q --){
		char tp; cin >> tp;
		if(tp == '+'){
			int u; cin >> u;
			addNode(u);
		}
		else if(tp == '-'){
			int u; cin >> u;
			remNode(u);
		}
		else cout << ans / 2 << endl;
	}
	return 0;
}

