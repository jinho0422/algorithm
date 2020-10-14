#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
using namespace std;

int N;
int board[51][10]; // �� �̴׿��� �������� Ÿ�������� ��Ȳ
int check[10];
int player[10]; // ������ �������� �ִ� �迭
int scoreResult; // �����

deque<int> Q; // ������ ������ �ִ´�..
vector<int> Vec; // �� �̴׺� ����ȹ�� ��Ȳ�� ���� ����..

void DFS(int depth);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int hang = 1; hang <= N; hang++) {
		for (int yal = 1; yal <= 9; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	DFS(1);
	printf("%d\n", scoreResult);
	return 0;
}

int score() {
	int cnt = 0; // ������ �������� �� �� �ִ� �� ���ڿ�
	for (int hang = 1; hang <= N; hang++) {
		int out = 0; // out
		while (!Q.empty()) {
			int p = Q.front();
			Q.pop_front();

			if (board[hang][p] == 0) { // board[hang][yal] == 0 �̸� �ƿ��� ��Ȳ�̱� ������ out++
				out++;
				Q.push_back(p); // ���� �̴��� ���� front���� back���� �־��ش�..(ȸ��)
				if (out == 3) break; // out�� 3���̸� �̴� ����
			}
			else { // board[hang][yal] != 0 �̸� ��Ÿ�� ģ ����̹Ƿ�
				Q.push_back(p); 
				Vec.push_back(1);// ��Ÿģ ����� 1�� ǥ���ϰ� �������� 0���� �Ѵ�..
				for (int i = 1; i < board[hang][p]; i++) Vec.push_back(0);			
			}
		}
		int sz = Vec.size();
		if (sz >= 4) {// sz�� 4�̻��̸� ������ ���� �� �ִ� ��Ȳ�̹Ƿ� Vec�� 1�� �ִ��� 1�� 2�� 3�縦 ���� ����..
			for (int i = 0; i < sz - 3; i++) {
				if (Vec[i] == 1) cnt++;
			}
		}
		Vec.clear(); // �̴� ���� �� ���̽� �ʱ�ȭ
	}
	return cnt;
}
// 1~9�������� �� ������ ����
void DFS(int depth) {
	if (depth == 4) DFS(depth + 1); // 4������ 1�������� �־�ߵǱ⶧����..
	if (depth == 10) {
		player[4] = 1;
		while (!Q.empty()) Q.pop_front();// �ʱ�ȭ
		for (int i = 1; i < depth; i++) Q.push_back(player[i]);
		int result = score();
		if (scoreResult < result) scoreResult = result; // ����� ����..
		return;
	}
	for (int s = 2; s <= 9; s++) {
		if (!check[s]) {
			check[s] = true;
			player[depth] = s;
			DFS(depth + 1);
			player[depth] = 0;
			check[s] = false;
		}
	}
}