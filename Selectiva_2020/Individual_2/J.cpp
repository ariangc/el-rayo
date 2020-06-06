/*
	J - Gorgeous Sequence
	Approach: Segment Tree Beats (aplicación directa)
*/

//When I wrote this only God and I knew what it is
//Now, only The_Blitz knows...
#pragma GCC optimize ("Ofast,unroll-loops")
#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>
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

const int N = 1e6 + 2;
const ll oo = INT_MAX;

struct Node{
	int fmx, smx, cmx;
	ll sum;

	Node():fmx(-oo), smx(-oo-1), cmx(0), sum(0){}
	Node(ll x):fmx(x), smx(-oo), cmx(1), sum(x){}

	void merge(Node &u, Node &v){
		cmx = 0;
		sum = u.sum + v.sum;
		fmx = max(u.fmx, v.fmx);
		smx = max(u.smx, v.smx);

		if(fmx == u.fmx) cmx += u.cmx;
		else smx = max(smx, u.fmx);
		if(fmx == v.fmx) cmx += v.cmx;
		else smx = max(smx, v.fmx);
	}
};

struct STBeats{
	int n;
	Node t[4*N];
	int lazy[4*N], arr[N];
	bool isLazy[4*N];

	STBeats(){}

	Node Op(Node &u, Node &v){
		Node res; res.merge(u, v);
		return res;
	}

	void build(int u, int a, int b){
		if(a + 1 == b){
			t[u] = Node(arr[a]);
			return;
		}
		build(u << 1, a, (a + b) >> 1);
		build(u << 1 | 1, (a + b) >> 1, b);
		t[u] = Op(t[u << 1], t[u << 1 | 1]);
	}

	void push(int u, int a, int b){
		if(isLazy[u]){
			if(t[u].fmx <= lazy[u]){
				lazy[u] = 0;
				isLazy[u] = false;
				return;
			}
			t[u].sum -= 1LL * t[u].cmx * (t[u].fmx - lazy[u]);
			t[u].fmx = lazy[u];
			if(a + 1 != b){
				lazy[u << 1] = lazy[u];
				lazy[u << 1 | 1] = lazy[u];
				isLazy[u << 1] = isLazy[u << 1 | 1] = true;
			}
			lazy[u] = 0;
			isLazy[u] = false;
		}
	}

	void update(int u, int a, int b, int l, int r, int x){
		push(u, a, b);
		if(b <= l || a >= r || t[u].fmx <= x) return;
		if(a >= l && b <= r && t[u].smx < x){
			lazy[u] = x;
			isLazy[u] = true;
			push(u, a, b);
			return;
		}
		update(u << 1, a, (a + b) >> 1, l, r, x);
		update(u << 1 | 1, (a + b) >> 1, b, l, r, x);
		t[u] = Op(t[u << 1], t[u << 1 | 1]);
	}

	ll querySum(int u, int a, int b, int l, int r){
		push(u, a, b);
		if(b <= l || a >= r) return 0;
		if(a >= l && b <= r) return t[u].sum;
		ll lch = querySum(u << 1, a, (a + b) >> 1, l, r);
		ll rch = querySum(u << 1 | 1, (a + b) >> 1, b, l, r);
		return lch + rch;
	}

	int queryMax(int u, int a, int b, int l, int r){
		push(u, a, b);
		if(b <= l || a >= r) return -oo;
		if(a >= l && b <= r) {
			return t[u].fmx;
		}
		int lch = queryMax(u << 1, a, (a + b) >> 1, l, r);
		int rch = queryMax(u << 1 | 1, (a + b) >> 1, b, l, r);
		return max(lch, rch);
	}

	inline void clear(){
		FER(i, 0, 4*n) isLazy[i] = false, lazy[i] = 0;
	}

	inline void build(){ build(1, 0, n);}
	inline void update(int l, int r, int x){ update(1, 0, n, l, r, x); }
	inline ll querySum(int l, int r){ return querySum(1, 0, n, l, r); }
	inline int queryMax(int l, int r){ return queryMax(1, 0, n, l, r); }
}st;

int main(){
	int t; scanf("%d", &t);
	while(t --){
		int n, q; scanf("%d%d", &n, &q);
		st.n = n;
		st.clear();
		FER(i, 0, n) scanf("%d", &st.arr[i]);
		st.build();
		FER(i, 0, q){
			int tp; scanf("%d", &tp);
			if(tp == 0){
				int x, y, z; scanf("%d%d%d", &x, &y, &z);
				st.update(x - 1, y, z);
			}
			else if(tp == 1){
				int x, y; scanf("%d%d", &x, &y);
				printf("%d\n", st.queryMax(x - 1, y));
			}
			else{
				int x, y; scanf("%d%d", &x, &y);
				printf("%lld\n", st.querySum(x - 1, y));
			}
			//FER(i, 0, n) printf("%d ", st.queryMax(i, i + 1));
			//printf("\n");
		}
	}
	return 0;
}

