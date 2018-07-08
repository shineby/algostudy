#include <iostream>
#include <string>

using namespace std;
static const int NUM_TC_MAX = 50;

class WILDCARD {
private:

	string m_wildcard;
	string m_data;

	int m_nresult;
public:
	void init();
	void inputData();
	int verifyData(unsigned int wIndex, unsigned int dIndex);
	void printResult(void);
	void sortResult(void);
	string m_result[NUM_TC_MAX];
};


void WILDCARD::printResult(void){
	//cout << "-----------------------------" << endl;
 	for (int i = 0 ; i < NUM_TC_MAX ; i++) {
		if (!m_result[i].empty())
			cout << m_result[i] << endl;
	}
}

void WILDCARD::sortResult(void){
	string temp;
	for (int i = 0 ; i < NUM_TC_MAX; i++){
		for (int j = i+1 ; j < NUM_TC_MAX-1 ; j++){
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
	for (int i = 0 ; i < NUM_TC_MAX ; i++)
		m_result[i].clear();
}

int WILDCARD::verifyData(unsigned int wIndex, unsigned int dIndex)
{
	//m_wildcard
	//m_data


	//case 1 : check string alphabet
	while(  (wIndex < m_wildcard.length() && dIndex < m_data.length()) &&
			(m_wildcard[wIndex] == m_data[dIndex] || m_wildcard[wIndex] == '?') ) {
		wIndex++;
		dIndex++;
	}
	//cout << wIndex << "," << dIndex << endl;
	if(wIndex == m_wildcard.length() && dIndex == m_data.length()) return 1;
	if(wIndex == m_wildcard.length() && m_wildcard.at(wIndex-1) == '*') return 1;

	//case 2 : check * wildcard
	if ( m_wildcard[wIndex] == '*' )
		for (int step = 0; dIndex + step <= m_data.length(); step++){
			if (verifyData(wIndex+1, dIndex+step))
				return 1;
		}

	return 0;
}

void WILDCARD::inputData()
{
	int m_ntest;

	cin >> m_wildcard;
	cin >> m_ntest;


	while(m_ntest--){
		m_data.clear();
		cin >> m_data;



		if ( verifyData(0, 0) == 1)
		{
			//cout <<"m_nresult: " << m_nresult << endl;
			m_result[m_nresult] = m_data;
			m_nresult++;
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
		wildcard.printResult();
	}

	return 0;
}
