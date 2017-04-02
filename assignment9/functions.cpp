#include "functions.hh"

Poly addPolynomials(Poly p1, Poly p2){
	Poly p;
	Node* current1 = p1.getHead();
	Node* current2 = p2.getHead();
	int	length1 = p1.getListLength();
	int	length2 = p2.getListLength();
	if (length1 == length2) {
		while (current1 != nullptr) {
			p.append((current1->value) + (current2->value));
			current1 = current1->next;
			current2 = current2->next;
		}
	}
	else if (length1 > length2) {
		while (length1) {
			if (length1 > length2) {
				p.append((current1->value));
				current1 = current1->next;
			}
			else if (length1 <= length2){
				p.append((current1->value) + (current2->value));
				current1 = current1->next;
				current2 = current2->next;
			}
			length1--;
		}
	}
	else if (length1 < length2) {
		while (length2) {
			if (length1 < length2) {
				p.append((current2->value));
				current2 = current2->next;
			}
			else if (length1 >= length2) {
				p.append((current1->value) + (current2->value));
				current1 = current1->next;
				current2 = current2->next;
			}
			length2--;
		}
	}
	return p;
}


Poly subtractPolynomials(Poly p1, Poly p2){
	Poly p;
	Node* current1 = p1.getHead();
	Node* current2 = p2.getHead();
	int	length1 = p1.getListLength();
	int	length2 = p2.getListLength();
	if (length1 == length2) {
		while (current1 != nullptr) {
			p.append((current1->value) - (current2->value));
			current1 = current1->next;
			current2 = current2->next;
		}
	}
	else if (length1 > length2) {
		while (length1) {
			if (length1 > length2) {
				p.append((current1->value));
				current1 = current1->next;
			}
			else if (length1 == length2) {
				p.append((current1->value) - (current2->value));
				current1 = current1->next;
				current2 = current2->next;
			}
			length1--;
		}
	}
	else if (length1 < length2) {
		while (length2) {
			if (length1 < length2) {
				p.append( 0 - (current2->value));
				current2 = current2->next;
			}
			else if (length1 == length2) {
				p.append((current1->value) - (current2->value));
				current1 = current1->next;
				current2 = current2->next;
			}
			length1--;
		}
	}
	Node* currentnew = p.getHead();			//commented lines remove unnecessary terms preceding the first actual term
	//Node* nextnew = nullptr;
	if ((currentnew->value) == 0) {
		p.setHead(currentnew->next);
		delete currentnew;
	}
	/*for (currentnew = p.getHead(); (currentnew != nullptr) && (currentnew->value == 0); currentnew = nextnew) {
		nextnew = currentnew->next;
		delete currentnew;
	}
	p.setHead(currentnew);*/
	return p;
}

Poly multiplyPolynomials(Poly p1, Poly p2){
	Poly pTotal;
	int length1 = p1.getListLength();
	int length2 = p2.getListLength();
	int append0 = (length1+length2) - 1;	//the listlength of the multiplied polynomial
	append0 = append0 - length2;		//number of 0s to append on first p, subtract 1 to get number to append to second p and so on
	Node* top1 = nullptr;
	Node* top2 = nullptr;
	for (top1 = p1.getHead(); length1 != 0; length1--, top1 = top1->next) {
		Poly p;
		for (top2 = p2.getHead(), length2 = p2.getListLength(); length2 != 0; length2--, top2 = top2->next) {
			p.append((top1->value)*(top2->value));
		}
		for (int i = 0; i < append0; i++) {
			p.append(0);
		}
		append0--;
		pTotal = addPolynomials(pTotal, p);
	}
	return pTotal;
}

