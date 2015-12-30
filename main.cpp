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
	bool m_valid;

	CValue m_value;

	CKey m_key;

	char m_color;

	CNode* m_parent;
	CNode* m_left;
	CNode* m_right;
public:
	CNode() {
		m_valid = false;
		m_color = 'R';
		m_parent = NULL;
		m_left = NULL;
		m_right = NULL;
	}

	CNode(const CKey &key, const CValue &value) {
		m_valid = true;
		m_color = 'R';
		m_key = key;
		m_value = value;
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
		m_root = NULL;
	}; 

	bool insert(const CKey& key, const CValue& val) {
		CNode* actual_node = m_root;
		CNode* prev_node = NULL;
		CNode* x = NULL;

		while(actual_node != NULL) {
			prev_node = actual_node;

			std::cout << actual_node->getKey().m_key << std::endl;

			if (actual_node->getKey() < key) {
				actual_node = actual_node->getLeft();
				std::cout << "L" << std::endl;
			} else {
				actual_node = actual_node->getRight();
				std::cout << "R" << std::endl;
			}
		}

		x = new CNode(key, val);
		x->setParent(prev_node);

		if (!prev_node) {
			m_root = x;
			std::cout << "vytvarim root" << std::endl;
		} else {
			if (prev_node->getKey() < x->getKey()) {
				prev_node->setLeftChild(x);

				std::cout << "vlozim do left" << std::endl;
			} else {
				prev_node->setRightChild(x);

				std::cout << "vlozim do right" << std::endl;
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
		printf("provadim R rotaci\n");
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
		printf("provadim L rotaci\n");
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

	bool remove(const CKey& key) {
		return true;
	}

	CValue search(const CKey& key) const {
		CNode* actual_node = m_root;

		while (actual_node != NULL) {
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


		if (actual_node == NULL) {
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
	std::cout << "key2:" << std::endl;
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

	return 0;
}
