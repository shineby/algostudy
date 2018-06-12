// 1.Question
// 안드로메다 유치원 익스프레스반에서는 다음 주에 율동공원으로 소풍을 갑니다. 원석 선생님은 소풍 때 학생들을 두 명씩 짝을 지어 행동하게 하려고 합니다. 그런데 서로 친구가 아닌 학생들끼리 짝을 지어 주면 서로 싸우거나 같이 돌아다니지 않기 때문에, 항상 서로 친구인 학생들끼리만 짝을 지어 줘야 합니다.
// 각 학생들의 쌍에 대해 이들이 서로 친구인지 여부가 주어질 때, 학생들을 짝지어줄 수 있는 방법의 수를 계산하는 프로그램을 작성하세요.
// 짝이 되는 학생들이 일부만 다르더라도 다른 방법이라고 봅니다. 예를 들어 다음 두 가지 방법은 서로 다른 방법입니다.
// (태연,제시카) (써니,티파니) (효연,유리)
// (태연,제시카) (써니,유리) (효연,티파니)

// 2.문제
// 입력
// 입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다.
// 각 테스트 케이스의 첫 줄에는 학생의 수 n (2 <= n <= 10) 과 친구 쌍의 수 m (0 <= m <= n*(n-1)/2) 이 주어집니다.
// 그 다음 줄에 m 개의 정수 쌍으로 서로 친구인 두 학생의 번호가 주어집니다. 번호는 모두 0 부터 n-1 사이의 정수이고,
// 같은 쌍은 입력에 두 번 주어지지 않습니다. 학생들의 수는 짝수입니다.

// 3.출력
// 각 테스트 케이스마다 한 줄에 모든 학생을 친구끼리만 짝지어줄 수 있는 방법의 수를 출력합니다.
/*
예제입력
3
2 1
0 1
4 6
0 1 1 2 2 3 3 0 0 2 1 3
6 10
0 1 0 2 1 2 1 3 1 4 2 3 2 4 3 4 3 5 4 5
예제출력
1
3
4
*/

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
//(std::find(vector.begin(), vector.end(), item) != vector.end())
// true, false

using namespace std;

int cases;
int case_index = 0;
int nStudent;
int nPair;
int pairA, pairB;
int temp;
int flag = 1;
int student[100] = {0, };
vector<int> pairTable;
int totalCount[100] = {0,};

vector<vector<int> *> seqList;
vector<int> *seqTemp;

void checkInput(int nStudent, int nPair, vector<int> v)
{
    cout << nStudent << " " << nPair << "\n";
    vector<int>::iterator iter = v.begin();
    for (iter = v.begin() ; iter != v.end() ; ++iter)
        cout << *iter << " ";
    cout << "\n";
}

void printVector(vector<int> v) 
{
    vector<int>::iterator iter = v.begin();	
    for (iter = v.begin() ; iter != v.end() ; ++iter)
        cout << *iter << " ";
}

void searchPair(vector<int> &pairTable) {


	//if (pairTable.empty()) return;


	vector<int>::reverse_iterator rit ;
	//for (int index = 0 ; index < nPair ; index++) {
	student[pairA] =1;
	student[pairB] = 1;
	int index = 0;
	//cout << "student : " << student[0] << student[1] << student[2] << student[3] << student[4] << student[5] << endl;
	for (rit = pairTable.rbegin() ; rit != pairTable.rend() ; rit++){

		flag = 1;
		// pair 추출
		int a = *rit;
		++rit;
		int b = *rit;
		//cout << " => " << a << ", " << b << endl;

		// map update

		if (student[a] == 0 && student[b] == 0) {
			student[a] = 1;
			student[b] = 1;
			seqTemp->push_back(index);
			//cout << index << ",";
			//cout << "student : " << student[0] << student[1] << student[2] << student[3] << student[4] << student[5] << endl;
		}


		index += 1;

	} // end of pair
	//cout << "\n";

	for (int i = 0 ; i < nStudent ; i++) {
		flag = flag && student[i];
	}

	if (flag == 1) {
		//TODO
		//sort를 진행해서 index sequence가 기존에 없는 경우에만 totalCount를 늘린다.

		//cout << "student : " << student[0] << student[1] << student[2] << student[3] << student[4] << student[5] << endl;
		
		sort(seqTemp->begin(), seqTemp->end());

		////TODO
		if (seqList.empty()) { 
			seqList.push_back(seqTemp);
			totalCount[case_index] += 1;
		}

		int isFound = 0;
		vector<vector<int> *>::iterator it = seqList.begin();
		for ( it = seqList.begin() ; it != seqList.end() ; ++it ){
			if ( (**it) == *seqTemp ) {
				isFound = 1;
				break;
			}
			//printVector(**it);
			//cout <<"\n";
		}
		if (isFound == 0 ) {
			seqList.push_back(seqTemp);
			totalCount[case_index] += 1;
		};
		//cout << "totalCount: " << totalCount << endl;
	}
	for (int i = 0 ; i < 100 ; i++) {
		student[i] = 0;
	}

	//pairTable.pop_back();
	//pairTable.pop_back();
	//searchPair(pairTable);
}

int main()
{
	cin >> cases;
	while( case_index < cases) {
		totalCount[case_index] = 0;

		pairTable.clear();
		cin >> nStudent >> nPair;
		for (int i = 0; i < (nPair * 2); i++) {
			cin >> temp;
			//cout << "temp : " << temp << "\n";
			pairTable.push_back(temp);
		}

        //checkInput(nStudent, nPair, pairTable);
        //cout << "\n" << endl;

		
		vector<int> tempTable = pairTable;
		for (int index = 0 ; index < nPair ; index++) {
			//cout << "!!!!!!!!!! index : " << index << endl;
			seqTemp = new vector<int>;
			seqTemp->push_back(index);
			
			pairA = tempTable.back();
			tempTable.pop_back();
			pairB = tempTable.back();
			tempTable.pop_back();
			//cout << index << ",";
			searchPair(pairTable);
			
			//sort(seqTemp.begin(), seqTemp.end());

			//seqTemp->clear();
		}

		seqList.clear();
		case_index ++;
	}
	for (int index = 0 ; index < cases ; index ++)
		cout << totalCount[index] << "\n";
	return 0;

}
