// Test Cases (1 <= C <= 50)
// # of items (1 <= N <= 100)
// volume (1 <= W <= 1000)

#include <iostream>
#include <string.h>
#include <limits.h>

using namespace std;

class LunchBox {
public:
	int heatTime;
	int eatTime;
	

};

class MW {
public:
	LunchBox boxList[10001];
	int heatedBoxMap[10001];
	int nLunchBox;
	int totalRun;
	int totalEat;
	int nheatedBox;
	int _temp;


	MW() {
		nLunchBox = 0;
		totalRun = INT_MAX;
		nheatedBox = 0;
		_temp = 0;
	}

	void init(void) {
		nLunchBox = 0;
		totalRun = INT_MAX;
		nheatedBox = 0;
		_temp = 0;
		memset(heatedBoxMap, 0, sizeof(heatedBoxMap));
	}

	void inputHeatTime() {
		int _heatTime = 0;
		for ( int i = 0 ; i < nLunchBox; i++) {
			cin >> _heatTime;
			boxList[i].heatTime = _heatTime;
		}
	}
	void inputEatTime() {
		int _eatTime = 0;
		for ( int i = 0 ; i < nLunchBox; i++) {
			cin >> _eatTime;
			boxList[i].eatTime = _eatTime;
		}
	}
	void printBoxList(void) {
		for ( int i = 0; i < nLunchBox ; i++) {
			cout << "[" << i << "] " <<  "HeatTime: " << boxList[i].heatTime << " EatTime: " << boxList[i].eatTime << endl;
		} 
	}
	int doMW(int start = 0) {
		//TODO
		//do microwave
		int tempFinal = 0;
		

		if (start =! 0)
			tempFinal = totalRun + boxList[start-1].eatTime;	
		else
			tempFinal = totalRun + boxList[0].eatTime;

		if (tempFinal > totalRun) {return 0;}
		
		if (nLunchBox == 1){
			totalRun = boxList[0].eatTime + boxList[0].heatTime;
			return 0;
		}
		if (nheatedBox >= nLunchBox){
			
			if (_temp < totalRun) {
				//cout << "start: " << start << endl; 
				totalRun = _temp + boxList[start].eatTime; 
			}
			_temp = 0;
			return 0;

		}
	
		for (int i = 0; i < nLunchBox ; i++) {
			if (heatedBoxMap[i] == 0) {
				_temp = _temp + boxList[i].heatTime;
				nheatedBox++;
				heatedBoxMap[i] = 1;
				doMW(i);	
				heatedBoxMap[i] = 0;
				nheatedBox--;
				_temp = _temp - boxList[i].heatTime;				
			}
		}
		
	}
	void sortBox(int sel) {
		//TODO 
		//sort box with eat time or heat time	
	}
};





//----------------------------------------------------------------
int main(void) {
	int testCases = 0;

	MW mw;
	cin >> testCases;
	while (testCases--){
		mw.init();
		int _nLunchBox = 0;
		cin >> _nLunchBox;
		mw.nLunchBox = _nLunchBox;
		mw.inputHeatTime();		
		mw.inputEatTime();
		//mw.printBoxList();
		mw.doMW();
		cout << mw.totalRun << endl;
		
		
	}
}

