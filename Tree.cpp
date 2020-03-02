#include "Tree.h"

void Tree::insert(const string& str) {
	if (root == nullptr) {
		root = new Node();
		root->small = str;
		return;
	}
	Node* cur = root;
	Node* par = nullptr;
	//find node to insert to
	while (cur != nullptr) {
		par = cur;
		if (str < cur->small) {
			cur = cur->left;
		}
		else if (str > cur->small) {
			if (cur->large == "" || str < cur->large)
				cur = cur->middle;
			else {
				cur = cur->right;
			}
		}
	}
	cur = par;
	//2 node
	if (cur->large == "") {
		if (cur->small < str) {
			cur->large = str;
		}
		else {
			cur->large = cur->small;
			cur->small = str;
		}
	}
	//3 node
	else {
		split(nullptr, cur, nullptr, str);
	}
}
void Tree::split(Node* l, Node* cur, Node* r, const string& str) {
	//cur is root
	if (cur == nullptr) {
		cur = new Node();
		cur->small = str;
		cur->left = l;
		cur->middle = r;
		l->parent = cur;
		r->parent = cur;
		root = cur;
		return;
	}
	//if no further split is needed
	if (cur->large == "") {
		//insert str into node
		if (str > cur->small) {
			cur->large = str;
			//update child pointers
			cur->right = r;
			r->parent = cur;
		}
		else {
			cur->large = cur->small;
			cur->small = str;
			//update child pointers
			cur->right = cur->middle;
			cur->middle = r;
			r->parent = cur;
		}
		return;
	}
	//splitting
	string middle = str;
	if (middle < cur->small) {
		middle = cur->small;
		cur->small = str;
	}
	else if (middle > cur->large) {
		middle = cur->large;
		cur->large = str;
	}
	//creating new node
	Node* temp = new Node();
	temp->small = cur->large;
	cur->large = "";
	split(cur, cur->parent, temp, middle); 
	if(cur->parent->parent!= nullptr&&cur->parent->large ==""){
		//updating pointers
		Node* par = cur->parent;
		Node* par2 = par->parent;
		if (par2->left == par) {
			if (cur == par->left) {
				par2->middle->left = par->middle;
				par->middle->parent = par2->middle;
				par2->middle->middle = par->right;
				par->right->parent = par2->middle;
				par->middle = temp;
				temp->parent = par->middle;
				par->right = nullptr;
			}
			else if (cur == par->middle) {
				par2->middle->left = temp;
				par2->middle->middle = par->right;
				par->right->parent = par2->middle;
				temp->parent = par2->middle;
				par->right = nullptr;
			}
			else {
				par2->middle->middle = temp;
				par2->middle->left = par->right;
				par->right->parent = par2->middle;
				temp->parent = par2->middle;
				par->right = nullptr;
			}
		}
		else if(par2->middle == par) {
			if (cur == par->left) {
				par2->middle->left = par->middle;
				par->middle->parent = par2->middle;
				par2->middle->middle = par->right;
				par->right->parent = par2->middle;
				par->middle = temp;
				temp->parent = par->middle;
				par->right = nullptr;
			}
			else if (cur == par->middle) {
				par2->middle->left = temp;
				par2->middle->middle = par->right;
				par->right->parent = par2->middle;
				temp->parent = par2->middle->left;
				par->right = nullptr;
			}
			else {
				par2->middle->middle = temp;
				par2->middle->left = par->right;
				par->right->parent = par2->middle;
				temp->parent = par2->middle->middle;
				par->right = nullptr;
			}
		}
	}
}
void Tree::preOrder() const {
	pre(root);
	cout << endl;
}
void Tree::inOrder() const {
	in(root);
	cout << endl;
}
void Tree::postOrder() const {
	post(root);
	cout << endl;
}
void Tree::post(Node* r)const {
	if (r == nullptr)
	{
		return;
	}
	post(r->left);
	post(r->middle);
	cout << r->small << ", ";
	post(r->right);
	if (r->large != "") {
		cout << r->large << ", ";
	}
}
void Tree::in(Node* r)const {
	if (r == nullptr)
	{
		return;
	}
	in(r->left);
	cout << r->small << ", ";
	in(r->middle);
	if (r->large != "") {
		cout << r->large << ", ";
	}
	in(r->right);
}
void Tree::pre(Node* r)const {
	if (r == nullptr)
	{
		return;
	}
	cout << r->small << ", ";
	pre(r->left);
	if (r->large != "") {
		cout << r->large << ", ";
	}
	pre(r->middle);
	pre(r->right);
}
void Tree::remove(const string& str) {
	Node* cur = root;
	//find node to remove
	bool sm = false;
	while (cur != nullptr) {
		if (str == cur->small) {
			sm = true;
			break;
		}
		else if (str == cur->large) {
			break;
		}
		else {
			if (str < cur->small) {
				cur = cur->left;
			}
			else if (str > cur->small) {
				if (cur->large == "" || str < cur->large)
					cur = cur->middle;
				else {
					cur = cur->right;
				}
			}
		}
	}
	if (cur == nullptr) {
		return;
	}
	//small is removed
	if (sm) {
		//leaf node
		if (cur->left == nullptr) {
			//check if node still has data
			if (cur->large == "") {
				if (cur == root) {
					delete root;
					root = nullptr;
				}
				//redistribute or merge
				else {
					cur->small = "";
					emptyNode(cur);
				}
			}
			else {
				cur->small = cur->large;
				cur->large = "";
			}
		}
		//find successor
		else {
			Node* suc = cur->middle;
			while (suc->left != nullptr) {
				suc = suc->left;
			}
			cur->small = suc->small;
			suc->small  = "";
			emptyNode(suc);
		}
	}
	//large is removed
	else {
		//leaf node
		if (cur->left == nullptr) {
			cur->large = "";
		}
		//find successor
		else {
			Node* suc = cur->middle;
			while (suc->left != nullptr) {
				suc = suc->left;
			}
			cur->small = suc->small;
			suc->small = "";
			emptyNode(suc);
		}
	}
}
void Tree::emptyNode(Node* cur) {
	//check redistribute first
	while (cur->small == "") {
		if (hasSpare(cur)) {
			redist(cur);
		}
		else if (cur != root) {
			merge(cur);
		}
		if (cur == root && cur->small == "") {
			if (cur->left->small == "") {
				root = cur->middle;
				delete cur->left;
			}
			else {
				root = cur->left;
				delete cur->middle;
			}
			delete cur;
			cur = nullptr;
			break;
		}
		cur = cur->parent;
	}
}
void Tree::merge(Node* n) {
	Node* par = n->parent;
	if (n == par->left) {
		//par is 2 node
		if (par->large == "") {
			par->middle->large = par->middle->small;
			par->middle->small = par->small;
			par->small = "";
		}
		//implement if par is 3 node later
	}
	else if (n == par->middle) {
		//par is 2 node
		if (par->large == "") {
			par->left->large = par->small;
			par->small = "";
		}
		//implement if par is 3 node later
	}
	else {
		//implement if par is right node later
	}
}
bool Tree::hasSpare(Node* n) {
	if (n->parent) {
		Node* par = n->parent;
		if (par->large != "" || par->left->large != "" || par->middle->large != "") {
			return true;
		}
		else if (par->right) {
			if (par->right->large != "") {
				return true;
			}
		}
	}
	return false;
}
void Tree::redist(Node* n) {
	if (n->parent) {
		Node* par = n->parent;
		//checks each case and updates pointers appropriately
		if (n == par->left) {
			if (par->middle->large != "") {
				n->small = par->small;
				par->small = par->middle->small;
				par->middle->small = par->middle->large;
				par->middle->large = "";
			}
			else if(par->right !=nullptr && par->right->large !="") {
				n->small = par->small;
				par->small = par->middle->small;
				par->middle->small = par->large;
				par->large = par->right->small;
				par->right->small = par->right->large;
				par->right->large = "";
			}
			else if(par->large!= ""){
				n->small = par->small;
				n->large = par->middle->small;
				par->small = par->large;
				par->large = "";
				delete par->middle;
				par->middle = par->right;
				par->right = nullptr;
			}
		}
		else if (n == par->middle) {
			if (par->left->large != "") {
				par->middle->small = par->small;
				par->small = par->left->large;
				par->left->large = "";
			}
			else if(par->right != nullptr && par->right->large != "") {
				par->middle->small = par->large;
				par->large = par->right->small;
				par->right->small = par->right->large;
				par->right->large = "";
			}
			else if (par->large != "") {
				par->left->large = par->small;
				par->small = par->large;
				par->large = "";
				n->small = par->right->small;
				delete par->right;
				par->right = nullptr;
			}
		}
		else {
			if (par->middle->large != "") {
				par->right->small = par->large;
				par->large = par->middle->large;
				par->middle->large = "";
			}
			else if (par->left->large != "") {
				par->right->small = par->large;
				par->large = par->middle->small;
				par->middle->small = par->small;
				par->small = par->left->large;
				par->left->large = "";
			}
			else if (par->large != "") {
				par->middle->large = par->large;
				par->large = "";
				delete par->right;
				par->right = nullptr;
			}
		}
	}
}
bool Tree::search(const string& str) const {
	if (find(root, str) != nullptr) {
		return true;
	}
	return false;
}
Node* Tree::find(Node* r, const string& str)const {
	if (r == nullptr) {
		return nullptr;
	}
	if (str == r->small || str == r->large) {
		return r;
	}
	else if (str < r->small) {
		//cout << r->small;
		return find(r->left, str);
	}
	else if (str > r->small) {
		//cout << r->small;
		if (str < r->large|| r->large == "")
			return find(r->middle, str);
		else if (str > r->large)
			return find(r->right, str);
	}
	return nullptr;
}