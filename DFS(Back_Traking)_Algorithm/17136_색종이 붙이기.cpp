/*
	���簢�� ����� �� �ټ�����(1, 2, 3, 4, 5�� ����)�� �����̰� �ְ� �� ������ �����̴� 5���� �������ִ�.
	�����̸� ũ�Ⱑ 10*10�� ���� ���� ���̷��� �ϴµ� �� ĭ���� 0, 1�� ��ĥ�Ǿ� �ְ� 1�� ���� ĭ�� ��� �����̷� �������� �Ѵ�.
	�����̸� ���� ���� ������ ��� ������ �������� �ȵǰ�, ���ĵ� �ȵȴ�. ����, ĭ�� ���� ��ġ�ϰ� �ٿ����Ѵ�.
	���̰� �־����� ��, 1�� ���� ��� ĭ�� ���̴µ� �ʿ��� �������� �ּ� ������ ���ϴ� �˰����̴�.

	������ ���簢�� �����̴� 5�����ְ� 1�� ��Ÿ���� 5������ �����̸� ���� �� �ִ��� �������� �Ǵ��ϸ鼭
	�ؾߵǹǷ� ����������� Ȱ���Ͽ� �˰����� �����ߴ�.
	*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int board[10][10];
bool check[10][10];
int paper_num; // �����̸� �ٿ��ߵǴ� 1�� ����..
int result;
int paper[6] = { 0, 5, 5, 5, 5, 5 }; // ������ ������ �������� ����..

void solve(int hang, int yal, int num);

int main() {
	result = 987654321;
	for (int hang = 0; hang < 10; hang++) {
		for (int yal = 0; yal < 10; yal++) {
			scanf("%d", &board[hang][yal]);
			if (board[hang][yal] == 1) paper_num++;
		}
	}
	solve(0, 0, paper_num); // 0, 0���� �����Ͽ� Ž���� �����Ѵ�..
	if (result == 987654321) printf("-1\n");
	else printf("%d\n", result);
	return 0;
}

bool go_find(int i, int j, int s) { // �����̸� ���� �� �ִ��� �Ǵ�..
	if (i + s > 10 || j + s > 10) return false; // ������ �Ѿ�� ������ ���ϹǷ� return false
	if (paper[s] == 0) return false; // �������� ������ �������� ������ ������ ���ϹǷ� return false

	for (int hang = i; hang < i + s; hang++) {
		for (int yal = j; yal < j + s; yal++) {
			if (board[hang][yal] == 0) return false; // �����̸� ���̴ٰ� �߰��� ������ �ʾƵ� �Ǵ� ���� ��Ÿ���� return false..
		}
	}
	return true; // s�� ũ���� �����̷� ������ ���� �� �����Ƿ� return true..
}

void erase(int i, int j, int s, int n) {
	for (int hang = i; hang < i + s; hang++) {
		for (int yal = j; yal < j + s; yal++) {
			board[hang][yal] = n;
		}
	}
}

void solve(int hang, int yal, int num) {

	if (yal == 10) { // yal�� 10�̸� ���� ����� ���ߵǹǷ� hang�� 1������Ű�� yal�� 0���� �����.
		hang++; yal = 0;
	}
	if (num == 0) { // 1�� ������ ��� ��������
		int sum = 0;
		for (int i = 1; i <= 5; i++) {
			sum += 5 - paper[i]; // ������ ������ �����̴� 5���� �־����Ƿ� 5������ ���� paper�� ���� ������� �����.
		}
		if (result > sum) result = sum; // ����� ����..

		return;
	}
	if (hang == 10) return; // hang�� 10�� �Ǹ� 0,0 ���� 9,9 ���� ��� �� ���̹Ƿ� return..

	if (board[hang][yal] == 1) { // 0,0���� 9,9���� ���鼭 1�� ������ ��..

		for (int sz = 5; sz >= 1; sz--) { // ����ū�ͺ��� �ٿ����� �������� ������ ���� ���� �� �����Ƿ�..
			bool flag = go_find(hang, yal, sz); // ������� �����̷� ���� �� �ִ��� �Ǵ�..
			if (flag) {// ���� ���� �� �ִ� �����̰� �ȴٸ�..
				erase(hang, yal, sz, 0); //10 *10�� �����̿��� 1 --> 0���� �ٲ��ְ�
				num -= sz * sz; // �ٿ���ߵǴ� 1�� ������ ����.
				paper[sz]--; // ���� �� �ִ� �������� ������ �Ѱ� ���ش�..

				solve(hang, yal + sz, num); // ���̰� �� ���� yal �� ���� ũ���� sz��ŭ �������� ���..
				paper[sz]++; // recover..
				num += sz * sz;
				erase(hang, yal, sz, 1);
			}
		}
	}
	else solve(hang, yal + 1, num); // ���� 0�̶�� yal�� 1 �����Ͽ� ���..


}