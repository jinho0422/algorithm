#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int dirY[4] = { 0, -1, 0, 1 };
int dirX[4] = { 1, 0, -1, 0 }; // 0 : �� 1 : �� 2 : �� 3 : ��
int dirYcheck[3] = { 0, 1, 1 }; // ���簢���� ����������� �Ǵ�
int dirXcheck[3] = { 1, 1, 0 };
bool check[104][104]; // �巡�� Ŀ���� �� ������ �������..
int result;

vector<int> dir; // �巡�� Ŀ���� �������������ִ�..

int main() {
	//�Է�
	scanf("%d", &N);
	for (int a, b, c, d, i = 0; i < N; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		//0 ���� �巡�� Ŀ��
		check[b][a] = true;
		dir.push_back(c);
		b += dirY[dir[0]];
		a += dirX[dir[0]];
		check[b][a] = true;
		// j���� �巡�� Ŀ��
		for (int j = 0; j < d; j++) {
			int sz = dir.size();
			for (int s = sz -1; s >= 0; s--) {
				// 90�� ����ٲٱ�
				int curve = dir[s] + 1;
				if (curve == 4) curve = 0;
				dir.push_back(curve); // �ٲ� ���� �ֱ�..
				// �����
				b += dirY[curve];
				a += dirX[curve];
				check[b][a] = true;
			}
		}
		dir.clear(); // ���� �巡��Ŀ�긦 ���� �ʱ�ȭ
	}
	// ���簢������ �Ǵ�..
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