#include <iostream>

#if !__PROGTEST__

class NotFoundException {
public:
	NotFoundException() {}
	friend std::ostream& operator<<(std::ostream& os, const NotFoundException& e ) { os << "Value not found"; return os; }
};

class CValue {
	int m_value;
public:   
	CValue() {
		m_value = 0;
	} 
	CValue(int value) {
		m_value = value;
	}     
	CValue(const CValue &i) {
		m_value = i.m_value;
	}
	~CValue() {
	}
	CValue& operator = ( const CValue &i ) {
		m_value = i.m_value;
		return *this;
	}   
	bool operator == ( const CValue &i ) const {
    	return (i.m_value == this->m_value);
    }
	bool operator != ( const CValue &i ) const {
    	return (i.m_value != this->m_value);
    }
	bool operator < ( const CValue &i ) const {
    	return (i.m_value < this->m_value);
    }
	bool operator > ( const CValue &i ) const {
    	return (i.m_value > this->m_value);
    }
	bool operator >= ( const CValue &i ) const {
    	return (i.m_value >= this->m_value);
    }
	bool operator <= ( const CValue &i ) const {
    	return (i.m_value <= this->m_value);
    }
};

class CKey {
public:
	int m_key;

	CKey() {
		m_key = 0;
	};
	CKey(int key) {
		m_key = key;
	}     
	CKey(const CKey &i) {
		m_key = i.m_key;
	}
    ~CKey() {
    }
   	CKey& operator = ( const CKey &i ) {
   		m_key = i.m_key;
   		return *this;
   	}    
    bool operator == ( const CKey &i ) const {
    	return (i.m_key == this->m_key);
    }
    bool operator != ( const CKey &i ) const {
    	return (i.m_key != this->m_key);
    }
    bool operator < ( const CKey &i ) const {
    	return (i.m_key < this->m_key);
    }
    bool operator > ( const CKey &i ) const {
    	return (i.m_key > this->m_key);
    }
   	bool operator >= ( const CKey &i ) const {
    	return (i.m_key >= this->m_key);
    }
    bool operator <= ( const CKey &i ) const {
    	return (i.m_key <= this->m_key);
    }
};

#endif

class CNode {
	bool m_is_sentinel;
	char m_color;
	CValue m_value;
	CKey m_key;
	CNode* m_parent;
	CNode* m_left;
	CNode* m_right;

	
public:
	CNode() {
		m_is_sentinel = false;
		m_color = 'R';
		m_parent = NULL;
		m_left = NULL;
		m_right = NULL;
	}

	CNode(const CKey &key, const CValue &value) {
		m_is_sentinel = false;
		m_color = 'R';
		m_key = key;
		m_value = value;

		m_left = new CNode();
		m_left->setSentinel();
		m_right = new CNode();
		m_right->setSentinel();
	}

	void setSentinel() {
		m_is_sentinel = true;
		m_color = 'B';
		m_left = NULL;
		m_right = NULL;
	}

	bool isSentinel() {
		return m_is_sentinel;
	}

	void setKey(const CKey &key) {
		m_key = key;
	}

	void setParent (CNode* parent) {
		m_parent = parent;

		return;
	}

	void setLeftChild (CNode* left) {
		m_left = left;

		return;
	}

	void setRightChild (CNode* right) {
		m_right = right;

		return;
	}

	void setColorRed() {
		m_color = 'R';

		return;
	}

	void setColorBlack() {
		m_color = 'B';

		return;
	}

	char getColor() const {
		return m_color;
	}

	char getColorLeftChild () {
		if (!m_left)
			return 'B';

		return m_left->m_color;
	}

	char getColorRightChild () {
		if (!m_right)
			return 'B';

		return m_right->m_color;
	}

	CNode* getParent() const {
		return m_parent;
	}

	CNode* getLeft() const {
		return m_left;
	}

	CNode* getRight() const {
		return m_right;
	}

