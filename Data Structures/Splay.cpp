struct item{
	item *child[2], *p;
	bool t;
	int tsz; //Subtree size
	int val, sum; //Data
	void setData(int x){val = sum = x;}
	void clear(){ tsz = -oo;}
};

typedef item * pitem;

struct SplayTree{
	pitem root, nil;
	int a[N], n;

	//Set d child of x into y
	void set(pitem x, pitem y, int d){
		x->child[d] = y;
		y->p = x;
	}
	
	//Get rotation value
	int get(pitem x, pitem y){
		return x->child[0] == y ? 0 : 1;
	}

	//Update operation to maintain node values
	void update(pitem &x){
		x->tsz = x->child[0]->tsz + x->child[1]->tsz + 1;
		x->sum = x->child[0]->sum + x->child[1]->sum + x->val;
	}

	//Rotation operation
	void rotate(pitem &x, int d){
		pitem y = x->child[d], z = x->p;
		set(x, y->child[d^1], d);
		set(y, x, d^1);
		set(z, y, get(z, x));
		update(x), update(y);
	}
		
	//Splay operation
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

	//Gets node on position pos, brings it to root (splay)
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
	
	//Split tree x in t1 and t2
	//t1: l first elements
	//t2: remaining elements
	void split(pitem x, int l, pitem &t1, pitem &t2){
		if(l == 0) t1 = nil, t2 = x;
		else{
			t1 = getnode(x, l - 1);
			t2 = t1->child[1];
			t1->child[1] = t2->p = nil;
			update(t1);
		}
	}

	//Merges two trees x and y
	pitem merge(pitem x, pitem y){
		if(x == nil) return y;
		x = getnode(x, x->tsz - 1);
		set(x, y, 1);
		update(x);
		return x;
	}

	//Inserts an element with value val before position pos
	void insert(int pos, int val){
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

	//Removes (deletes) an element on position pos
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

	//Sum query from l to r
	int query(int l, int r){
		pitem t1, t2, t3;
		split(root, r, t1, t3);
		split(t1, l, t1, t2); //t2 contains values in [l,r]
		int ans = t2->sum;
		root = merge(merge(t1, t2), t3);
		return ans;
	}
	
	//Build operation
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

	//Build operation (call splay.build())
	void build(){
		nil = new item();
		nil->child[0] = nil->child[1] = nil->p = nil;
		nil->val = nil->tsz = nil->sum = 0;
		nil->t = false;
		pitem newRoot = build(0, n);
		root = newRoot;
	}
}st;
