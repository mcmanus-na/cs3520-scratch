#include <string>
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

/*
Exercise 1:

Create an enum called "MealSize" with the possible options "None", "Small", "Medium", "Large"
This enum should be scoped. Add a comment explaining why a scoped enum is a good idea.
Create a struct called "Meal" with three member variables: burger_size, fries_size, drink_size. Each variable should have the type "MealSize"
Create a class called "Restaurant" with two member variables: an int called "num_employees" and a vector of "Meal"s called "todays_orders"
Create a default constructor and a constructor that takes an int and a vector as input. The default constructor should initialize the Restaurant object with reasonable defaults, while the other constructor should set the member variables based on what's passed in.
Create a member function that prints the number of employees and the number of daily orders.
Create one or more member functions that do something else. Get creative
*/

// scoped enum means if we had another enum with an overlapping option it wouldn't be confused
enum class MealSize {
    None,
    Small,
    Medium,
    Large
};

struct Meal {
    MealSize burger_size;
    MealSize fries_size;
    MealSize drink_size;
};

const Meal EMPTY_MEAL = {MealSize::None, MealSize::None, MealSize::None};

class Restaurant {
    int num_employees;
    vector<Meal> todays_orders;

    string get_meal_desc(Meal meal) const {
        return "Burger:" + get_size_desc(meal.burger_size)
            + "\nFries:" + get_size_desc(meal.fries_size)
            + "\nDrink:" + get_size_desc(meal.drink_size);
    }

    string get_size_desc(MealSize size) const {
        switch (size) {
            case MealSize::None:
                return "None";
            case MealSize::Small:
                return "Small";
            case MealSize::Medium:
                return "Medium";
            case MealSize::Large:
                return "Large";
        }
        return "Error";
    }

public:
    void print() const {
        cout << "This restaurant has " << num_employees << " employees:" << endl;
        cout << "Todays orders:" << endl;
        for (Meal meal : todays_orders) {
            cout << "Order:" << endl << get_meal_desc(meal) << endl;
        }
    }

    Restaurant(): num_employees(1), todays_orders(vector<Meal>()) {
        cout << "Creating default Restaurant:" << endl;
        print();
    }

    Restaurant(int num_employees, vector<Meal> todays_orders)
        : num_employees(num_employees), todays_orders(todays_orders) {
        cout << "Creating new Restaurant:" << endl;
        print();
    }

    void add_order(Meal new_order) {
        todays_orders.push_back(new_order);
    }

    Meal get_order() {
        if (todays_orders.size() == 0) {
            cout << "No orders!" << endl;
            return EMPTY_MEAL;
        }
        Meal meal = todays_orders.at(0);
        todays_orders.erase(todays_orders.begin());
        return meal;
    }
};

void test_part1() {
    Restaurant r1;
    Meal m1 = {MealSize::Small, MealSize::Medium, MealSize::Small};
    Meal m2 = {MealSize::Large, MealSize::Small, MealSize::Large};
    Meal m3 = {MealSize::Medium, MealSize::Large, MealSize::Medium};
    Restaurant r2(10, {m1, m2, m3});

    r1.add_order(m1);
    r1.print();
    r2.get_order();
    r2.print();
}

/*
Use the debugger, (and not cout) to determine the value assigned to result when ii is 5.

You can paste the code into scratch.cpp from the demo to run in VS Code.

Optional challenge: if you set mys to 0 in that iteration of the loop (before result is added to mys), what is the value of result on the next iteration?
*/

/* ANSWER:
result = 15
result = 22
*/

int mystery_func(int & x) {
  x = 5 + ((x * x * 2) % 41);
  return x / 2;
}

void test_part2() {
  int mys = 0;
  for (int ii = 0; ii < 10; ++ ii) {
    int result = mystery_func(mys);
    mys += result;
  }
}

/*
Use valgrind to find a memory error in the program.  Add a comment at the top of
the file describing the error along with relevant output from valgrind.

You can paste the code into scratch.cpp from the demo to run in VS Code.
*/

/* ANSWER:
There's an error if the first number you input is larger than the size of the list.
Invalid read of size 4
==36109==    at 0x109486: test_part3() (scratch.cpp:55)
==36109==    by 0x109551: main (scratch.cpp:61)
==36109==  Address 0x4e1e9c8 is 24 bytes after a block of size 16 in arena "client"
*/

void test_part3() {
  cout << "Enter some numbers and then eof:" << endl;

  vector< int > numbers;
  int x;
  while (cin >> x) {
    numbers.push_back(x);
  }
  
  if (!numbers.empty()) {
    const int index = numbers.front();
    const int number = numbers[index];
    cout << "The number at index " << index << " is " << number << endl;
  }
}

/*
Use gcov to determine how many times the lines commented LINE 1 and LINE 2 are executed (each).

You can paste the code into scratch.cpp from the demo to run in VS Code.

Hint: You may need to change your Makefile.
*/

/* ANSWER:
LINE 1: 100
LINE 2: 4799
*/

#include <iostream>
using namespace std;

void test_part4() {
    int x = 0;
    int y = 0;
    for (int ii = 0; ii < 100; ++ ii) {
        x = ((x + 1) * 7) % 97; // LINE 1
        for (int jj = 0; jj < x; ++ jj) {
            y = ((y + 1) * 5) % 97; // LINE 2
        }
    }
    cout << x << " " << y << endl;
}

/*
Use callgrind to determine whether the program spends more instructions (inclusive) in mystery1 or mystery2.  Include relevant callgrind output in your answer.

You can paste the code into scratch.cpp from the demo to run in VS Code.
*/

/* ANSWER:
It spends more time in mystery2 
6,084,952,092 (83.64%)  scratch.cpp:mystery2() [/home/dalma/cs3520-scratch/scratch]
1,188,256,012 (16.33%)  scratch.cpp:mystery1() [/home/dalma/cs3520-scratch/scratch]
*/

#include <iostream>
using namespace std;

void mystery1() {
    int x = 0;
    int y = 0;
    for (int ii = 0; ii < 1000000; ++ ii) {
        x = ((x + 1) * 7) % 97;
        for (int jj = 0; jj < x; ++ jj) {
            y = ((y + 1) * 5) % 97;
        }
    }
    cout << x << " " << y << endl;
}

void mystery2() {
    int x = 0;
    int y = 0;
    for (int ii = 0; ii < 100000; ++ ii) {
        x = ((x + 1) * 7) % 5011;
        for (int jj = 0; jj < x; ++ jj) {
            y = ((y + 1) * 5) % 97;
        }
    }
    cout << x << " " << y << endl;
}

void test_part5() {
    mystery1();
    mystery2();
}

int main() {
  test_part5();
}