#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N;
char str[51];
int board[51][51];
bool check[2][51][51]; // 0 : ,�볪�� ���� 1 : �볪�� ����
int dirY[8] = { -1, 1, 0, 0, -1, 1, 1, -1 };
int dirX[8] = { 0, 0, -1, 1, 1, 1, -1, -1 };
int type, endtype; // type : �볪���� �������� ��������, endtype : ������ ���� �������� ��������..

typedef struct _pos {
	int h, y, n; //  h : hang, y : yal, n : �������� ��������..
}pos;
vector<pos> start;
vector<pos> endd;
queue<pos> Q;
int BFS();

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 0; hang < N; hang++) {
		scanf("%s", str);
		for (int yal = 0; yal < N; yal++) {
			board[hang][yal] = str[yal] - '0';
			if (board[hang][yal] == 'B' - '0') {
				start.push_back(pos({ hang, yal, 0 }));
				board[hang][yal] = 0;
			}
			else if (board[hang][yal] == 'E' - '0') {
				endd.push_back(pos({ hang, yal, 0 }));
				board[hang][yal] = 0;
			}
		}
	}
	//����� �߽��̹Ƿ�.. �߽��� �������� type����
	if (start[0].h != start[1].h) type = 1; 
	if (endd[0].h != endd[1].h) endtype = 1;

	printf("%d\n", BFS());
	return 0;
}

bool move(int t, int hang, int yal, int d) {
	if (t == 0) {
		for (int i = -1; i < 2; i++) {
			int newY = hang + dirY[d];
			int newX = yal + i + dirX[d];
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
		}
	}
	else if (t == 1) {
		for (int i = -1; i < 2; i++) {
			int newY = hang + i + dirY[d];
			int newX = yal + dirX[d];
			if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
		}
	}
	return true;
}

bool move1(int t, int hang, int yal, int d) {
	int newY = hang + dirY[d];
	int newX = yal + dirX[d];
	if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
	return true;
}

bool turns(int hang, int yal) {
	for (int dir = 0; dir < 8; dir++) {
		int newY = hang + dirY[dir];
		int newX = yal + dirX[dir];
		if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1 || board[newY][newX] == 1) return false;
	}
	return true;
}
// �߽ɰ��� �߽����� �����δ�..
int BFS() {
	check[type][start[1].h][start[1].y] = true;
	Q.push(pos({ start[1].h, start[1].y, type }));
	int time = 0;
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.front();
			Q.pop();
			//�������� �����ϰ� type�� ������ return time..
			if (p.n == endtype && p.h == endd[1].h && p.y == endd[1].y) return time;

			for (int dir = 0; dir < 4; dir++) {
				int newY = p.h + dirY[dir];
				int newX = p.y + dirX[dir];
				//�߽ɰ��� ��谪�� �Ѿ�� continue..
				if (newY < 0 || newY > N - 1 || newX < 0 || newX > N - 1) continue;
				// �볪���� ������ �� �� �Ʒ��� �����̰ų� �볪���� ������ �� �¿�� �����϶�
				if ((p.n == 0 && (dir == 0 || dir == 1)) || (p.n == 1 && (dir == 2 || dir == 3))) {
					// �߽ɰ��� ������ ���� ���̶�� move�Լ��� ���� ������ �� �ִ��� �Ǵ�
					if (!check[p.n][newY][newX]) {
						bool flag = move(p.n, p.h, p.y, dir);
						if (flag) {
							check[p.n][newY][newX] = true;
							Q.push(pos({ newY, newX, p.n }));
						}
					}	
				}
				// �볪���� ������ �� �¿�� �����̰ų� �볪���� ������ �� ���Ʒ��� ������ ��
				else {
					//�߽ɰ��� ������ ���� ���̶�� move1�Լ��� ���� ������ �� �ִ��� �Ǵ�
					if (!check[p.n][newY][newX]) {
						bool flag = move1(p.n, newY, newX, dir);
						if (flag) {
							check[p.n][newY][newX] = true;
							Q.push(pos({ newY, newX, p.n }));
						}
					}
				}
			}
			//  90�� turn�� �Ҷ� �����϶� ���η� �湮�ߴ�������, �����϶� ���η� �湮�ߴ� ������ �Ǵ��ϰ� �湮���� �ʾ��� ��
			if ((p.n == 1 && !check[0][p.h][p.y]) || (p.n == 0 && !check[1][p.h][p.y])) {
				bool flag = turns(p.h, p.y);
				if (flag) {
					if (p.n == 1) {
						check[0][p.h][p.y] = true;
						Q.push(pos({ p.h, p.y, 0 }));
					}
					else if (p.n == 0) {
						check[1][p.h][p.y] = true;
						Q.push(pos({ p.h, p.y, 1 }));
					}
				}
			}
		}
		time++;
	}
	return 0;
}