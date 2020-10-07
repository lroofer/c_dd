#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Node {
	long int sz = 1, prior;
	Node *l, *r;
	long int val = NULL;
	long int sumic = 0;
	bool Reversed = false;
	Node() : l(nullptr), r(nullptr){}
	Node(long int x) : l(nullptr), r(nullptr), val(x), sumic(x),prior((rand() << 15) + rand()) {}
};

long int getsz(Node* root) {
	if (!root)
		return 0;
	else
		return root->sz;
}
typedef pair<Node*, Node*> Pair;
long int sum(Node* v) { return v ? v->sumic : 0; }
void update(Node *root) {
	long int answer = root->val;
	if (root->l != nullptr)
		answer += sum(root->l);
	if (root->r != nullptr)
		answer += sum(root->r);
	root->sumic = answer;
	if (!root)
		root->sz = NULL;
	else
		root->sz = getsz(root->l) + getsz(root->r) + 1;
}
void merge(Node*& root, Node *l, Node*r) {
	if (!l || !r) {
		return void(root = l ? l : r);
	}
	if (l->prior > r->prior) {
		merge(l->r, l->r, r);
		root = l;
		update(root);
	}
	else {
		merge(r->l, l, r->l);
		root = r;
		update(root);
	}

}
int getkth(Node * root, int k) {
	if (getsz(root->l) > k)
		return getkth(root->l, k);
	else if (getsz(root->l) == k)
		return root->val;
	else
		return getkth(root->r, k - getsz(root->l) - 1);
}
void split(Node*root, Node*&l, Node*&r, long int k) {
	if (!root) {
		l = r = nullptr;
		return;
	}
	if (k <= getsz(root->l)) {
		split(root->l, l, root->l, k);
		r = root;
		update(r);
	}
	else {
		split(root->r, root->r, r, k - getsz(root->l) - 1);
		l = root;
		update(l);
	}
}
Node* tmp1, *tmp2, *tmp3;
void insert(Node*&root, long int x, long int pos) {
	Node* ins = new Node(x);
	split(root, tmp1, tmp2, pos);
	merge(root, tmp1, ins);
	merge(root, root, tmp2);
}
void erase(Node *&root, long int pos) {
	split(root, tmp1, tmp2, pos);
	split(tmp2, tmp2, tmp3, 1);
	merge(root, tmp1, tmp3);

}
void print(Node*& root) {
	if (!root)
		return;
	else {
		print(root->l);
		cout << root->val << " ";
		print(root->r);
	}
}
int translate(char a) {
	if (a == 'x')
		return 1;
	else if (a == 'y')
		return 2;
	else
		return 3;
}
void Reverse(Node*& root, long int A, long int B)
{
	Node *l, *m, *r;
	split(root, l, r, A);
	split(r, m, r, B - A);
	m->Reversed ^= true;
	merge(l, l, m);
	merge(root, l, r);
	return;
}
long int returnSum(Node* root, long int l, long int r) {
	r++;
	Pair rq;
	split(root, rq.first, rq.second, r);
	Pair lq;
	split(rq.first, lq.first, lq.second, l);
	long int res = sum(lq.second);
	merge(rq.first, lq.first, lq.second);
	merge(root, rq.first, rq.second);
	return res;
}
int main() {
	Node* tree = NULL;
	long int n, m;
	vector<long int> answers_list;
	cin >> n >> m;
	for (long int i = 0; i < n; ++i) {
		long int height;
		cin >> height;
		insert(tree, i + 1, height);
	}
	for (long int i = 0; i < m; ++i) {
		int com;
		cin >> com;
		if (com == 1) {
			long int l, r;
			cin >> l >> r;
			l--;
			r--;
			Reverse(tree, l, r);
		}
		else {
			long int l, r;
			cin >> l >> r;
			l--;
			r--;
			long int elem = returnSum(tree, l, r);
			answers_list.push_back(elem);
		}

	}
	for (auto u : answers_list) {
		cout << u << endl;
	}
	return 0;
}
