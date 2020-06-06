/*
	F - Can you Answer these queries VIII
	Approach: Splay Tree, Math
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
typedef unsigned int ll;
typedef pair<int, int> ii;


const ll oo = 1e9;
const int N = 1e5 + 2;
ll comb[11][11];

struct item{
	item *child[2], *p;
	ll sum[11];
	bool t;
	int tsz; //Subtree size
	ll val; //Data
	void setData(int x){
		val = x;
		for(int i = 0; i <= 10; ++ i) sum[i] = x;
	}
	void clear(){ tsz = -oo;}
};

typedef item * pitem;

struct SplayTree{
	pitem root, nil;
	ll a[N];
	int n;

	void set(pitem x, pitem y, int d){
		x->child[d] = y;
		y->p = x;
	}

	int get(pitem x, pitem y){
		return x->child[0] == y ? 0 : 1;
	}

	void update(pitem &x){
		x->tsz = x->child[0]->tsz + x->child[1]->tsz + 1;
		if(x->child[0] == nil && x->child[1] == nil){
			for(int i = 0; i <= 10; ++ i) x->sum[i] = x->val;
		}
		else if(x->child[0] != nil && x->child[1] == nil){
			ll coef = 1;
			for(int i = 0; i <= 10; ++ i){
				x->sum[i] = x->child[0]->sum[i] + (coef * x->val);
				coef *= (ll)(x->child[0]->tsz + 1LL);
			}
		}
		else if(x->child[0] == nil && x->child[1] != nil){
			for(int i = 0; i <= 10; ++ i){
				ll tot = 0;
				for(int j = i; j >= 0; j--){
					tot += (x->child[1]->sum[j] * comb[i][j]);
				}
				x->sum[i] = x->val + tot;
			}
		}
		else{
			ll coef = 1;
			for(int i = 0; i <= 10; ++ i){
				ll tot = 0, coef2 = 1;
				for(int j = i; j >= 0; -- j){
					ll toadd = x->child[1]->sum[j] * comb[i][j];
					toadd *= coef2;
					tot += toadd;
					coef2 *= (x->child[0]->tsz + 1);
				}
				x->sum[i] = x->child[0]->sum[i] + x->val * coef + tot;
				coef *= (ll)(x->child[0]->tsz + 1);
			}
		}
	}

	void rotate(pitem &x, int d){
		pitem y = x->child[d], z = x->p;
		set(x, y->child[d^1], d);
		set(y, x, d^1);
		set(z, y, get(z, x));
		update(x), update(y);
	}

	void splay(pitem &x){
		while(x->p != nil){
			pitem y = x->p, z = y->p;
			int dy = get(y, x), dz = get(z, y);
			if(z == nil) rotate(y, dy);
			else if(dy == dz) rotate(z, dz), rotate(y, dy);
			else rotate(y, dy), rotate(z, dz);
		}
		update(x);
	}

	pitem getnode(pitem x, int pos){
		while(x->child[0]->tsz != pos){
			if(pos < x->child[0]->tsz) x = x->child[0];
			else{
				pos -= x->child[0]->tsz + 1;
				x = x->child[1];
			}
		}
		splay(x);
		return x;
	}

	void split(pitem x, int l, pitem &t1, pitem &t2){
		if(l == 0) t1 = nil, t2 = x;
		else{
			t1 = getnode(x, l - 1);
			t2 = t1->child[1];
			t1->child[1] = t2->p = nil;
			update(t1);
		}
	}

	pitem merge(pitem x, pitem y){
		if(x == nil) return y;
		x = getnode(x, x->tsz - 1);
		set(x, y, 1);
		update(x);
		return x;
	}

	void insert(int pos, ll val){
		pitem cur = new item();
		cur->setData(val);
		cur->p = nil, cur->t = false, cur->tsz = 1;
		cur->child[0] = cur->child[1] = nil;

		int r = pos;
		if(r == root->tsz or r == 0){
			if(r == 0) root = merge(cur, root);
			else root = merge(root, cur);
			return;
		}

		pitem t1, t2;
		split(root, r, t1, t2);
		root = merge(merge(t1, cur), t2);
	}

	void remove(int pos){
		pitem t1, t2, t3;
		int l = pos, r = pos + 1;
		if(l == 0 or r == root->tsz){
			if(l == 0) split(root, r, t1, t2), root = t2;
			else split(root, l, t1, t2), root = t1;
			return;
		}

		split(root, r, t1, t3);
		split(t1, l, t1, t2);
		root = merge(t1, t3);
		delete t2;
		return;
	}

	ll query(int l, int r, int k){
		pitem t1, t2, t3;
		split(root, r, t1, t3);
		split(t1, l, t1, t2); //t2 contains values in [l,r]
		ll ans = t2->sum[k];
		root = merge(merge(t1, t2), t3);
		return ans;
	}

	pitem build(int l, int r){
		if(l == r) return nil;
		int mid = (l + r) >> 1;
		pitem x = new item();
		x->setData(a[mid]);
		x->p = nil, x->t = false;
		set(x, build(l, mid), 0);
		set(x, build(mid + 1, r), 1);
		update(x);
		return x;
	}

	void build(){
		nil = new item();
		nil->child[0] = nil->child[1] = nil->p = nil;
		nil->val = nil->tsz = 0;
		for(int i = 0; i <= 10; ++ i) nil->sum[i] = 0;
		nil->t = false;
		pitem newRoot = build(0, n);
		root = newRoot;
	}
}st;

int main(){
	fastio;
	for(int i = 0; i <= 10; ++ i) comb[i][0] = comb[i][i] = 1;
	for(int i = 1; i <= 10; ++ i){
		for(int j = 1; j < i; ++ j){
			comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]);
		}
	}
	int n; scanf("%d", &n);
	for(int i = 0; i < n; ++ i){
		scanf("%u", &st.a[i]);
	}
	st.n = n;
	st.build();
	//puts("Construi como un campeon");

	int q; scanf("%d", &q);
	while(q --){
		char tp[3]; scanf("%s", tp);
		if(tp[0] == 'I'){
			int pos; ll val; scanf("%d%u", &pos, &val);
			st.insert(pos, val);
		}
		else if(tp[0] == 'D'){
			int pos; scanf("%d", &pos);
			st.remove(pos);
		}
		else if(tp[0] == 'R'){
			int pos; ll val; scanf("%d %u", &pos, &val);
			st.remove(pos);
			st.insert(pos, val);
		}
		else{
			int l, r, k; scanf("%d%d%d", &l, &r, &k);
			printf("%u\n", st.query(l, r + 1, k));
		}

	}
	return 0;
}


