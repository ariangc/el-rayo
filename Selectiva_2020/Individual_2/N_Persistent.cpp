/*
	N - Kth Number
	Approach: Persistent Segment Tree, Binary Search
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

struct PersistentST{
	int n;
	int OpId = 0;
	vector<int> arr;
	vector<int> L, R;
	vector<int> tree;

	int Op(int a, int b){ return a + b;}

	int new_node(int l, int r){
		L.pb(l); R.pb(r); tree.pb(Op(tree[l], tree[r]));
		return sz(tree) - 1;
	}

	int new_node(int x){
		L.pb(0); R.pb(0); tree.pb(x);
		return sz(tree) - 1;
	}

	int build(int a, int b){
		if(a + 1 == b) return new_node(arr[a]);
		int lch = build(a, (a + b) / 2);
		int rch = build((a + b) / 2, b);
		return new_node(lch, rch);
	}

	int update(int tid, int a, int b, int pos, int x){
		if(a + 1 == b) return new_node(Op(tree[tid], x));
		int mid = (a + b) / 2;
		if(pos < mid){
			int new_left = update(L[tid], a, mid, pos, x);
			return new_node(new_left, R[tid]);
		}
		else{
			int new_right = update(R[tid], mid, b, pos, x);
			return new_node(L[tid], new_right);
		}
	}

	int query(int tid, int a, int b, int l, int r){
		if(b <= l || a >= r) return OpId;
		if(a >= l && b <= r) return tree[tid];
		int lch = query(L[tid], a, (a + b) >> 1, l, r);
		int rch = query(R[tid], (a + b) >> 1, b, l, r);
		return Op(lch, rch);
	}
	
	void clear(){
		tree.clear(); L.clear(); R.clear(); arr.clear();
	}
	
	inline int build(){ n = sz(arr); return build(0, n);}
	inline int update(int root, int pos, int x){ return update(root, 0, n, pos, x);}
	inline int query(int root, int l, int r){ return query(root, 0, n, l, r); }
}st;

const int oo = 1e9;

const int N = 1e5 + 2;
int a[N];

bool check2(int root, int k, int mid){
	int cant = st.query(root, 0, mid + 1);
	return (cant >= k);
}

bool check(vector<ii> &vpos, int x, int l){
	return (vpos[x].ff >= l);
}

int main(){
	fastio;
	int n, q; cin >> n >> q;
	vector<ii> vpos;
	for(int i = 0; i < n; ++ i){
		int x; cin >> x;
		a[i] = x;
		vpos.pb(ii(x, i));
		st.arr.pb(0);
	}
	vpos.pb(ii(oo, oo));
	int root = st.build();
	vector<int> versions;
	versions.pb(root);
	sort(vpos.begin(), vpos.end());
	reverse(vpos.begin(), vpos.end());
	for(int i = 1; i < sz(vpos); ++ i){
		root = st.update(root, vpos[i].ss, 1);
		versions.pb(root);
	}
	while(q --){
		int l, k; cin >> l >> k;
		int low = 0, high = sz(vpos);
		while(high - low > 1){
			int mid = (low + high) / 2;
			if(check(vpos, mid, l)) low = mid;
			else high = mid;
		}
		int curroot = versions[low];
		low = -1, high = sz(vpos) - 1;
		while(high - low > 1){
			int mid = (low + high) / 2;
			if(check2(curroot, k, mid)) high = mid;
			else low = mid;
		}
		cout << a[high] << endl;
	}
	return 0;
}


