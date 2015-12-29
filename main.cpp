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
	CValue& operator = ( const CValue &i );       
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
   	CKey& operator = ( const CKey &i );    
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
	CValue m_value;
	CKey m_key;

	char m_color;

	CNode* m_parent;
	CNode* m_left;
	CNode* m_right;

public:
	char getColor() const {
		return m_color;
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
	CNode* m_root;

public:
	CTable() {
		m_root = NULL;
	}; 

	bool insert(const CKey& key, const CValue& val) {
		CNode* actual_node = m_root;

		while(actual_node != NULL) {
			if (actual_node->getKey() < key) {
				actual_node = actual_node->getLeft();
			} else {
				actual_node = actual_node->getRight();
			}
		}

		CNode* new_node = new CNode();

		return true;
	}

	bool remove(const CKey& key) {
		return true;
	}

	CValue search(const CKey& key) const {
		CNode* actual_node = m_root;

		while (actual_node != NULL) {
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

	CKey key(5);

	CTable* table = new CTable();
	

	if (table->isElem(key)) {
		std::cout << "isElem TRUE" << std::endl;
	} else {
		std::cout << "isElem FALSE" << std::endl;
	}




	return 0;
}
