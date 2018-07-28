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
	int nLunchBox;
	int totalRun;
	int totalEat;
	int heatedBox;
	int _temp;


	MW() {
		nLunchBox = 0;
		totalRun = INT_MAX;
		heatedBox = 0;
		_temp = 0;
	}

	void init(void) {
		nLunchBox = 0;
		totalRun = INT_MAX;
		heatedBox = 0;
		_temp = 0;
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
		if (tempFinal > totalRun) {return 0;}
		if (heatedBox >= nLunchBox){
			
			if (_temp < totalRun) {
				//cout << "start: " << start << endl; 
				totalRun = _temp + boxList[start-1].eatTime; 
			}
			_temp = 0;
			return 0;

		}
	
		for (int i = start; i < nLunchBox ; i++) {
			for (int j = i+1 ; j <nLunchBox; j++) {		
				_temp = _temp + boxList[i].heatTime;
				heatedBox++;
				doMW(i+1);	
				heatedBox--;
						
				//TODO
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

