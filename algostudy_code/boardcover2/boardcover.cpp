/*
<문제정보>
제한시간: 2000ms
ID: BOARDCOVER2

<문제>
H×W 크기의 게임판과 한 가지 모양의 블록이 여러 개 있습니다. 
게임판에 가능한 많은 블록을 올려놓고 싶은데, 게임판은 검은 칸과 
흰 칸으로 구성된 격자 모양을 하고 있으며 이 중에서 흰 칸에만 
블록을 올려놓을 수 있습니다. 
이때 블록들은 자유롭게 회전해서 놓을 수 있지만, 
서로 겹치거나, 격자에 어긋나게 덮거나, 검은 칸을 덮거나, 
게임판 밖으로 나가서는 안 됩니다.

입력
입력의 첫 줄에는 테스트 케이스의 수 T (T≤100)가 주어집니다. 
각 테스트 케이스의 첫 줄에는 게임판의 크기 H, W (1≤H, W≤10), 
그리고 블록의 모양을 나타내는 격자의 크기 R, C (1≤R, C≤10)가 주어집니다. 
다음 H줄에는 각각 W 글자의 문자열로 게임판의 정보가 주어집니다. 
문자열의 각 글자는 게임판의 한 칸을 나타내며, #은 검은 칸, 마침표는 흰 칸을 의미합니다. 
다음 R줄에는 각 C 글자의 문자열로 블록의 모양이 주어집니다. 
이 문자열에서 #은 블록의 일부, 마침표는 빈 칸을 나타냅니다.

각 게임판에는 최대 50개의 흰 칸이 있으며, 
각 블록은 3개 이상 10개 이하의 칸들로 구성됩니다. 
변을 맞대고 있는 두 변이 서로 연결되어 있다고 할 때, 
블록을 구성하는 모든 칸들은 서로 직접적 혹은 간접적으로 연결되어 있습니다.

출력
각 테스트 케이스마다 게임판에 놓을 수 있는 최대의 블록 수를 출력합니다.

<예제입력>
2
4 7 2 3
##.##..
#......
#....##
#..####
###
#..
5 10 3 3
..........
..........
..........
..........
..........
.#.
###
..#

<예제출력>
3
8


*/
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
static const int NUM_TC_MAX = 50;

typedef struct _board {
    int w,h,r,c = 0;
    char boardMap[10][10] = {'.',};
    char blkMap[10][10] = {'.',};

    void init() {
        memset(boardMap, 0, sizeof(boardMap));
        memset(blkMap, 0, sizeof(blkMap));
        w = 0;
        h = 0;
        r = 0;
        w = 0;
    }

    void inputBoard(void) {
        for (int j = 0; j < h; j++)
            for (int i = 0; i < w; i++) {
                cin >> boardMap[i][j];
            }

    }

    void inputBlk(void) {
        for (int j = 0; j < r; j++)
            for (int i = 0; i < c; i++) {
                cin >> blkMap[i][j];
            }

    }

    void printMap(void){   
         for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                cout << boardMap[i][j] ;
            }       
            cout << "\n";
        }
    }

    void printBlk(void){   
         for (int j = 0; j < r; j++) {
            for (int i = 0; i < c; i++) {
                cout << blkMap[i][j] ;
            }       
            cout << "\n";
        }
    }
} BOARD;



int main() {
    BOARD brd;
    int testcases =0 ;
    cin >> testcases;
    while(testcases--) {
        cin >> brd.h;
        cin >> brd.w;
        cin >> brd.r;        
        cin >> brd.c;
        brd.inputBoard();   
        //brd.printMap();
        brd.inputBlk();
        //brd.printBlk();

    }
    return 1;
}
