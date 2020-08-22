#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <math.h>

using namespace std;

int N, M, J;
int board[21];
int result;

vector<int> Vec;

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &J);
	for (int i = 0; i < J; i++) {
		scanf("%d", &board[i]);
	}
	//바구니의 위치를 넣는다(연속된 M)
	for (int i = 1; i <= M; i++) {
		Vec.push_back(i);
	}
	// 사과가 떨어지는 곳을 하나씩 보면서 움직임의 최소값을 찾는다.
	for (int i = 0; i < J; i++) {
		int minCheck = 100; // 움직임 최소값을 찾기위해
		bool flag = false; // 바구니의 왼쪽에 사과가 있으면 false 오른쪽에 있으면 true
		for (int j = 0; j < Vec.size(); j++) {
			if (board[i] > Vec[0] && !flag) flag = true;
			// 움직임 최소값 갱신
			if (minCheck > abs(board[i] - Vec[j])) minCheck = abs(board[i] - Vec[j]);
		}
		// 결과값을 더해주고
		result += minCheck;
		// 사과가 바구니의 왼쪽에 있으면 바구니를 minCheck만큼 왼쪽으로 바구니를 옮겨주고
		if (!flag) {
			for (int k = 0; k < Vec.size(); k++) {
				Vec[k] -= minCheck;
			}
		}
		// 오른쪽으로 바구니를 옮겨준다.
		else {
			for (int k = 0; k < Vec.size(); k++) {
				Vec[k] += minCheck;
			}
		}
	}
	//출력
	printf("%d\n", result);
	return 0;
}