/*
 * wildcard.cpp
 *
 *  Created on: 2018. 7. 1.
 *      Author: NOTE
 */

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class WILDCARD {
public:
	void init();
	void inputData();
	void verifyData(unsigned int wIndex, unsigned int dIndex);
	void printResult(void);
	void sortResult(void);
	string m_result[50];
private:
	string m_wildcard;
	string m_data;


	int m_nresult;
};

void WILDCARD::printResult(void){
	for (int i = 0 ; i < 50 ; i++) {
		if (!m_result[i].empty())
			cout << m_result[i] << endl;
	}
}

void WILDCARD::sortResult(void){
	string temp;
	for (int i = 0 ; i < 50; i++){
		for (int j = i+1 ; j < 49 ; j++){
			if (m_result[i] > m_result[j]){
				temp = m_result[j];
				m_result[j] = m_result[i];
				m_result[i] = temp;
			}
		}
	}

}


void WILDCARD::init(void)
{
	m_wildcard.clear();
	m_data.clear();
	m_nresult = 0;
	memset(m_result, 0, sizeof(m_result));
}

void WILDCARD::inputData()
{
	int m_ntest;

	cin >> m_wildcard;
	cin >> m_ntest;


	if (m_wildcard.empty()) { exit(0); }

	//cout << "wildcard : " <<  m_wildcard << endl;

	m_wildcard.append(" ");

	while(m_ntest--){
		m_data.clear();
		cin >> m_data;

		if (m_data.empty()) {continue;}
		m_data.append(" ");
		//cout << "data : " << m_data << endl;
		verifyData(0, 0);
	}
}

void WILDCARD::verifyData(unsigned int wIndex, unsigned int dIndex)
{
	//TODO
	// exit condition

	if (wIndex >= m_wildcard.length()-1 ) {
		if (dIndex >= m_data.length()-1) {
			//cout << m_data;
			m_result[m_nresult++] = m_data;
			return;
		} else return;
	}
	if (dIndex >= m_data.length()-1) {
		while (m_wildcard.at(wIndex) == '*') {
				//cout << "wIndex: " << wIndex << endl;
				wIndex++;
		}
	}


	if ((m_wildcard.at(wIndex) == '*') && (dIndex < m_data.length()-1) ) {
		wIndex++;
		dIndex++;

		while (m_wildcard.at(wIndex) != m_data.at(dIndex) && dIndex < m_data.length()-1) {
				dIndex++;
		}
		verifyData(wIndex, dIndex);
		//wIndex++;
	} else {
		if  (m_wildcard.at(wIndex) == '?') {
			++wIndex;
			++dIndex;
			verifyData(wIndex, dIndex);
		} else if (m_wildcard.at(wIndex) == m_data.at(dIndex)) {
			++wIndex;
			++dIndex;
			verifyData(wIndex, dIndex);
		} else {
			wIndex = m_wildcard.length() - 1;
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
		wildcard.sortResult();
		cout << "-----------" << endl;
		wildcard.printResult();
	}

	return 0;
}


