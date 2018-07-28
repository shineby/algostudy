// Test Cases (1 <= C <= 50)
// # of items (1 <= N <= 100)
// volume (1 <= W <= 1000)

#include <iostream>
#include <string.h>

using namespace std;

class PackItem {
public:
	string name[1001];
	int vol;
	int needs;
	void setVolume(int _vol);
	void setName(string _name);
	int getVolume(void);
};

void PackItem::setVolume(int _vol) {}
void PackItem::setName(string _name) {}
int PackItem::getVolume(void) {}

class CarrierBox {
public:
	int maxVol;
	int maxItem;
	PackItem itemList[100];
	

	CarrierBox( int _maxItem, int _maxVol): maxItem(_maxItem) , maxVol(_maxVol) {};
	void setMaxVolume(int _volume);
	void setItem(PackItem _item);
	void showInfo(void) {
		cout << "MaxItem : " << maxItem << " MaxVol : " << maxVol << endl;
	}
};

class PackCarrier {
public:
	PackCarrier(CarrierBox cbox){};



};
//----------------------------------------------------------------
int main(void) {
	int testCases = 0;

	cin >> testCases;
	while (testCases--){
		int maxItem = 0;
		int maxVol = 0 ;
		cin >> maxItem;
		cin >> maxVol;

		CarrierBox cb = CarrierBox(maxItem, maxVol);
		cb.showInfo();
		PackCarrier pc( cb );


	}
}

