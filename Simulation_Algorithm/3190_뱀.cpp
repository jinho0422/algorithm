#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, K, L;
int time;
char direction;
bool appleCheck[102][102];
bool snakeCheck[102][102];
int dirY[4] = { 0, 1, 0, -1 };
int dirX[4] = { 1, 0, -1, 0 };
int timeResult;

typedef struct _pos {
	int h, y, dd; // h : ��, y : ��, dd : �����̴� ����
}pos;
deque<pos> Q;
typedef struct _pos1 {
	int t; // t : �ð�
	char c; // c : ȸ���ϴ� ����
}pos1;
vector<pos1> Vec;

void solve(int hang, int yal, int d);

int main() {
	//�Է�
	scanf("%d %d", &N, &K);
	for (int a, b, i = 0; i < K; i++) {
		scanf("%d %d", &a, &b);
		appleCheck[a][b] = true;
	}
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d %c", &time, &direction);
		Vec.push_back(pos1({ time, direction }));
	}
	Vec.push_back(pos1({ -1, -1 })); // ȸ���� ó���ϴ� Vec�� �������� ���ؼ�..
	solve(1, 1, 0);
	//���
	printf("%d\n", timeResult);

	return 0;
}

void solve(int hang, int yal, int d) {
	snakeCheck[hang][yal] = true;
	timeResult = 0; // �ð������
	int cnt = 0; // ȸ���� �ϴ��� Ȯ���ϱ� ���� cnt..
	Q.push_back(pos({ hang, yal, d }));
	while (1) {
		pos p = Q.front();
		int newY = p.h + dirY[p.dd];
		int newX = p.y + dirX[p.dd];
		if (newY <= 0 || newY > N || newX <= 0 || newX > N || snakeCheck[newY][newX]) {
			timeResult++;
			break;
		}
		// ������ ������ ����� ������
		if (appleCheck[newY][newX] && !snakeCheck[newY][newX]) {
			snakeCheck[newY][newX] = true;
			appleCheck[newY][newX] = false;
			Q.push_front(pos({ newY, newX, p.dd }));
		}
		//������ ������ ����� ������ ���� ������ �߶󳽴�
		if (!appleCheck[newY][newX] && !snakeCheck[newY][newX]) {
			snakeCheck[newY][newX] = true;
			Q.push_front(pos({ newY, newX, p.dd }));
			pos q = Q.back();
			Q.pop_back();
			snakeCheck[q.h][q.y] = false;
		}
		timeResult++; // ����� ����

		if (Vec[cnt].t == timeResult) { // ������ �ð����� ȸ���� �ؾߵȴٸ�..
			if(Vec[cnt].c == 'D') { // �ð����ȸ��
				pos f = Q.front(); // ���� �Ӹ��� ȸ����Ų��..
				Q.pop_front();
				f.dd++;
				if (f.dd == 4) f.dd = 0;
				Q.push_front(pos({ f.h, f.y, f.dd }));
			}
			else { // �ݽð����ȸ��
				pos f = Q.front();
				Q.pop_front();
				f.dd--;
				if (f.dd == -1) f.dd = 3;
				Q.push_front(pos({ f.h, f.y, f.dd }));
			}
			cnt++; // ���� ȸ���ϴ� �ð��� üũ�ϱ�����..
		}
	}
}