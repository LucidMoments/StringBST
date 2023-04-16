
#pragma once

class Tree {
	public:
		virtual void insert(int element) = 0;

		virtual bool search(int element) = 0;

		bool checked_insert(int element) {
			bool found = this->search(element);
			if (!found) {
				this->insert(element);
			}
			return found;
		}

		virtual unsigned int length() = 0;

		virtual ~Tree() = 0;
};

Tree::~Tree() {}

class BST : public Tree {
	private:
		struct Node {
			int element;
			Node *left;
			Node *right;

			Node (int elem) : element(elem),left(nullptr),right(nullptr) {}
		};

		unsigned int elements = 0;
		Node *root = nullptr;

		bool branch_search(Node *node, int element) {
			if (!node) {
				return false;
			} else if (node->element == element) {
				return true;
			} else if (element < node->element) {
				return branch_search(node->left, element);
			} else {
				return branch_search(node->right, element);
			}
		}

		void recursive_delete(Node *n) {
			if (n) {
				recursive_delete(n->left);
				recursive_delete(n->right);
				delete n;
			}
		}

	public:
		void insert(int element) override {
			///	this->elements++;

			Node *y = nullptr;
			Node *x = this->root;
			while (x) {
				y = x;

				if (element < x->element) {
					x = x->left;
				} else {
					x = x->right;
				}
			}

			Node *n = new Node(element);
			if (!y) {
				this->root = n;
			} else if (element < y->element) {
				y->left = n;
			} else {
				y->right = n;
			}
		}

		bool search(int element) override {
			return branch_search(this->root, element);
		}

		unsigned int length() override {
			return this->elements;
		}

		~BST () override {
			recursive_delete(this->root);
		}
};

class AVL : public Tree {
	private:
		struct Node {
			int element;
			int height;
			Node *left;
			Node *right;

			Node (int elem) : element(elem),left(nullptr),right(nullptr) {}
		};

		unsigned int elements = 0;
		Node *root = nullptr;

		Node* inner_insert(Node *x, int element) {
			if (!x) {
				Node *n = new Node(element);
				x = n;
				x->height = 1;
				return x;
			} else {
				if (element < x->element) {
					x->left = inner_insert(x->left, element);
				} else {
					x->right = inner_insert(x->right, element);
				}
			}

			if (x->left && x->right) {
				if (x->left->height < x->right->height) {
					x->height = x->right->height + 1;
				} else {
					x->height = x->left->height + 1;
				}
			} else if (x->left && !x->right) {
				x->height = x->left->height + 1;
			} else if (!x->left && x->right) {
				x->height = x->right->height + 1;
			} else {
				x->height = 0;
			}

			const auto bf = [](Node *n) {
				if (n->left && n->right) {
					return n->left->height - n->right->height;
				} else if (n->left && !n->right) {
					return n->left->height;
				} else if (!n->left && n->right) {
					return -n->right->height;
				} else {
					return 0;
				}
			};

			if (bf(x) == 2 && bf(x->left) == 1) {
				Node *p, *tp;
				p = x;
				tp = p->left;

				p->left = tp->right;
				tp->right = p;

				x = tp;
			} else if (bf(x) == -2 && bf(x->right) == -1) {
				Node *p, *tp;
				p = x;
				tp = p->right;

				p->right = tp->left;
				tp->left = p;

				x = tp;
			} else if (bf(x) == -2 && bf(x->right) == 1) {
				Node *p, *tp, *tp2;
				p = x;
				tp = p->right;
				tp2 = p->right->left;

				p->right = tp2->left;
				tp->left = tp2->right;
				tp2->left = p;
				tp2->right = tp;

				x = tp2;
			} else if (bf(x) == 2 && bf(x->left) == -1) {
				Node *p, *tp, *tp2;
				p = x;
				tp = p->left;
				tp2 = p->left->right;

				p->left = tp2->right;
				tp->right = tp2->left;
				tp2->right = p;
				tp2->left = tp;

				x = tp2;
			}

			return x;
		}

		bool branch_search(Node *node, int element) {
			if (!node) {
				return false;
			} else if (node->element == element) {
				return true;
			} else if (element < node->element) {
				return branch_search(node->left, element);
			} else {
				return branch_search(node->right, element);
			}
		}

		void recursive_delete(Node *n) {
			if (n) {
				recursive_delete(n->left);
				recursive_delete(n->right);
				delete n;
			}
		}

	public:
		void insert(int element) override {
			this->elements++;
			this->root = inner_insert(this->root, element);
		}

		bool search(int element) override {
			return branch_search(this->root, element);
		}

		unsigned int length() override {
			return this->elements;
		}

		~AVL () override {
			recursive_delete(this->root);
		}
};


