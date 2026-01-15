/*
This program demonstrates accessing and modifying a private member variable
of a base class through multiple levels of derived classes using pointers.
*/

                                                /*  This program was written in TURBO CPP  */
#include <iostream.h>
#include <conio.h>

class Parent {
private:
    int x;

public:
    int *p;

    Parent(int y) {
	x = y;
	p = &x; //stores the reference of variable x.
    }

    void display() {
	cout << x;
    }
};

class Child : public Parent {
public:
    int **q; //double pointer to store the ref of pointer p.

    Child(int y) : Parent(y) {
	q = &p; //stores the reference of pointer p.
    }
};

class Child2 : public Child {
public:
    int ***r; //triple pointer to store the ref of pointer q.

    Child2(int y) : Child(y) {
	r = &q; //stores the reference of pointer q.
    }

    void modify(int newVal) {
	***r = newVal; //modifies the value of private variable x using triple pointer. (*** indicates 'value at')
    }
};

int main() {
    int in;
    clrscr();
    Child2 a(10); //initializes private variable x to 10.

    cout << "Before change the value of private variable is: ";
    a.display(); //displays the initial value of x.

    cout << "\nEnter new value: ";
    cin >> in; //modifies the value of private variable x.

    a.modify(in);

    cout << "After changing the value through pointer, the new value is: ";
    a.display(); //displays the modified value of x.
    getch(); 
    return 0;

}
