/*
 * wildcard.cpp
 *
 *  Created on: 2018. 7. 1.
 *      Author: NOTE
 */

#include <iostream>
#include <string>

using namespace std;

class WILDCARD {
public:
	void init();
	void inputData();
	void verifyData(unsigned int wIndex, unsigned int dIndex);
private:
	string m_wildcard;
	string m_data;
	int m_ntest;
};

void WILDCARD::init(void)
{
	m_wildcard.clear();
	m_data.clear();

}

void WILDCARD::inputData()
{
	cin >> m_wildcard;
	cin >> m_ntest;


	if (m_wildcard.empty()) { exit(0); }

	//cout << m_wildcard << endl;

	m_wildcard.append("\n");
	while(m_ntest--){
		m_data.clear();
		cin >> m_data;

		if (m_data.empty()) {continue;}
		m_data.append("\n");
		cout << m_data.length() << endl;
		verifyData(0, 0);
	}
}

void WILDCARD::verifyData(unsigned int wIndex, unsigned int dIndex)
{
	//TODO
	// exit condition

	cout << "wIndex : " << wIndex << endl;
	cout << "dIndex : " << dIndex << endl;

	if (wIndex >= m_wildcard.length() ) {
		if (dIndex >= m_data.length()) {
			cout << m_data;
			return;
		} else return;
	}

	if (m_wildcard.at(wIndex) == '*' ) {
		cout << "case 1" << endl;

		cout << m_wildcard.at(wIndex) << endl;
		cout << m_data.at(dIndex) << endl;
		wIndex++;
		dIndex++;
		cout << "wIndex 1: " << wIndex << endl;
		cout << "dIndex 1: " << dIndex << endl;
		while (m_wildcard.at(wIndex) != m_data.at(dIndex) && dIndex < m_data.length()) {
				cout << "dddd: ";
				dIndex++;
		}
		cout << "wIndex 2: " << wIndex << endl;
		cout << "dIndex 2: " << dIndex << endl;
		verifyData(wIndex, dIndex);
		//wIndex++;
	} else {
		if  (m_wildcard.at(wIndex) == '?') {
			++wIndex;
			++dIndex;
			verifyData(wIndex, dIndex);
		} else if (m_wildcard.at(wIndex) == m_data.at(dIndex)) {
			cout << m_wildcard.at(wIndex);
			cout << m_data.at(dIndex);
			cout << "case 3" << endl;
			++wIndex;
			++dIndex;
			verifyData(wIndex, dIndex);
		} else {
			//wIndex = m_wildcard.length() + 1;
		}
	}





}

int main(void)
{
	int testcases = 0;
	cin >> testcases;

	WILDCARD wildcard;

	while (testcases--) {
		wildcard.init();
		wildcard.inputData();
	}
	return 0;
}