	CKey getKey() const {
		return m_key;
	} 

	CValue getValue() const {
		return m_value;
	}
};

class CTable {
	

public:
	CNode* m_root;

	CTable() {
		m_root = new CNode();
		m_root->setSentinel();
		//m_sentinel = new CNode();
		//m_sentinel->setColorBlack();
	}; 

	~CTable() {
	}

	bool insert(const CKey& key, const CValue& val) {
		CNode* actual_node = m_root;
		CNode* prev_node = NULL;
		CNode* x = NULL;

		while(!actual_node->isSentinel()) {
			prev_node = actual_node;

			std::cout << actual_node->getKey().m_key << std::endl;

			if (actual_node->getKey() < key) {
				actual_node = actual_node->getLeft();
				//std::cout << "L" << std::endl;
			} else {
				actual_node = actual_node->getRight();
				//std::cout << "R" << std::endl;
			}
		}

		x = new CNode(key, val);
		x->setParent(prev_node);

		if (!prev_node) {
			m_root = x;
			//std::cout << "vytvarim root" << std::endl;
		} else {
			if (prev_node->getKey() < x->getKey()) {
				prev_node->setLeftChild(x);

				//std::cout << "vlozim do left" << std::endl;
			} else {
				prev_node->setRightChild(x);

				//std::cout << "vlozim do right" << std::endl;
			}
		}

		while (x->getParent() && x->getParent()->getParent()) {
			if (x->getParent() == x->getParent()->getParent()->getLeft()) { //pokud je rodic levym potomkem sveho rodice
				CNode* parent = x->getParent();
				CNode* grandparent = parent->getParent();
				CNode* uncle = grandparent->getRight();

				if (parent->getColor() == 'R' && grandparent->getColorRightChild() == 'R') {
					parent->setColorBlack();
					uncle->setColorBlack();
					grandparent->setColorRed();

					x = grandparent;
				} else if (parent->getColor() == 'R' && grandparent->getColorRightChild() == 'B') {
					if (x == parent->getRight()) { //right rotation on parent
						this->rotateLeft(parent, x);

						x = parent;
					} else { //left rotation on grandparent
						grandparent->setColorRed();
						parent->setColorBlack();

						this->rotateRight(grandparent, parent);

						x = parent;
					} 
				} else {
					break;
				}
			} else if (x->getParent() == x->getParent()->getParent()->getRight()) { //pokud je rodic pravym potomkem sveho 
				CNode* parent = x->getParent();
				CNode* grandparent = parent->getParent();
				CNode* uncle = grandparent->getLeft();

				if (parent->getColor() == 'R' && grandparent->getColorLeftChild() == 'R') {
					parent->setColorBlack();
					uncle->setColorBlack();
					grandparent->setColorRed();

					x = grandparent;
				} else if (parent->getColor() == 'R' && grandparent->getColorLeftChild() == 'B') {
					if (x == parent->getLeft()) { //right rotation on parent
						this->rotateRight(parent, x);

						x = parent;
					} else { //left rotation on grandparent
						grandparent->setColorRed();
						parent->setColorBlack();

						this->rotateLeft(grandparent, parent);

						break;
					} 
				} else {
					break;
				}
			}
		} 

		m_root->setColorBlack();

		return true;
	}

	void rotateRight (CNode* x, CNode* y) {
		//printf("provadim R rotaci\n");
		if (x->getParent()) {
			if (x->getParent()->getRight() == x) {
				x->getParent()->setRightChild(y); 
			} else {
				x->getParent()->setLeftChild(y); 
			}
		} else {
			m_root = y;
		}

		y->setParent(x->getParent());
		x->setParent(y);

		x->setLeftChild(y->getRight());
		
		if (y->getRight()) {
			y->getRight()->setParent(x);
		}

		y->setRightChild(x);

		return;
	}

