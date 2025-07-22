#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <optional>
#include <stdexcept>

using namespace std;

/*
Create a Counter class, with the following member functions:
increment(), a void function that (seemingly) does nothing
get_count(), a function that tells you how many times increment() has been called for this object
get_total_count(), a function that tells you how many times increment() has been called for **all** counter objects

Hint: use static members.
*/

class Counter {
  int count = 0;
  static int total_count;
public:
  Counter() {}
  void increment() {
    count++;
    total_count++;
  }
  int get_count() {
    return count;
  }
  static int get_total_count() {
    return total_count;
  }
};

int Counter::total_count = 0;

void test_part1() {
  Counter c1;
  Counter c2;
  c1.increment();
  c2.increment();
  c2.increment();
  cout << c1.get_count() << endl;  // `1`
  cout << Counter::get_total_count() << endl; // `3`
  cout << c2.get_count() << endl;  // `2`
  cout << Counter::get_total_count() << endl; // `3`
}

/*
Write a function index_of that takes a vector of strings and a string to search for. 
See the function definition for more instructions 
Write a function optional_index_of that takes a vector of strings and a string to search for. 
See the function definition for more instructions
Fill out the code in main. See the main function for more instructions
*/

class not_found_error : public runtime_error {
public:
  explicit not_found_error(const std::string &what) : runtime_error(what) {}
  explicit not_found_error() : runtime_error("Index not found") {}
};

class empty_input_error : public runtime_error {
public:
  explicit empty_input_error(const std::string &what) : runtime_error(what) {}
  explicit empty_input_error() : runtime_error("Arguments are empty") {}
};

size_t index_of(const vector<string> &search_input,
                const string &search_string) {
  // This function looks through search input
  // searching for "search_string"
  // The function returns the index of the search string
  //
  // If the vector or string is empty
  // The function throws an empty_input_error
  //
  // If the string is not found
  // The function throws a not_found_error
  if (search_input.size() == 0) throw empty_input_error("Empty vector!");
  if (search_string.length() == 0) throw empty_input_error("Empty string!");
  for (size_t i = 0; i < search_input.size(); i++) {
    if (search_input[i] == search_string) return i;
  }
  throw not_found_error("String not in vector!");
}

optional<size_t> optional_index_of(const vector<string> &search_input,
                                   const string &search_string) noexcept {
  // This function looks through search input
  // searching for "search_string"
  // The function returns the index of the search string
  //
  // If the vector or string is empty
  // The function returns a nullopt
  //
  // If the string is not found
  // The function returns a nullopt
  if (search_input.size() == 0 || search_string.length() == 0) return nullopt;
  for (size_t i = 0; i < search_input.size(); i++) {
    if (search_input[i] == search_string) return i;
  }
  return nullopt;
}

void test_part2() {
  vector<string> vector_to_search_in = {"a", "b", "c", "d", "e", "f"};
  vector<string> strings_to_search_for = {"a", "q", "f", ""};

  for (auto string_to_search_for : strings_to_search_for) {
    // TODO: Modify the inside of this for loop
    // If there's a not_found_error, print "Index not found"
    // If there's a empty_input_error, print "Arguments are empty"
    // Hint: Don't hardcode these messages manually, use the .what() function
    // for the error
    try {
      cout << index_of(vector_to_search_in, string_to_search_for) << endl;
    } catch (not_found_error &error) {
      cout << "Index not found" << endl;
    } catch (empty_input_error &error) {
      cout << "Arguments are empty" << endl;
    }
    // Expected output:
    // 0
    // Index not found
    // 5
    // Arguments are empty
  }

  for (auto string_to_search_for : strings_to_search_for) {
    // TODO: Modify the inside of this for loop
    // If index_of failed in any way
    // print "Failure in index_of"
    auto result = optional_index_of(vector_to_search_in, string_to_search_for);
    if (result) {
      cout << result.value() << endl;
    } else {
      cout << "Failure in index_of" << endl;
    }
    // Expected output:
    // 0
    // Failure in index_of
    // 5
    // Failure in index_of
  }
}

int main() {
  test_part1();
  test_part2();
}