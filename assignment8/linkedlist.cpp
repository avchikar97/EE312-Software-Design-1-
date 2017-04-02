/*******************
Chikarmane, Akaash
avc536
Section #: 16290
EE312 - Assignment 8
*******************/

typedef struct list {
	int value;
	struct list* next;
}Node;

class LinkedList{
public:
	LinkedList() {
		head = nullptr;
		ListLength = 0;
	}
	~LinkedList() {
		Node* current = getHead();		//topold is the head of the old list
		Node* nextfree = nullptr;
		setHead(nullptr);		//sets head to the new reversed list, listlength is the same
		for (current; current != nullptr; current = nextfree) {
			nextfree = current->next;
			delete current;
		}
	}
	void addToListAtPosition(int position, int value) {
		if (position > getListLength()) {		//do nothing if position is more than the length
			return;
		}
		Node* current = getHead();
		Node* x = new Node;
		x->value = value;
		x->next = nullptr;
		if (position == 0) {
			x->next = current;
			setHead(x);
		}
		else {
			for (int s = position - 1; s > 0; s--){		//set current to the node before position to set to
				current = current->next;
			}
			x->next = current->next;
			current->next = x;
		}
		setListLength(getListLength() + 1);
	}
	void addToHead(int value) {
		Node* x = new Node;
		x->value = value;
		x->next = getHead();
		setHead(x);
		setListLength(getListLength() + 1);
	}
	void appendToList(int value) {
		Node* current = getHead();
		Node* x = new Node;
		x->value = value;
		x->next = nullptr;
		for (current = getHead(); current->next != nullptr; current = current->next) {}	//sets current to the last node in the linked list
		current->next = x;
		setListLength(getListLength() + 1);
	}
	void removeFromListAtPosition(int position) {
		if (position > getListLength()) {
			return;
		}
		Node* current = getHead();
		Node* todelete = nullptr;
		if (position == 0) {
			setHead(current->next);
			delete current;
		}
		else {
			for (int s = position - 1; s > 0; s--) {		//set current to the node before position to remove
				current = current->next;
			}
			todelete = current->next;
			current->next = todelete->next;
			delete todelete;
		}
		setListLength(getListLength() - 1);
	}
	void removeFromHead(void) {
		if (getHead() == nullptr) {
			return;
		}
		Node* current = getHead();		//current is used to set head to the next value
		Node* todelete = getHead();		//set todelete to node to be deleted (in this case it's head)
		setHead(current->next);		//sets head regardless of if it's null (only one node) or not
		setListLength(getListLength() - 1);
		delete todelete;		//deletes the head
	}
	void removeFromEnd(void) {
		Node* current = getHead();
		Node* previous;
		if (current->next == nullptr) {	//if there is only one node in the list, setHead to null and delete it
			setHead(current->next);
		}
		else {
			for (current = getHead(); current->next != nullptr; previous = current, current = current->next) {}		//current is the last node, previous is the node before it
			previous->next = nullptr;		//deletes current from the list
		}
		delete current;
		setListLength(getListLength() - 1);
	}
	bool find(int value) {
		Node* current = nullptr;
		for (current = getHead(); current != nullptr; current = current->next) {
			if (current->value == value) {
				return true;
			}
		}
		return false;
	}
	void reverseList(void) {
		Node* currentold = getHead();
		Node* nextold = nullptr, *topold = nullptr;		//both will be used for deletion later
		Node* previousnew = nullptr;		//previousnew will point to the new node after the current new node
		Node* currentnew = new Node;
		currentnew->value = currentold->value;
		currentnew->next = nullptr;		//"tail" is initialized
		for (currentold = (getHead())->next; currentold != nullptr; currentold = currentold->next) {		//continue until all nodes done
			previousnew = currentnew;		//sets previousnew so that currentnew->next can be set
			currentnew = new Node;		//create a new node
			currentnew->value = currentold->value;		//set the value
			currentnew->next = previousnew;
		}
		currentold = getHead();		//topold is the head of the old list
		setHead(currentnew);		//sets head to the new reversed list, listlength is the same
		for (currentold; currentold != nullptr; currentold = nextold) {
			nextold = currentold->next;
			delete currentold;
		}
		return;
	}
	int getListLength(void) {
		return ListLength;
	}
	Node* getHead(void) {
		return head;
	}
	void setListLength(int length) {
		ListLength = length;
	}
	void setHead(Node* newhead) {
		head = newhead;
	}
private:
	Node* head;
	int ListLength;
};