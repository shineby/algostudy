#include <iostream>
#include <string.h>

using namespace std;

class CheckFriends{
	private:
		int pairTable[10][10];
		int checkTable[10];
		int studentNum;
		int pairNum;

		int totalCount;
		int foundCnt;
	public:
		void inputData(void){
			// initialize 
			memset(pairTable, 0, sizeof(int)*10*10);
			memset(checkTable, 0, sizeof(int)*10);
			totalCount = 0;
			foundCnt = 0;

			cin >> studentNum;
			cin >> pairNum;

			int friendA, friendB;
			for ( int i = 0 ; i < pairNum ; i++)
			{

				cin >> friendA;
				cin >> friendB;
				pairTable[friendA][friendB] = 1;
				pairTable[friendB][friendA] = 1;
			}

		}
		void searchFriend(int start = 0) {
			//checkTable
			//pairTable

			for (int i = start ; i < studentNum ; i++)
				for (int j = i+1; j < studentNum; j++) {
					//cout << i << ", " << j << "\n";
					
					if (checkTable[i] ==0 && checkTable[j] == 0 && pairTable[i][j]) {
						//cout << "found \n";
						checkTable[i] = 1;
						checkTable[j] = 1;
						foundCnt++;
					        //cout << "funcCnt: " << foundCnt << "\n";	
						searchFriend(i+1);
					
						if (foundCnt == studentNum/2)
							totalCount++;
						checkTable[i] = 0;
						checkTable[j] = 0;
						foundCnt--;
					}

					
				}

		}

		void printResult(void) {
			cout << totalCount << "\n";
		}

		void printTable(void){
			for (int i = 0 ; i < studentNum ; i++) {
				cout << "\n";
				for (int j = 0 ; j < studentNum ; j++)
					cout << pairTable[i][j];
			}
			cout << "\n";	
		}
};

int main(void) {
	int testCases = 0;
	cin >> testCases;

	CheckFriends sf;

	while (testCases--) {
		sf.inputData();
		sf.searchFriend();	
		//sf.printTable();
		sf.printResult();
	}
}
