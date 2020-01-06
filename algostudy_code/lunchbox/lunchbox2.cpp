// Test Cases (1 <= C <= 50)
// # of items (1 <= N <= 100)
// volume (1 <= W <= 1000)

#include <iostream>
#include <string.h>
#include <limits.h>
#include <algorithm>

using namespace std;

class LunchBox {
public:
	int heatTime;
	int eatTime;
};

typedef struct _totalEat {
	int heatTime;
	int eatTime;
	int sum(void) {
		//cout << "heatTime: " << heatTime << ", " << "eatTime: " << eatTime << endl;
		return heatTime + eatTime;
	}
} TotalTime;


bool compare(LunchBox a, LunchBox b){
	if(a.eatTime > b.eatTime) 
		return true;
	return false;
}

class MW {
public:
	
	//int heatedBoxMap[10001];
	LunchBox boxList[10001];
	int nLunchBox;
	int nheatedBox;
	TotalTime totalRun = {};
	TotalTime maxTotalRun = {};
	int _temp;


	MW() {
		nLunchBox = 0;
		nheatedBox = 0;
		_temp = 0;
	}

	void init(void) {
		nLunchBox = 0;
		nheatedBox = 0;
		totalRun = {};
		maxTotalRun = {};
		_temp = 0;
		memset(boxList, 0, sizeof(boxList));
		//memset(heatedBoxMap, 0, sizeof(heatedBoxMap));
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
		// 1. exit criteria
		if (nheatedBox == nLunchBox)
			return 1;
		

		for (int i = start; i < nLunchBox ; i++) {
			
			totalRun.eatTime = boxList[i].eatTime;
			totalRun.heatTime += boxList[i].heatTime;

			if ( maxTotalRun.sum() < totalRun.sum() ) {
				maxTotalRun.heatTime = totalRun.heatTime;
				maxTotalRun.eatTime = totalRun.eatTime;
			}			
		}

	}
	void sortBox(void  ) {
		//TODO 
		//sort box with eat time or heat time	
		//printBoxList();		
		sort(boxList,boxList+nLunchBox, compare);
		//printBoxList();

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
		mw.sortBox();
		//mw.printBoxList();
		mw.doMW();
		cout << mw.maxTotalRun.sum() << endl;
		
		

		
	}
}

