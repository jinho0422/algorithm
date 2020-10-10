#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, M, T;
int board[52][52];
bool check[52][52]; // ������ ��ġ�� ���� ���� �ִ��� �Ǵ��ϴ� check�迭
int dirY[4] = { -1, 0, 0, 1 }; // ��, ��, ��, ��
int dirX[4] = { 0, -1, 1, 0 };
int numbers, result; // numbers : ���ǿ� �ִ� �Ѱ� , result : ���� ���

deque<int> Q[52];

int main() {
	//�Է�
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
		//�ð�
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
		//�ݽð�
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
		float sum = 0; // ������ ���� ����
		// board�迭�� ������ �־��ش�..
		for (int hang = 1; hang <= N; hang++) {
			for (int yal = 1; yal <= M; yal++) {
				board[hang][yal] = Q[hang][yal - 1];
				sum += board[hang][yal];
			}
		}
		bool flag = false;
		for (int hang = 1; hang <= N; hang++) {
			for (int yal = 1; yal <= M; yal++) {
				if (board[hang][yal] == 0) continue; // ���� ������ ������ ���ڴ� continue..
				for (int dir = 0; dir < 4; dir++) {
					int newY = hang + dirY[dir];
					int newX = yal + dirX[dir];
					
					if (newY <= 0 || newY > N) continue; // ��踦 �Ѵ� ��
					if (newX <= 0) { // �����̹Ƿ� ��谪�� �������� �Ѿ�� ������ �Ͱ� ��
						if (board[hang][yal] == board[newY][M]) {
							check[hang][yal] = check[newY][M] = true;
							flag = true;
						}
					}
					if (newX > M) { // ��谪 ���������� �Ѿ�� ó���Ͱ� ��
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
		// ������ ��� ������ �������� ������
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
		//������ ���� ������
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
	// ������̱�, ���
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= M; yal++) {
			result += Q[hang][yal -1];
		}
	}
	printf("%d\n", result);
	return 0;
}