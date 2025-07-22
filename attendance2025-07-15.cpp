#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

/*
Write the implementation for two classes Base and Derived.  
Derived inherits from Base and the classes have two member functions: 
redefinable and overridable.  Both functions return the name of the class as a string; 
however, the derived class redefines redefinable and overrides overridable.

Hint: one member function should be virtual and one should not.
Hint: your functions should be const. Try it without const and see what happens
*/

#include <iostream>
#include <string>
using namespace std;

class Base {
public:
  virtual ~Base() {} // recommended
  
  string redefinable() const {
    return "Base";
  }

  virtual string overridable() const {
    return "Base";
  }
};

class Derived : public Base {
public:
  virtual ~Derived() {} // recommended
  
  string redefinable() const {
    return "Derived";
  }

  string overridable() const override {
    return "Derived";
  }
};

void use_base(const Base & b) {
  cout << b.redefinable() << " " << b.overridable() << endl;
}

void use_derived(const Derived & d) {
  cout << d.redefinable() << " " << d.overridable() << endl;
}

void test_part1() {
  Base b;
  Derived d;

  use_base(b); // prints "Base Base"
  use_base(d); // prints "Base Derived"
  use_derived(d);  // prints "Derived Derived"
}

/*
Given the implementation for the class ChessPiece, fill in the implementation for the derived classes Bishop and Rook.

Provide implementations for isLegalMove in the derived classes. A bishop can move along diagonals [ https://en.wikipedia.org/wiki/Bishop_(chess) ] and a rook can move along rows and columns [ https://en.wikipedia.org/wiki/Rook_(chess) ].  You only need to check the given cell against the piece’s movement rules. Also add constructors and destructors.
*/

#include <iostream>
using namespace std;

struct Cell {
  int row, col;
};

class ChessPiece {
public:
  ChessPiece(const Cell & _cell): cell(_cell) {}
  virtual ~ChessPiece() {} // recommended
  const Cell & getCell() const { return cell; }
  bool moveIfLegal(const Cell & other_cell) {
    if (isLegalMove(other_cell)) {
      cell = other_cell;
      return true;
    } else {
      return false;
    }
  }
private:
  virtual bool isLegalMove(const Cell & other_cell) const = 0;
  Cell cell;
};

class Bishop : public ChessPiece {
public:
 virtual ~Bishop() {};
 Bishop(const Cell & _cell): ChessPiece(_cell) {}

private:
 bool isLegalMove(const Cell &other_cell) const override {
    return abs(this->getCell().row - other_cell.row)
        == abs(this->getCell().col - other_cell.col);
 }
};

class Rook : public ChessPiece {
public:
 virtual ~Rook() {};
 Rook(const Cell & _cell): ChessPiece(_cell) {}

private:
 bool isLegalMove(const Cell &other_cell) const override {
    return (this->getCell().row == other_cell.row) 
        != (this->getCell().col == other_cell.col);
 }
};

void try_move(ChessPiece & p, const Cell & c) {
  if (p.moveIfLegal(c)) {
    cout << "move was legal, now at: ";
  } else {
    cout << "move was not legal, now at: ";
  }
  cout << p.getCell().row << "," << p.getCell().col << endl;
}

void test_part2() {
  Bishop b({0, 0});
  cout << "moving bishop:" << endl;
  try_move(b, {0, 4}); // at 0,0 (not legal)
  try_move(b, {4, 4}); // at 4,4 (legal)
  try_move(b, {5, 3}); // at 5,3 (legal)

  Rook r({0, 0});
  cout << "moving rook:" << endl;
  try_move(r, {4, 4}); // at 0,0 (not legal)
  try_move(r, {0, 3}); // at 0,3 (legal)
  try_move(r, {5, 3}); // at 5,3 (legal)
}

/*
 * Wraparoundint is a class which stores a single value and a wraparound_ceiling parameter. 
 * This value can never go below 0 or up to the wraparound ceiling value. 
 * Example: If the int's value is 4, and the wraparound value is 5, then
 * adding 1 to the Wraparoundint makes it fall back down to 0 
 * Example: If the int's value is 4, and the wraparound value is 5, then adding 3 will make it wrap back around to 2
 * Essentially, whenever the value is set, the mod function is applied to wrap it back around. 
 * The mod function in C++ is %
 *
 * Implement the operators declared in the WraparoundInt class.
 * operator<< and operator+ are already done for you.
 */

#include <iostream>
using namespace std;

class WraparoundInt {
public:
  WraparoundInt(int value, int wraparound_ceiling);

  friend ostream &operator<<(ostream &, const WraparoundInt &);
  WraparoundInt operator+(const WraparoundInt &other) const;

  // compare just the values, not the wraparound_ceiling
  bool operator==(const WraparoundInt &other) const;
  WraparoundInt &operator+=(const WraparoundInt &other);
  // throw out of range exception if i is not equal to 0
  int operator[](const int i) const;
  // increment operator
  WraparoundInt & operator++();
  WraparoundInt operator++(int);
  // multiplication
  friend WraparoundInt operator*(int i, WraparoundInt wi);

private:
  int value;
  const int wraparound_ceiling;
};

WraparoundInt::WraparoundInt(int _value, int _wraparound_ceiling)
    : value(_value % _wraparound_ceiling),
      wraparound_ceiling(_wraparound_ceiling) {}

ostream &operator<<(ostream &os, const WraparoundInt &wi) {
  return (os << wi.value);
}

WraparoundInt WraparoundInt::operator+(const WraparoundInt &other) const {
  return WraparoundInt(value + other.value, wraparound_ceiling);
}

// compare just the values, not the wraparound_ceiling
bool WraparoundInt::operator==(const WraparoundInt &other) const {
    return this->value == other.value;
}

WraparoundInt & WraparoundInt::operator+=(const WraparoundInt &other) {
    this->value = (this->value + other.value) % this->wraparound_ceiling;
    return *this;
}

// throw out of range exception if i is not equal to 0
int WraparoundInt::operator[](const int i) const {
    if (i == 0) return this->value;
    throw out_of_range("Must be zero!");
}

// decrement operator
WraparoundInt & WraparoundInt::operator++() {
    this->value = (this->value + 1) % this->wraparound_ceiling;
    return *this;
}

WraparoundInt WraparoundInt::operator++(int) {
    WraparoundInt old_value(this->value, this->wraparound_ceiling);
    this->value = (this->value + 1) % this->wraparound_ceiling;
    return old_value;
}

// multiplication
WraparoundInt operator*(int i, WraparoundInt wi) {
    return WraparoundInt(i * wi.value, wi.wraparound_ceiling);
}

void test_part3() {
  WraparoundInt wi0(4U, 5U);
  WraparoundInt wi1(1U, 5U);
  WraparoundInt wi2(4U, 5U);
  WraparoundInt wi3(2U, 5U);

  cout << boolalpha;

  cout << (wi0 == wi1) << endl; // false
  cout << (wi0 == wi2) << endl; // true

  cout << wi0 + wi3 << endl; // 1
  wi0 += wi3;
  cout << wi0 << endl; // 1
  cout << wi0[0] << endl; // 1
  cout << wi2++ << endl; // 4
  cout << wi2 << endl; // 0
  cout << ++wi2 << endl; // 1
  cout << wi2 << endl; // 1
  cout << 7 * wi3 << endl; // 4

  //
  // false
  // true
  // 1
  // 1
  // 1
  // 4
  // 0
  // 1
  // 1
  // 4
}

int main() {
    test_part1();
    test_part2();
    test_part3();
}