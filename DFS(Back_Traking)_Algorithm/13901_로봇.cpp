#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M, K, sh, sy;
bool check[1001][1001];
int dirY[5] = { 0, -1, 1, 0, 0 };
int dirX[5] = { 0, 0, 0, -1, 1 };
int d[4];


int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int a, b, i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		check[a][b] = true;
	}
	scanf("%d %d", &sh, &sy);
	check[sh][sy] = true;
	for (int dd, i = 0; i < 4; i++) {
		scanf("%d", &dd);
		d[i] = dd;
	}

	int numbers = 0;
	int cnt = 0;
	int tmpH = sh, tmpY = sy;
	while (1) {
		tmpH = sh + dirY[d[cnt]];
		tmpY = sy + dirX[d[cnt]];

		
		if (check[tmpH][tmpY] || tmpH < 0 || tmpH > N -1 || tmpY < 0 || tmpY > M -1) {
			numbers++;
			cnt++;
			cnt %= 4;
		}
		else {
			sh = tmpH;
			sy = tmpY;
			check[sh][sy] = true;
			numbers = 0;
		}
		if (numbers == 4) break;
	}
	printf("%d %d\n", sh, sy);
	return 0;
}