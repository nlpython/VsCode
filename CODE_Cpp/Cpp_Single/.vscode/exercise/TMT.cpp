# include <iostream>
using namespace std;

class Node {
private:
	Node *next;
	int value;
public:
	Node(int v) {
		next = NULL;
		value = v;
	}
	Node* getNext() {
		return next;
	}
	void setNext(Node *node) {
		next = node;
	}
	int& getValue() {
		return value;
	}
};

class List {
private:
	Node *first;
	Node *last;
	int count;
public:
	List() {
		first = NULL;
		last = NULL;
		count = 0;
	}
	Node* getFirst() {
		return first;
	}
	Node* getLast() {
		return last;
	}
	void add(int value) {
		Node* temp = new Node(value);
		Node* tail = new Node(INT_MAX);
        if (count == 0) {
            first = temp;
            last = tail;
            temp->setNext(last);
            count += 1;
        } else {
//        	last->setNext(temp);
//            last = temp;
//            last->setNext(NULL);
			bool sign = false;
			Node *tf = first;
			while (tf != last) {
				if (value == tf->getValue()) {
					sign = true;
					break;
				}
				tf = tf->getNext();
			}
			
			if (!sign) {
	            last->getValue() = value;
	            last->setNext(tail);
	            last = tail;
	            count += 1;
			}
        }
	}
	int size() {
		return count;
	}
	void Display() {
		Node *tf = first;
		while (tf != last) {
			cout << tf->getValue() << " ";
			tf = tf->getNext();
		}
	}
	void order() {
		int len = count;
		Node *p=first, *r=p->getNext();
    	int i = 0, j = 0;
    	int temp;
		for(i=len-1;i>0;i--)
	    {
	        p=first;
	        r=p->getNext();
	        for(j=0;j<i;j++)
	        {
	            if(p->getValue() > r->getValue())
	            {
	                temp=p->getValue();
	                p->getValue() = r->getValue();
	                r->getValue() = temp;
	            }
	            p = p->getNext();
	            r = r->getNext();
	        }
	    }
	}
	List Union(List & other) {
		List temp = List();
		Node *tf1 = first, *tf2 = other.getFirst();
		while (tf1->getNext() != NULL && tf2->getNext() != NULL) {
			if (tf1->getValue() > tf2->getValue()) {
				temp.add(tf2->getValue());
				tf2 = tf2->getNext();
			} else if (tf1->getValue() < tf2->getValue()) {
				temp.add(tf1->getValue());
				tf1 = tf1->getNext();				
			} else {
				temp.add(tf1->getValue());
				tf1 = tf1->getNext();
				tf2 = tf2->getNext();
			}
		}
		while (tf1->getNext() != NULL) {
			temp.add(tf1->getValue());
			tf1 = tf1->getNext();	
		}
		while (tf2->getNext() != NULL) {
			temp.add(tf2->getValue());
			tf2 = tf2->getNext();	
		}
		temp.order();
		return temp;
	}
	List Cross(List & other) {
		List temp = List();
		Node *tf1 = first, *tf2 = other.getFirst();
		while (tf1->getNext() != NULL && tf2->getNext() != NULL) {
			if (tf1->getValue() > tf2->getValue()) {
				tf2 = tf2->getNext();
			} else if (tf1->getValue() < tf2->getValue()) {
				tf1 = tf1->getNext();				
			} else {
				temp.add(tf1->getValue());
				tf1 = tf1->getNext();
				tf2 = tf2->getNext();
			}
		}
		return temp;
	}
	List Sub(List & other) {
		List temp = List();
		Node *tf1 = first, *tf2 = other.getFirst();
		while (tf1->getNext() != NULL && tf2->getNext() != NULL) {
			if (tf1->getValue() > tf2->getValue()) {
				temp.add(tf1->getValue());
				tf1 = tf1->getNext();
				while (tf2->getNext() != NULL && tf2->getValue() < tf1->getValue()) {
                    if (tf2->getValue() == tf1->getValue()) {
                        tf1 = tf1->getNext();
                        tf2 = tf2->getNext();
                        
                    } else {
                        tf2 = tf2->getNext();	
                    }
				}
				if (tf2->getValue() == tf1->getValue()) {
					tf1 = tf1->getNext();
					tf2 = tf2->getNext();
				}
			} else if (tf1->getValue() < tf2->getValue()) {
				temp.add(tf1->getValue());
				tf1 = tf1->getNext();	
				while (tf2->getNext() != NULL && (tf2->getValue() > tf1->getValue() || tf2->getValue() == tf1->getValue())) {
					tf2 = tf2->getNext();	
				}
				if (tf2->getValue() == tf1->getValue()) {
					tf1 = tf1->getNext();
					tf2 = tf2->getNext();
				}			
			} else {
				tf1 = tf1->getNext();
				tf2 = tf2->getNext();
			}
		}
		return temp;
	}
};

int main() {
	List list = List();
	list.add(5);
	list.add(3);
	list.add(19);
	list.add(15);
	list.order();
//	list.Display();
	
	List other = List();
	other.add(5);
	other.add(1);
	other.add(15);
	other.add(16);
	other.order();
	
	List unione = list.Union(other);
	cout << "Union: " << endl;
	unione.Display();
	cout << endl;
	
	List cross = list.Cross(other);
	cout << "Cross: " << endl;
	cross.Display();
	cout << endl;
	
	List sub = list.Sub(other);
	cout << "Sub: " << endl;
	sub.Display();
	cout << endl;

	return 0;
}