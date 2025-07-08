#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <format>
using namespace std;

void characterPrinter(string str) {
    for (char c: str) {
        if (c == 'l') continue;
        cout << c << endl;
    }
}

void numberStorer() {
    cout << "Enter a number:" << endl;

    double number;
    string input;
    if (cin >> number && cin.eof()) { // could remove eof to store even if enter text after the number
        cout << setw(10) << fixed << setprecision(5) << number << endl;
        //cout << format("{:10.5f}", number) << endl;
    } else {
        cin.clear();
        getline(cin, input);
        
        ofstream outputFile("out.txt");
        outputFile << input << endl;
        //outputFile.close(); (not needed since we're in a block)
    }

    if (!cin) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void numberStorerStringStream() {
    cout << "Enter a number:" << endl;
    string input;
    double number;

    getline(cin, input);
    stringstream ss;
    ss << input;

    if (ss >> number && ss.eof()) { // could remove eof to store even if enter text after the number
        cout << setw(10) << fixed << setprecision(5) << number << endl;
        //cout << format("{:10.5f}", number) << endl;
    } else {
        ofstream outputFile("out.txt");
        outputFile << input << endl;
    }
}

void numberGuesser() {
    srand(time(nullptr)); // seed the random number generator
    int target = rand() % 51; // 0-50
    int guess = -1;
    while (true) {
        cout << "Guess a number:" << endl;
        cin >> guess;
        if (guess == target) break;
        cout << (guess > target ? "too high" : "too low") << endl;
    }
    cout << "congratulations!" << endl;
}

int main() {
    characterPrinter("Hello World");
    numberStorerStringStream();
    numberGuesser();
}

