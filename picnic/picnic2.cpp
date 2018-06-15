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
	public:
		void inputData(void){
			// initialize 
			memset(pairTable, 0, sizeof(int)*10*10);
			memset(checkTable, 0, sizeof(int)*10);
			totalCount = 0;


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
		void searchFriend(void) {
			
		}

		void printResult(void) {
			cout << totalCount << "\n";
		}

};

int main(void) {
	int testCases = 0;
	cin >> testCases;

	CheckFriends sf;

	while (testCases--) {
		sf.inputData();
		sf.searchFriend();	
		sf.printResult();
	}
}
