// Test Cases (1 <= C <= 50)
// # of items (1 <= N <= 100)
// volume (1 <= W <= 1000)

#include <iostream>
#include <string.h>

using namespace std;

class PackItem {
private:
	string name[1001];
	int volume;
	int needs;
public:
	void setVolume(int _vol);
	void setName(string _name);
	int getVolume(void);
};

void PackItem::setVolume(int _vol) {}
void PackItem::setName(string _name) {}
int PackItem::getVolume(void) {}

class CarrierBox {
private:
	int maxVolme;
	PackItem itemList[100];

public:
	void setMaxVolume(int _volume);
	void setItem(PackItem _item);

};
//----------------------------------------------------------------
int main(void) {

}

