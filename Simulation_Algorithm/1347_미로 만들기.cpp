#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <math.h>
using namespace std;

int N;
char str[51];
int dirY[4] = { 1, 0, -1, 0 };
int dirX[4] = { 0, -1, 0, 1 };
char result[100][100];

typedef struct _pos {
	int h, y;
}pos;
vector<pos> Vec;

int main() {
	//�Է�
	scanf("%d", &N);
	scanf("%s", str);
	//������� #�� �ʱ�ȭ
	for (int hang = 0; hang < 100; hang++) {
		for (int yal = 0; yal < 100; yal++) {
			result[hang][yal] = '#';
		}
	}
	int hh = 0, yy = 0, dir = 0; // ������ġ hh : hang, yy : yal, dir : ����
	Vec.push_back(pos({ hh, yy })); // �����̴� ��ġ�� Vector�� �ִ´�.
	for (int s = 0; str[s] != '\0'; s++) {
		if (str[s] == 'R') dir = ((dir + 1) % 4); // ���������� ����
		else if (str[s] == 'L') { // �������� ����
			dir--;
			if (dir < 0) dir = 3;
		}
		else if (str[s] == 'F') { // ������ �����ؼ� Vector�� �ִ´�.
			int newY = hh + dirY[dir];
			int newX = yy + dirX[dir];
			Vec.push_back(pos({ newY, newX }));
			hh = newY, yy = newX;
		}
	}
	int minH = 987654321, maxH = 0, minY = 987654321, maxY = 0; // ������� �̱����� ����üũ ����
	for (int i = 0; i < Vec.size(); i++) {
		if (Vec[i].h < minH) minH = Vec[i].h;
		if (Vec[i].y < minY) minY = Vec[i].y;
	}
	for (int i = 0; i < Vec.size(); i++) { // ��� �� ������ ũ�Ⱑ ���� ���� ��ġ �����ָ鼭 ���� ��ġ�� 0,0���� �ٲ��ش�
		Vec[i].h += abs(minH), Vec[i].y += abs(minY);
		if (Vec[i].y > maxY) maxY = Vec[i].y;
		if (Vec[i].h > maxH) maxH = Vec[i].h;
		result[Vec[i].h][Vec[i].y] = '.';	
	}
	// ���
	for (int hang = 0; hang <= maxH; hang++) {
		for (int yal = 0; yal <= maxY; yal++) {
			printf("%c", result[hang][yal]);
		}
		printf("\n");
	}
	return 0;
}