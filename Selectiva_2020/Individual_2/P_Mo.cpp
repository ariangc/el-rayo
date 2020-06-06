/*
	P - Little Elephant and Array
	Approach: Mo's Algorithm
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

const int N = 1e5 + 2;

vector< array<int, 3> > q;
int a[N], b[N], ret[N];
unordered_map<int,int> f;
int ans;

void rem(int pos){
	if(f[a[pos]] == a[pos]) ans --;
	f[a[pos]] --;
	if(f[a[pos]] == a[pos]) ans ++;
}

void add(int pos){
	if(f[a[pos]] == a[pos]) ans --;
	f[a[pos]] ++;
	if(f[a[pos]] == a[pos]) ans ++;
}

bool cmp(array<int, 3> &x, array<int, 3> &y){
	if(b[x[0]] != b[y[0]])
		return b[x[0]] < b[y[0]];
	if(x[1] != y[1])
		return x[1] < y[1];
	return x[2] < y[2];
}

int main(){
	fastio;
	int n, m; cin >> n >> m;
	int sq = sqrt(n);
	FER(i, 0, n) cin >> a[i], b[i] = i / sq;
	FER(i, 0, m){
		int l, r; cin >> l >> r;
		l --;
		q.pb({l, r, i});
	}
	sort(q.begin(), q.end(), cmp);
	int L = 0, R = 0;
	while(R < n) add(R ++);
	for(auto x: q){
		int l = x[0], r = x[1], idx = x[2];
		while(L < l) rem(L++);
		while(L > l) add(--L);
		while(R < r) add(R++);
		while(R > r) rem(--R);
		ret[idx] = ans;
	}
	FER(i, 0, m) cout << ret[i] << endl;
	return 0;
}