	void rotateLeft (CNode* x, CNode* y) {
		//printf("provadim L rotaci\n");
		if (x->getParent()) {
			if (x->getParent()->getRight() == x) {
				x->getParent()->setRightChild(y); 
			} else {
				x->getParent()->setLeftChild(y); 
			}
		} else {
			m_root = y;
		}

		y->setParent(x->getParent());
		x->setParent(y);

		x->setRightChild(y->getLeft());

		if (y->getLeft()) {
			y->getLeft()->setParent(x);
		}

		y->setLeftChild(x);

		return;
	}

	CNode* treeMinimum (CNode* x) {
		while (!x->getLeft()->isSentinel()){
			x = x->getLeft();
		}

		return x;
	}

	CNode* treeMaximum (CNode* x) {
		while (!x->getRight()->isSentinel()){
			x = x->getRight();
		}

		return x;
	}

	CNode* treePredecessor(CNode* x) {
		if (!x->getLeft()->isSentinel())
			return this->treeMaximum(x->getLeft());

		CNode* y = x->getParent();

		while (!y->isSentinel() &&  x == y->getLeft()) {
			x = y;
			y = y->getParent();
		}

		return y;
	}

	bool remove(const CKey& key) {
		CNode *node_to_delete = m_root;
		CNode *y = NULL, *x = NULL;

		while (!node_to_delete->isSentinel()) {
			if (node_to_delete->getKey() == key)
				break;

			if (node_to_delete->getKey() < key)
				node_to_delete = node_to_delete->getLeft();
			else
				node_to_delete = node_to_delete->getRight();
		}

		if (node_to_delete->isSentinel())
			return false;

		if (node_to_delete->getLeft()->isSentinel() || node_to_delete->getRight()->isSentinel()) {
			y = node_to_delete;
		} else {
			y = this->treePredecessor(node_to_delete);
		}

		if (!y->getLeft()->isSentinel())
			x = y->getLeft();
		else
			x = y->getRight();

		x->setParent(y->getParent());
		
		if (y->getParent() == NULL)
			this->m_root = x;
		else if (y == y->getParent()->getLeft()) {
			y->getParent()->setLeftChild(x);
		} else {
			y->getParent()->setRightChild(x);
		}

		if (y != node_to_delete) {
			node_to_delete->setKey(y->getKey());
			// copy other satellite data
		}

		if (y->getColor() == 'B')
			this->deleteFixUp(x);

		return true;
	}

	void deleteFixUp(CNode* x) {
		while (x != m_root && x->getColor() == 'B') {
			if (x == x->getParent()->getLeft()) {
				/* x is left child of his parent */
				CNode *w = x->getParent()->getRight(); //sibling of x;

				if (w->getColor() == 'R') {
					w->setColorBlack();
					x->getParent()->setColorRed();

					this->rotateLeft(w->getParent(), w);

					w = x->getParent()->getRight();
				}

				if (w->getLeft()->getColor() == 'B' &&  w->getRight()->getColor() == 'B') {
					w->setColorRed();

					x = x->getParent();
				} else if (w->getRight()->getColor() == 'B') {
					w->getLeft()->setColorBlack();
					w->setColorRed();

					this->rotateRight(w, w->getLeft());

					w = x->getParent()->getRight();
				} else {
					if (x->getParent()->getColor() == 'B')
						w->setColorBlack();
					else
						w->setColorRed();

					x->getParent()->setColorBlack();
					w->getRight()->setColorBlack();

					this->rotateLeft(x->getParent(), w);

					x = m_root;
				}

			} else {
				/* x is right child of his parent */
				CNode *w = x->getParent()->getLeft(); //sibling of x;

				if (w->getColor() == 'R') {
					w->setColorBlack();
					x->getParent()->setColorRed();

					this->rotateRight(w->getParent(), w);

					w = x->getParent()->getLeft();
				}

				if (w->getRight()->getColor() == 'B' &&  w->getLeft()->getColor() == 'B') {
					w->setColorRed();

					x = x->getParent();
				} else if (w->getLeft()->getColor() == 'B') {
					w->getRight()->setColorBlack();
					w->setColorRed();

					this->rotateLeft(w, w->getRight());

					w = x->getParent()->getLeft();
				} else {
					if (x->getParent()->getColor() == 'B')
						w->setColorBlack();
					else
						w->setColorRed();

					x->getParent()->setColorBlack();
					w->getLeft()->setColorBlack();

					this->rotateRight(x->getParent(), w);

					x = m_root;
				}
			}
		}

		x->setColorBlack();
	}

