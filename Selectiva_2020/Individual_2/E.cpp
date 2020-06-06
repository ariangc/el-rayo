/*
	E - Garland Checking
	Approach: Link Cut Tree (Aplicacion Directa)
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
typedef long double ld;

//Link cut tree

const int N = 1e5 + 2;

struct Node {
    Node *left, *right, *parent;
    bool revert;
    Node() : left(0), right(0), parent(0), revert(false) {}
    bool isRoot() {
        return parent == NULL ||
            (parent->left != this && parent->right != this);
    }
    void push() {
        if (revert) {
            revert = false;
            Node *t = left;
            left = right;
            right = t;
            if (left != NULL) left->revert = !left->revert;
            if (right != NULL) right->revert = !right->revert;
        }
    }
};

struct LinkCutTree{
    Node nos[N];

    LinkCutTree(){
        FER(i,0,N) nos[i] = Node();
    }

    void connect(Node *ch, Node *p, bool isLeftChild) {
        if (ch != NULL) ch->parent = p;
        if (isLeftChild) p->left = ch;
        else p->right = ch;
    }

    void rotate(Node *x){
        Node* p = x->parent;
        Node* g = p->parent;
        bool isRoot = p->isRoot();
        bool leftChild = x == p->left;

        connect(leftChild ? x->right : x->left, p, leftChild);
        connect(p, x, !leftChild);
        if (!isRoot) connect(x, g, p == g->left);
        else x->parent = g;
    }

    void splay(Node *x){
        while (!x->isRoot()) {
            Node *p = x->parent;
            Node *g = p->parent;
            if (!p->isRoot()) g->push();
            p->push();
            x->push();
            if (!p->isRoot()) {
                rotate((x == p->left) == (p == g->left) ? p : x);
            }
            rotate(x);
        }
        x->push();
    }

    Node *expose(Node *x) {
        Node *last = NULL, *y;
        for (y = x; y != NULL; y = y->parent) {
            splay(y);
            y->left = last;
            last = y;
        }
        splay(x);
        return last;
    }

    void makeRoot(Node *x) {
        expose(x);
        x->revert = !x->revert;
    }

    bool connected(Node *x, Node *y) {
        if (x == y) return true;
        expose(x);
        expose(y);
        return x->parent != NULL;
    }

    bool link(Node *x, Node *y) {
        if (connected(x, y)) return false;
        makeRoot(x);
        x->parent = y;
        return true;
    }

    bool cut(Node *x, Node *y) {
        makeRoot(x);
        expose(y);
        if (y->right != x || x->left != NULL || x->right != NULL)
            return false;
        y->right->parent = NULL;
        y->right = NULL;
        return true;
    }
}lct;

int main(){
   fastio;
   int n; cin >> n;
   char c;
   while (cin >> c and c != 'E'){
      int l, r; cin >> l >> r;
      if(l > r) swap(l, r);
      if( c == 'C') lct.link(&lct.nos[l], &lct.nos[r]);
      else if(c == 'D'){
          lct.cut(&lct.nos[l], &lct.nos[r]);
      }
      else{
          cout << ((lct.connected(&lct.nos[l],&lct.nos[r])) ? "YES" : "NO") << endl;
      }
   }
   return 0;
}
