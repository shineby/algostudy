#include <iostream>
#include <string>

using namespace std;

int main () {
	string test;
	test.clear();
	test.append("\n");
	cout << test.size() << endl;
	if (test.at(0) == '\n') cout << "found" << endl;
	
}