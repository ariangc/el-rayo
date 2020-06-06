/*
	K - Cloning
	Approach: Persistent Segment Tree, Math, Hash, Binary Search
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

const int oo = 1e9;
const int N = 1e5 + 2;

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

ll psum[N], psum2[N];
ll hsh[N], pw[N];

#define bas 987625403
const ll Mod = 1e9 + 7;

ll mod_add(ll a, ll b){
	a %= Mod; b %= Mod;
	return (a + b + Mod) % Mod;
}

ll mod_mul(ll a, ll b){
	a %= Mod; b %= Mod;
	return (a * b) % Mod;
}

ll compute_hsh(int pos, ll x){
	ll phsh = (pos ? hsh[pos-1] : 0);
	return mod_add(phsh, pw[x]);
}

int main(){
	fastio;
	pw[0] = 1;
	for(int i = 1; i < N; ++ i) pw[i] = mod_mul(pw[i-1], bas);
	int t; cin >> t;
	while(t --){
		st.clear();
		int n, q; cin >> n >> q;
		vector<int> versions;
		for(int i = 0; i < n; ++ i) st.arr.pb(0);
		int root = st.build();
		versions.pb(root);
		vector<ii> vpos;
		for(int i = 0; i < n; ++ i){
			ll x; cin >> x;
			vpos.pb(ii(x, i));
			psum[i] = x; if(i) psum[i] += psum[i-1];
			psum2[i] = x*x; if(i) psum2[i] += psum2[i-1];
			hsh[i] = compute_hsh(i, x);
		}
		vpos.pb(ii(0, -1));
		sort(vpos.begin(), vpos.end());
		for(ii par: vpos){
			if(par.ss == -1) continue;
			int x = par.ff, pos = par.ss;
			root = st.update(root, pos, 1);
			versions.pb(root);
		}
		while(q --){
			int a, b, c, d; cin >> a >> b >> c >> d;
			a --; b --; c --; d --;
			ll x_sum = psum[b]; if(a) x_sum -= psum[a-1];
			ll x_sum2 = psum2[b]; if(a) x_sum2 -= psum2[a-1];

			ll y_sum = psum[d]; if(c) y_sum -= psum[c-1];
			ll y_sum2 = psum2[d]; if(c) y_sum2 -= psum2[c-1];

			ll x_hsh = hsh[b]; if(a) x_hsh = mod_add(x_hsh, -hsh[a-1]);
			ll y_hsh = hsh[d]; if(c) y_hsh = mod_add(y_hsh, -hsh[c-1]);

			ll dif = x_sum - y_sum, dif2 = x_sum2 - y_sum2;
			if(dif == 0 && dif2 == 0) {
				if(x_hsh != y_hsh) cout << "NO" << endl;
				else cout << "YES" << endl;
			}
			else if(dif == 0 && dif2 != 0) cout << "NO" << endl;
			else if(dif != 0 && dif2 == 0) cout << "NO" << endl;
			else if(dif2 % dif != 0) cout << "NO" << endl;
			else{
				ll sum = dif2 / dif;
				if((sum + dif) % 2 != 0) {
					cout << "NO" << endl;
					continue;
				}
				ll x = (sum + dif) / 2;
				ll y = sum - x;
				//x must be on [a,b]
				int lf, rg;
				lf = lower_bound(vpos.begin(), vpos.end(), ii(x, -1)) - vpos.begin();
				rg = upper_bound(vpos.begin(), vpos.end(), ii(x, oo)) - vpos.begin();
				rg --;
				if(lf > rg){
					cout << "NO" << endl;
					continue;
				}
				int x_cntlf = st.query(versions[lf-1], a, b + 1);
				int x_cntrg = st.query(versions[rg], a, b + 1);


				if(x_cntrg - x_cntlf <= 0){
					cout << "NO" << endl;
					continue;
				}

				lf = lower_bound(vpos.begin(), vpos.end(), ii(y, -1)) - vpos.begin();
				rg = upper_bound(vpos.begin(), vpos.end(), ii(y, oo)) - vpos.begin();
				rg --;

				if(lf > rg){
					cout << "NO" << endl;
					continue;
				}

				int y_cntlf = st.query(versions[lf-1], c, d + 1);
				int y_cntrg = st.query(versions[rg], c, d + 1);


				if(y_cntrg - y_cntlf <= 0){
					cout << "NO" << endl;
					continue;
				}

				lf = max(x_cntlf, y_cntlf);
				rg = min(x_cntrg, y_cntrg);

				x_hsh = mod_add(x_hsh, -pw[x]);
				y_hsh = mod_add(y_hsh, -pw[y]);

				if(lf >= rg || x_hsh != y_hsh) cout << "NO" << endl;
				else cout << "YES" << endl;
			}
		}
	}
	cout.flush();
	return 0;
}