	CValue search(const CKey& key) const {
		CNode* actual_node = m_root;

		while (!actual_node->isSentinel()) {
			printf("%d%c\n", actual_node->getKey().m_key, actual_node->getColor());

			if (actual_node->getKey() == key) {
				break;
			}

			if (actual_node->getKey() < key) {
				actual_node = actual_node->getLeft();
			} else {
				actual_node = actual_node->getRight();
			}
		}


		if (actual_node->isSentinel()) {
			throw NotFoundException();
		} else {
			return actual_node->getValue();
		}
	}

	bool isElem(const CKey& key) const {
		try {
			CValue tmp_value = this->search(key);
		}
		catch (...) {
			return false;
		}

		return true;
	}

	CNode * getRoot() const {
		return m_root;
	}
};

int main () {

	CKey key1(10), key2(85), key3(15), key4(70), key5(20), key6(60), key7(30), key8(50), key9(65), key10(80), key11(90), key12(40), key13(5), key14(55);
	CValue value(10);

	CTable* table = new CTable();
	std::cout << std::endl;
	std::cout << "key1:" << std::endl;
	table->insert(key1, value);
	table->search(key1);

	std::cout << std::endl;
	std::cout << "key2:" << std::endl;
	table->insert(key2, value);
	table->search(key2);

	std::cout << std::endl;
	std::cout << "key3:" << std::endl;
	table->insert(key3, value);
	table->search(key3);


	std::cout << std::endl;
	std::cout << "key4:" << std::endl;
	table->insert(key4, value);
	table->search(key4);


	std::cout << std::endl;
	std::cout << "key5:" << std::endl;
	table->insert(key5, value);
	table->search(key5);

	std::cout << std::endl;
	std::cout << "key6:" << std::endl;
	table->insert(key6, value);
	table->search(key6);

	std::cout << std::endl;
	std::cout << "key7:" << std::endl;
	table->insert(key7, value);
	table->search(key7);

	std::cout << std::endl;
	std::cout << "key8:" << std::endl;
	table->insert(key8, value);
	table->search(key8);

	std::cout << "key9:" << std::endl;
	table->insert(key9, value);
	table->search(key9);

	std::cout << "key10:" << std::endl;
	table->insert(key10, value);
	table->search(key10);

	std::cout << "key11:" << std::endl;
	table->insert(key11, value);
	table->search(key11);

	std::cout << "key12:" << std::endl;
	table->insert(key12, value);
	table->search(key12);

	std::cout << "key13:" << std::endl;
	table->insert(key13, value);
	table->search(key13);

	std::cout << "key14:" << std::endl;
	table->insert(key14, value);
	table->search(key14);

	std::cout << std::endl;

	std::cout << "del key11 = 90" << std::endl;
	table->remove(key11);
	


	std::cout << "del key2 = 85" << std::endl;
	table->remove(key2);

	std::cout << "del key7 = 30" << std::endl;
	table->remove(key7);
	
	std::cout << "del key5 = 20" << std::endl;
	table->remove(key5);

	std::cout << "del key4 = 70" << std::endl;
	table->remove(key4);

	std::cout << "del key3 = 15" << std::endl;
	table->remove(key3);

	//pomoc pro lldb
	table->remove(key4);


	return 0;
}
