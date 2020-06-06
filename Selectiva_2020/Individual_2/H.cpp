/*
	H - Dynamic Graph Connectivity
	Approach: SQRT Decomposition, Persistent Union Find
*/

//When I wrote this only God and I knew what it is
//Now, only The_Blitz knows...
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include <bits/stdc++.h>
using namespace std;
#define sz(x) int(x.size())
#define pb push_back
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define ff first
#define ss second
typedef long long ll;
typedef pair<int, int> ii;

const int N = 1e5 + 3;
const int BUF = 5e6 + 2;

struct UFRollback{
	int p[N], rk[N];
	int cnt, val[BUF];
	int *where[BUF];

	void rollback(){
		while(cnt > 0){
			*where[cnt - 1] = val[cnt - 1];
			-- cnt;
		}
	}

	int find(int u){
		return (u == p[u] ? u : find(p[u]));
	}

	void merge(int u, int v){
		u = find(u), v = find(v);
		if(u == v) return;
		if(rk[u] < rk[v]) swap(u, v);
		where[cnt] = &rk[u];
		val[cnt++] = rk[u];
		where[cnt] = &p[v];
		val[cnt++] = p[v];
		assert(cnt <= BUF);
		rk[u] += rk[v];
		p[v] = u;
	}

	int findFast(int u){
		return (u == p[u] ? u : p[u] = findFast(p[u]));
	}

	void mergeFast(int u, int v){
		u = find(u), v = find(v);
		if(u == v) return;
		if(rk[u] < rk[v]) swap(u, v);
		rk[u] += rk[v];
		p[v] = u;
	}

	bool connected(int u, int v){
		return find(u) == find(v);
	}
}uf;

struct Query{ //tp = 0 (add, rem) 1 (conn)
	int tp, u, v, eid;
}q[N];

bool vis[N], color[N];
vector<int> cur;
ii edgeVec[N];
map<ii, int> edgeMap;
int gid = 0;
int block;
int n, m;

void build(int from){
	for(int i = 0; i < n; ++ i){
		uf.p[i] = i, uf.rk[i] = 1;
	}
	for(int i = 0; i < m; ++ i) vis[i] = color[i] = 0;

	for(int i = 0; i < from; ++ i){
		if(!q[i].tp){
			int eid = q[i].eid;
			vis[eid] = 1, color[eid] ^= 1;
		}
	}
	int to = min(m, from + block);
	for(int i = from; i < to; ++ i){
		if(!q[i].tp) vis[q[i].eid] = 0;
	}
	cur.clear();
	uf.cnt = 0;
	for(int i = 0; i < from; ++ i){
		if(!q[i].tp){
			int eid = q[i].eid;
			if(vis[eid] && color[eid]){
				color[eid] = 0;
				uf.mergeFast(q[i].u, q[i].v);
			}
			else if(!vis[eid] && color[eid]){
				color[eid] = 0;
				cur.pb(eid);
			}
		}
	}
}

int main(){
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++ i){
		char tp[5]; int u, v;
		scanf("%s%d%d", tp, &u, &v);
		u --; v --;
		if(u > v) swap(u, v);
		ii edge = ii(u, v);
		if(!edgeMap.count(edge)){
			edgeVec[gid] = edge;
			edgeMap[edge] = gid ++;
		}
		int tipo;
		if(tp[0] != 'c') tipo = 0;
		else tipo = 1;
		int eid = edgeMap[edge];
		q[i] = {tipo, u, v, eid};
	}
	block = 400;
	for(int i = 0; i < m; ++ i){
		if(i % block == 0) build(i);
		int u = q[i].u, v = q[i].v;
		if(!q[i].tp){
			uf.rollback();
			int eid = q[i].eid;
			auto it = find(cur.begin(), cur.end(), eid);
			if(it == cur.end()) cur.pb(eid);
			else cur.erase(it);
		}
		else{
			for(int eid: cur) uf.merge(edgeVec[eid].ff, edgeVec[eid].ss);
			int res = uf.connected(u, v);
			if(res) printf("YES\n");
			else printf("NO\n");
		}
	}
	return 0;
}


