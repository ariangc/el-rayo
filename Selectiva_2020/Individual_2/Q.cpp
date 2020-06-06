/*
	Q - Prime Distance On Tree
	Approach: Centroid Decomposition, Brute Force
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

const int N = 1e5 + 5;
struct Centroid{
   set<int> graph[N]; 
   vector<int> cgraph[N];
	int sub[N];
   int cpar[N]; //la raiz tiene padre -2 
	int cent;
	int n;

   void add_edge(int a, int b){
      graph[a].insert(b);
      graph[b].insert(a);
   }

   void dfs(int cur, int parent){
      sub[cur] = 1;
      for(auto to: graph[cur]){
         if(to != parent && cpar[to] == -1){
            dfs(to, cur);
            sub[cur] += sub[to];
         }
      }
   }

   void decompose(int cur, int parent, int sb, int prevc){
      for(auto to: graph[cur]){
         if(to != parent && cpar[to] == -1 && (2 * sub[to] > sb)){
            decompose(to, cur, sb, prevc);
            return;
         }
      }
      cpar[cur] = prevc;
      for(auto to: graph[cur]){
         if(cpar[to] == -1){
            dfs(to, - 1);
            decompose(to, cur, sub[to], cur);
         }
      }
   }
   
   void init(int start){
      for(int i = 0; i < n; ++i) cpar[i] = -1;
      dfs(start, - 1);
      decompose(start, -1, sub[start], -2);
   	for(int i = 0; i < n; ++ i){
			if(cpar[i] == -2) cent = i;
			else cgraph[cpar[i]].pb(i);
		}
	}
}cd;

int is[N];
vector<int> pris;

void sieve(){
	for(int i = 2; i <= N; i ++){
		if(!is[i]){
			pris.pb(i);
			for(int j = 2 * i; j <= N; j += i){
				is[j] = 1;
			}
		}
	}
}

vector<int> toadd;
int f[N], vis[N];
int high;

ll getVal(int x){
	ll ans = 0;
	high = max(high, x);
	for(int i = 0; i < sz(pris); ++ i){
		if(pris[i] < x) continue;
		int need = pris[i] - x;
		if(f[need] == 0) break;
		//printf("Adding %d (%d + %d)\n", f[need], x, need);
		ans += f[need];
	}
	return ans;
}

ll dfs2(int u, int p, int cent, int dist = 1){
	//printf("Standing at %d\n", u);
	ll ans = 0;
	ans += getVal(dist);
	toadd.pb(dist); vis[u] = cent;
	for(auto v: cd.graph[u]){
		if(v == p) continue;
		if(vis[v] != cent) ans += dfs2(v, u, cent, dist + 1);
	}
	return ans;
}

ll dfs(int u){
	//printf("Centroid: %d\n", u);
	for(int i = 0; i <= high; ++ i) f[i] = 0;
	ll ans = 0;
	vector<int> toer;	
	high = 0; f[high] = 1;
	for(auto v: cd.graph[u]){
		toadd.clear();
		//printf("Going to %d\n", v);
		ans += dfs2(v, u, u);
		toer.pb(v);
		for(int x: toadd) f[x] ++;
	}
	for(auto v: toer){
		cd.graph[u].erase(v);
		cd.graph[v].erase(u);
	}
	for(auto v: cd.cgraph[u]) ans += dfs(v);
	return ans;
}

int main(){
	fastio;
	sieve();
	int n; cin >> n;
	cd.n = n;
	for(int i = 0; i < n - 1; ++ i){
		int a, b; cin >> a >> b;
		cd.add_edge(a - 1, b - 1);
	}
	memset(vis, -1, sizeof(vis));
	cd.init(0);
	ll ans = dfs(cd.cent);
	//printf("%lld\n", ans);
	//cout << ans << endl;
	cout << fixed << setprecision(8) << 2.0 * ans / (1LL * n * (n - 1)) << endl;
	return 0;
}


