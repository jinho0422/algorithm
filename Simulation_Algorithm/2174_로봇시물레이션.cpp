/*
	가로 N(1<= N <= 100), 세로 M(1<= M <= 100)크기의 땅이 있다. 이 땅위에 A(1 <= N <= 100)개 로봇이 있다.
	로봇들의 초기 위치는 x자표와 y좌표로 나타낸다. x좌표는 왼쪽부터, y좌표는 아래쪽부터 순서가 매겨진다.
	또한 각 로봇은 맨 ㅐ처음에 NWES 중 하나의 방향을 향해 서 있다. 초기에 서 있는 로봇들의 위치는 서로 다르다

	이러한 로봇들에 B(1 <= B <= 100)개의 명령을 내리려고 한다. 각각의명령은 순차적으로 실행.
	즉, 하나의 명령을 한 로봇에서 내렸으면, 그 명령이 완수될 때가지 그 로봇과 다른 모든 로봇에게 다른 명령을 내릴 수 없다.
	명령은 다음과 같다.
	1. L: 로봇이 향하고 있는 방향을 기준으로 왼쪽으로 90도 회전한다.
	2. R: 로봇이 향하고 있는 방향을 기준으로 오른쪽으로 90도 회전한다.
	3. F: 로봇이 향하고 있는 방향을 기준으로 앞으로 한 칸 움직인다.
	간 혹 로봇들에게 내리는 명령이 잘못될 수 있기 때문에, 당신은 로봇들에게 명령을 내리기 전에 한번 시뮬레이션을 해 보면서
	안전성을 검증하려 한다. 이를 도와주는 알고리즘 구현.

	board의 행 방향이 아래부터 1, 2, 3, ... N이 되므로 위에서부터 1, 2, 3,... N이 되기위해
	방향을 잘 설정해주면서 알고리즘 구현..
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int A, B, N, M;
int check[101][101]; // 몇 번째 로봇이 있는지 판단할 수 있는 check배열..
int dirY[4] = { -1, 0, 1, 0 }; // N, W, E, S (북, 동, 남, 서)
int dirX[4] = { 0, 1, 0, -1 };
int n, m;
char c;
bool flag;

typedef struct _pos { // 로봇의 위치(행, 열) 및 방향 struct
	int h, y, d;
}pos;
pos robot[101];

queue<pos> Q;

int main() {
	scanf("%d %d %d %d", &M, &N, &A, &B);
	for (int i = 1; i <= A; i++) {
		scanf("%d %d %c", &m, &n, &c);
		// 행을 위에서부터 1, 2, 3,.... N으로 하기위해서 
		if (c == 'N') robot[i] = { n , m, 2 }; // 입력에서 위쪽을 보고 있으면 아래로..
		else if (c == 'E') robot[i] = { n, m, 1 };
		else if (c == 'S') robot[i] = { n, m, 0 };//입력에서 아래쪽을 보고 있으면 위쪽으로..
		else if (c == 'W') robot[i] = { n, m, 3 };
		check[n][m] = i;// 몇번째 로봇이 있는지 나타내는 check배열..
	}

	for (int i = 0; i < B; i++) {
		scanf("%d %c %d", &n, &c, &m);

		if (!flag) { // 정답이 나오지 않았으면..
			if (c == 'L') {// 명령 L은 방향을 기준으로 왼쪽으로 90도 회전하지만.. 행의 위치를 바꿔주면서 방향을 기준으로 오른쪽으로 90도 회전..
				int cnt = 0;
				while (cnt < m) { // 각 명령의 횟수를 이행하기 위해서..
					robot[n].d++; // 시계방향으로 회전..
					if (robot[n].d == 4) robot[n].d = 0; // 만약 robot[n].d가 4가 되면 0으로 바꿔줘야된다..
					cnt++;
				}
			}
			else if (c == 'R') { // 명령 R은 시계방향으로 90도 돌지만 행의 위치를 바꿔주면서 반시게방향으로 90도 돌려준다..
				int cnt = 0;
				while (cnt < m) {
					robot[n].d--; //반시계방향 회전..
					if (robot[n].d == -1) robot[n].d = 3;
					cnt++;
				}
			}
			else if (c == 'F') { // 명령 F는 앞으로 전진..
				int cnt = 0;
				flag = false;
				while (cnt < m) { // 각 명령의 횟수를 이행..
					check[robot[n].h][robot[n].y] = 0; // 각 로봇의 위치에서 로봇을 움직이므로 현재의 위치에 로롯이 없애기 위해..
					int newY = robot[n].h + dirY[robot[n].d];
					int newX = robot[n].y + dirX[robot[n].d];

					if (newY <= 0 || newY > N || newX <= 0 || newX > M) { // 벽을 뚫고 나가면..
						printf("Robot %d crashes into the wall\n", n);
						flag = true;
						break;
					}
					if (check[newY][newX] != 0) { // 다른 로봇과 부딧히면..
						printf("Robot %d crashes into robot %d\n", n, check[newY][newX]);
						flag = true;
						break;
					}
					if (check[newY][newX] == 0) check[newY][newX] = n; // 움직인곳에 아무것도 없으면..
					cnt++; robot[n].h = newY; robot[n].y = newX;
				}
			}
		}
	}
	if (flag) return 0;
	printf("OK\n");
	return 0;
}