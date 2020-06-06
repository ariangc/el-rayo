/*
	O - The Untended Antiquity
	Approach: Hashing, Brute Force
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
typedef unsigned long long ll;
typedef pair<int, int> ii;

const int N = 2502;

ll hsh[N][N];
map<pair<ii, ii>, ll> val;

int main(){
	fastio;
	mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	ll n, m, q; cin >> n >> m >> q;
	for(int j = 0; j < q; ++ j){
		int tp, a, b, c, d; cin >> tp >> a >> b >> c >> d;
		if(tp == 1){
			ll rnd = rng();
			val[make_pair(ii(a, b), ii(c, d))] = rnd;
			for(int i = a; i <= c; ++ i) hsh[i][b] ^= rnd, hsh[i][d+1] ^= rnd;
		}
		else if(tp == 2){
			ll rnd = val[make_pair(ii(a, b), ii(c, d))];
			for(int i = a; i <= c; ++i) hsh[i][b] ^= rnd, hsh[i][d+1] ^= rnd;
		}
		else{
			ll foo = 0, bar = 0;
			for(int i = 1; i <= b; ++ i) foo ^= hsh[a][i];
			for(int i = 1; i <= d; ++ i) bar ^= hsh[c][i];

			if(foo == bar) cout << "Yes" << endl;
			else cout << "No" << endl;
		}
	}
	return 0;
}


