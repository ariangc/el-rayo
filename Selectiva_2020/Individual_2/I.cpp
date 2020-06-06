/*
	H - Prosjek
	Approach: Binary Search, Math
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
typedef long double ld;

const int N = 3e5 + 2;

ld a[N], b[N];

bool ok(ld x, int n, int k){
	b[0] = a[0] - x;
	for(int i = 1; i < n; ++ i) b[i] = b[i - 1] + a[i] - x;
	ld low = 0;
	ld res = -1e9;
	for(int i = k - 1; i < n; ++ i){
		res = max(res, b[i] - low);
		low = min(low, b[i - k + 1]);
	}
	return (res >= 0);
}

int main(){
	fastio;
	int n, k; cin >> n >> k;
	for(int i = 0; i < n; ++ i) cin >> a[i];
	ld low = 1, high = 1e6;
	for(int it = 0; it < 64; ++ it){
		ld mid = (low + high) * 0.5;
		if(ok(mid, n, k)) low = mid;
		else high = mid;
	}
	cout << fixed << setprecision(8) << low << endl;
	return 0;
}


