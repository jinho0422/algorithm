#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int dirY[4] = { 0, -1, 0, 1 };
int dirX[4] = { 1, 0, -1, 0 }; // 0 : 우 1 : 상 2 : 좌 3 : 하
int dirYcheck[3] = { 0, 1, 1 }; // 정사각형이 만들어졌는지 판단
int dirXcheck[3] = { 1, 1, 0 };
bool check[104][104]; // 드래콘 커브의 각 점들을 찍기위해..
int result;

vector<int> dir; // 드래곤 커브의 방향을가지고있다..

int main() {
	//입력
	scanf("%d", &N);
	for (int a, b, c, d, i = 0; i < N; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		//0 세대 드래곤 커브
		check[b][a] = true;
		dir.push_back(c);
		b += dirY[dir[0]];
		a += dirX[dir[0]];
		check[b][a] = true;
		// j세대 드래곤 커브
		for (int j = 0; j < d; j++) {
			int sz = dir.size();
			for (int s = sz -1; s >= 0; s--) {
				// 90도 방향바꾸기
				int curve = dir[s] + 1;
				if (curve == 4) curve = 0;
				dir.push_back(curve); // 바꾼 방향 넣기..
				// 점찍기
				b += dirY[curve];
				a += dirX[curve];
				check[b][a] = true;
			}
		}
		dir.clear(); // 다음 드래곤커브를 위해 초기화
	}
	// 정사각형인지 판단..
	for (int hang = 0; hang < 104; hang++) {
		for (int yal = 0; yal < 104; yal++) {
			if (check[hang][yal]) {
				bool flag = false;
				for (int dd = 0; dd < 3; dd++) {
					int newY = hang + dirYcheck[dd];
					int newX = yal + dirXcheck[dd];

					if (newY < 0 || newY > 100 || newX < 0 || newX > 100 || !check[newY][newX]) {
						flag = true;
						continue;
					}
				}
				if (!flag) result++;
			}
		}
	}
	printf("%d\n", result);
	return 0;
}