/*
	N - Kth Number
	Approach: Policy Based Data Structures, Sortings
*/

//When I wrote this only God and I knew what it is
//Now, only The_Blitz knows...
#pragma GCC optimize ("Ofast,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
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
typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> kset;

const int N = 1e5 + 2;

#define mp make_pair
#define mt(x,y,z) mp(x,mp(y,z))
typedef pair<ll,ii> tri;
#define tm1 ff
#define tm2 ss.ff
#define tm3 ss.ss

vector<tri> v;
kset st;
vector<int> pool[N];
int ans[N];

int main(){
	fastio;
	int n, k; cin >> n >> k;
	FER(i, 0, n){
		int x; cin >> x;
		pool[x].pb(i);
	}
	FER(i, 0, k){
		int l, x; cin >> l >> x;
		v.pb(mt(l, x, i));
	}
	sort(v.begin(), v.end()); reverse(v.begin(), v.end());
	int cur = N - 1;
	FER(i, 0, sz(v)){
		int l = v[i].tm1, x = v[i].tm2, idx = v[i].tm3;
		while(cur >= l) {
			for(auto x: pool[cur]) st.insert(mp(x, cur));
			cur --;
		}
		ans[idx] = (*st.find_by_order(x - 1)).ss;
	}
	FER(i, 0, k) cout << ans[i] << endl;
	return 0;
}


