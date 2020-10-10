#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M, T;
int board[52][52];
bool check[52][52]; // 인접한 위치에 같은 값이 있는지 판단하는 check배열
int dirY[4] = { -1, 0, 0, 1 }; // 상, 좌, 우, 하
int dirX[4] = { 0, -1, 1, 0 };
int numbers, result; // numbers : 원판에 있는 총값 , result : 최종 결과

deque<int> Q[52];

int main() {
	//입력
	scanf("%d %d %d", &N, &M, &T);
	numbers = N * M;
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			scanf("%d", &board[hang][yal]);
			Q[hang].push_back(board[hang][yal]);
		}
	}
	for (int x, d, k, t = 0; t < T; t++) {
		scanf("%d %d %d", &x, &d, &k);
		//시계
		if (d == 0) {
			for (int j = x; j <= N;) {		
				for (int i = 0; i < k; i++) {
					int p = Q[j].back();
					Q[j].pop_back();
					Q[j].push_front(p);
				}
				j += x;
			}
		}
		//반시계
		else if (d == 1) {	
			for (int j = x; j <= N;) {
				for (int i = 0; i < k; i++) {
					int p = Q[j].front();
					Q[j].pop_front();
					Q[j].push_back(p);
				}
				j += x;
			}
		}
		float sum = 0; // 원판의 값의 총합
		// board배열에 원판을 넣어준다..
		for (int hang = 1; hang <= N; hang++) {
			for (int yal = 1; yal <= M; yal++) {
				board[hang][yal] = Q[hang][yal - 1];
				sum += board[hang][yal];
			}
		}
		bool flag = false;
		for (int hang = 1; hang <= N; hang++) {
			for (int yal = 1; yal <= M; yal++) {
				if (board[hang][yal] == 0) continue; // 먼저 없어진 원판의 숫자는 continue..
				for (int dir = 0; dir < 4; dir++) {
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];
					
					if (newY <= 0 || newY > N) continue; // 경계를 넘는 것
					if (newX <= 0) { // 원판이므로 경계값이 왼쪽으로 넘어가면 마지막 것과 비교
						if (board[hang][yal] == board[newY][M]) {
							check[hang][yal] = check[newY][M] = true;
							flag = true;
						}
					}
					if (newX > M) { // 경계값 오른쪽으로 넘어가면 처음것과 비교
						if (board[hang][yal] == board[newY][0]) {
							check[hang][yal] = check[newY][0] = true;
							flag = true;
						}
					}
					if (board[hang][yal] == board[newY][newX]) {
						check[hang][yal] = check[newY][newX] = true;
						flag = true;
					}
				}
			}
		}
		// 원판의 모든 수들이 인접하지 않을때
		if (!flag) {
			float avg = sum / numbers;
			for (int hang = 1; hang <= N; hang++) {
				for (int yal = 1; yal <= M; yal++) {
					if (Q[hang][yal - 1] != 0) {
						if (Q[hang][yal - 1] > avg) Q[hang][yal - 1]--;
						else if (Q[hang][yal - 1] < avg )Q[hang][yal - 1]++;
					}
				}
			}
		}
		//인접한 것이 있을때
		else {
			for (int hang = 1; hang <= N; hang++) {
				for (int yal = 1; yal <= M; yal++) {
					if (check[hang][yal]) {
						Q[hang][yal -1] = 0;
						numbers--;
						check[hang][yal] = false;
					}
				}
			}
		}
	}
	// 결과값뽑기, 출력
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			result += Q[hang][yal -1];
		}
	}
	printf("%d\n", result);
	return 0;
}