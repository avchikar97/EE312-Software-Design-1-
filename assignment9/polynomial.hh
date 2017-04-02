class Node{
public:
	double value;
	Node* next;
	Node(double v, Node* n);
};

class Poly{
public:
	Poly();
	Poly(const Poly &newobj);
	~Poly();
	Poly operator=(const Poly &newobj);
	Node* getHead();
	void setHead(Node* newhead);
	int getListLength();
	void setListLength(int n);
	void print();
	void append(double v);
private:
	Node* head;
	int ListLength;
};
