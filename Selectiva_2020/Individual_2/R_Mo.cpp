/*
	R - Milk Visits
	Approach: Mo's Algorithm on Trees
*/

//When I wrote this only God and I knew what it is
//Now, only The_Blitz knows...
#pragma GCC optimize ("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define sz(x) int(x.size())
#define pb push_back
#define FER(i,a,b) for(int i =int(a); i < int(b); ++ i)
#define IFR(i,a,b) for(ll i = ll(a); i >= ll(b); -- i)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> ii;

const int N = 2e5 + 2;

vector<int> adj[N];
int p[N][18], st[N], en[N], gid;
int flat[N];
int ans[N];

bool test(int a, int b){
	if(a == -1) return true;
	return st[a] <= st[b] && en[a] >= en[b];
}

int lca(int a, int b){
	if(test(a, b)) return a;
	if(test(b, a)) return b;
	for(int i = 17; i >= 0; -- i) if(!test(p[a][i], b)) a = p[a][i];
	return p[a][0];
}

void dfs(int u, int pai = -1){
	p[u][0] = pai; flat[gid] = u; st[u] = gid ++;
	for(int i = 1; i < 18; ++ i) if(p[u][i - 1] != -1) p[u][i] = p[p[u][i - 1]][i - 1];
	for(auto v: adj[u]) if(v != pai) dfs(v, u);
	flat[gid] = u; en[u] = gid ++;
}

int l[N], r[N], ex[N];
int blk[N], cow[N], want[N];
int f[N], vist[N];

void add(int x){
	f[cow[x]] ++;
}

void rem(int x){
	f[cow[x]] --;
}

void touch(int x){
	int node = flat[x];
	if(vist[node]) rem(node);
	else add(node);
	vist[node] ^= 1;
}

bool cmp(int &a, int &b){
	if(blk[l[a]] != blk[l[b]])
		return blk[l[a]] < blk[l[b]];
	return r[a] < r[b];
}

int main(){
	fastio;
	int n, q; cin >> n >> q;
	for(int i = 1; i <= n; ++ i) cin >> cow[i];
	for(int i = 0; i < n - 1; ++ i){
		int a, b; cin >> a >> b;
		adj[a].pb(b); adj[b].pb(a);
	}
	memset(p, -1, sizeof(p));
	dfs(1);
	vector<int> ques;
	for(int i = 0; i < q; ++ i){
		int u, v, w; cin >> u >> v >> w;
		if(st[u] > st[v]) swap(u, v);
		int pai = lca(u, v);
		if(pai == u){
			l[i] = st[u], r[i] = st[v] + 1;
			ex[i] = -1;
		}
		else{
			l[i] = en[u], r[i] = st[v] + 1;
			ex[i] = pai;
		}
		want[i] = w;
		ques.pb(i);
	}
	int sq = sqrt(2 * n);
	for(int i = 0; i < 2 * n; ++ i) blk[i] = i / sq;
	sort(ques.begin(), ques.end(), cmp);
	int L = 0, R = 0;
	while(R < 2 * n) touch(R ++);
	for(int id: ques){
		int lf = l[id], rg = r[id];
		while(L > lf) touch(-- L);
		while(L < lf) touch(L ++);
		while(R < rg) touch(R ++);
		while(R > rg) touch(-- R);
		if(ex[id] != -1) add(ex[id]);
		ans[id] = (f[want[id]] > 0);
		if(ex[id] != -1) rem(ex[id]);
	}
	for(int i = 0; i < q; ++ i) cout << ans[i];
	cout << endl;
	return 0;
}


