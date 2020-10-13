#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, num;
int board[101]; // �����ؾߵ� ���� �ִ� �迭
int oper[100]; // �����ڰ� ����ִ� �迭 0 : +, 1 : -, 2 : *, 3 : / 
int tmpOper[100]; // �����ڸ� ������ ���� ������ �迭
bool check[101]; 
int maxResult, minResult; // �ִ밪, �ּҰ�

void DFS(int depth);

int main() {
	//�Է�
	maxResult = -2000000000;
	minResult = 2000000000;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	num = 0;
	for (int a, i = 0; i < 4; i++) {
		scanf("%d", &a);
		for (int j = 0; j < a; j++) {
			oper[num++] = i; // �����ڸ� ���ڷ� �ֱ�..
		}
	}
	DFS(0);
	printf("%d\n%d\n", maxResult, minResult);
	return 0;
}
// ����
int operating(int s, int sums, int nextNum ) {
	if (s == 0) sums += nextNum;
	else if (s == 1) sums -= nextNum;
	else if (s == 2) sums *= nextNum;
	else if (s == 3) sums /= nextNum;
	return sums;
}
//������ ���� �����ڸ� ��� ���� �����ϱ�..
void DFS(int depth) {
	if (depth == N -1) {
		int sum = board[0];
		for (int i = 0; i < depth; i++) {
			sum = operating(tmpOper[i], sum, board[i + 1]);
		}
		//���������..
		if (maxResult < sum) maxResult = sum;
		if (minResult > sum) minResult = sum;
		return;
	}
	for (int i = 0; i < num; i++) {
		if (!check[i]) {
			check[i] = true;
			tmpOper[depth] = oper[i];
			DFS(depth + 1);
			tmpOper[depth] = 0;
			check[i] = false;
		}
	}
}