#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <optional>
#include <stdexcept>

using namespace std;

// Write a function, "array_copy".
// This function takes in two arrays and overwrites as many elements
// as possible in the first array with elements in the second
// (it copies the second array into the first)
//
// Obviously this function needs to take in the two arrays.
// What other information does it need?
// How do you prevent the function from going out of bounds?
// How do you deal with differently sized arrays?
//
// Use the pointer syntax when writing the function

void array_copy(int * target, int target_len, int * source, int source_len) {
    for (int i = 0; i < min(target_len, source_len); i++) {
        target[i] = source[i];
    }
}

void test_part1() {
  int array1[] = {0, 1, 2, 3, 4};
  int array2[] = {55, 66, 77};
  // after array_copy with array1 and array2
  array_copy(array1, 5, array2, 3);
  for (int i : array1) cout << i << endl;
  cout << "-----" << endl;
  // array1 should be {55, 66, 77, 3, 4}

  int array3[] = {11, 22, 33};
  int array4[] = {5, 6, 7, 8, 9};
  // after array_copy with array3 and array4
  array_copy(array3, 3, array4, 5);
  for (int i : array3) cout << i << endl;
  cout << "-----" << endl;
  // array3 should be {5, 6, 7}
}

// Write a function "find_characters".
// This function takes in two strings, "input" and "character_set".
// It returns a pointer to the first place in input
// with a character found in character_set
// (or a pointer to input's null terminator)
//
// Hint, look at string_problem_6 from the live coding
// and return an offset pointer (a pointer added to something)
#include <iostream>
using namespace std;

const bool string_contains(const char * input, const char c) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == c) return true;
    }
    return false;
}

const char * find_characters(const char * input, const char * character_set) {
  int i = 0;
  while (input[i] != '\0' && !string_contains(character_set, input[i])) i++;
  return input + i;
}

void test_part2() {
  // "abcd"
  cout << '"' << find_characters("ABCDabcd", "a") << '"' << endl;
  // "Bbbb"
  cout << '"' << find_characters("bbbBbbb", "ABCD") << '"' << endl;
  // ""
  cout << '"' << find_characters("bbbbbbb", "qrs") << '"' << endl;
}

/*
Write a function reverseStringCopy
This function tries to copy instring into outstring, reversed
if outstring doesn't have enough space, it does nothing and returns false
if outstring has enough space, it fills outstring with a reversed version of
outstring

You can use functions from cstring

Hint: don't forget the terminating null character.
*/

#include <cstring>
#include <iostream>
using namespace std;

bool reverseStringCopy(char * outstring, size_t outstr_size,
                       const char * instring) {
  size_t size = 0;
  while (instring[size] != '\0') size++;
  if (size >= outstr_size) return false; // GEQ because outstr_size includes room for '\0', but size doesn't
  for (size_t i = 0; i < size; i++) {
    outstring[i] = instring[size - 1 - i];
  }
  outstring[size] = '\0';
  return true;
}

void test_part3() {
  const size_t buf_size = 21;
  char buf[buf_size] = "xxxxxxxxxxxxxxxxxxxx";

  cout << '"' 
       << (reverseStringCopy(buf, buf_size, "54321") ? buf : "false")
       << '"' << endl; // "12345"
  cout << '"' 
       << (reverseStringCopy(buf, buf_size, "cba") ? buf : "false")
       << '"' << endl; // "abc"
  cout << '"' 
       << (reverseStringCopy(buf, buf_size, "") ? buf : "false") 
       << '"' << endl; // ""
  cout << '"'
       << (reverseStringCopy(buf, buf_size, "01234567890123456789") ? buf : "false")
       << '"' << endl; // "98765432109876543210"
  cout << '"'
       << (reverseStringCopy(buf, buf_size, "012345678901234567890") ? buf : "false")
       << '"' << endl; // "false"
  cout << '"'
       << (reverseStringCopy(buf, buf_size, "this is a fairly long string") ? buf : "false")
       << '"' << endl; // "false"
}

int main() {
    test_part1();
    test_part2();
    test_part3();
}