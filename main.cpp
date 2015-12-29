#include <iostream>

#if !__PROGTEST__

class NotFoundException {
public:
	NotFoundException() {}
	friend std::ostream& operator<<(std::ostream& os, const NotFoundException& e ) { os << "Value not found"; return os; }
};

class CValue {
public:    
	CValue();     
	CValue(const CValue &i);
	~CValue();
	CValue& operator = ( const CValue &i );       
	bool operator == ( const CValue &i ) const;
	bool operator != ( const CValue &i ) const;
	bool operator < ( const CValue &i ) const;
	bool operator > ( const CValue &i ) const;
	bool operator >= ( const CValue &i ) const;
	bool operator <= ( const CValue &i ) const;
};

class CKey {
public:
	CKey();     
	CKey(const CKey &i);
    ~CKey();
   	CKey& operator = ( const CKey &i );       
    bool operator == ( const CKey &i ) const;
    bool operator != ( const CKey &i ) const;
    bool operator < ( const CKey &i ) const;
    bool operator > ( const CKey &i ) const;
   	bool operator >= ( const CKey &i ) const;
    bool operator <= ( const CKey &i ) const;
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
	CTable(); 

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

	return 0;
}
