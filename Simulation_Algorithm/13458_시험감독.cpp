#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N;
int board[1000001];
int first, second;
long long result;

int main() {
	//�Է�
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &board[i]);
	}
	//first : �Ѱ����� ���� �� �ִ� �ο�, second : �� ������ ���� �� �ִ� �ο�
	scanf("%d %d", &first, &second);
	result = N; // �Ѱ����� �׻� ����忡 �Ѹ� �־�ߵǹǷ�
	for (int i = 0; i < N; i++) {
		int s = board[i] - first; // ������ο����� �Ѱ����� ���� �� �ο��� ����
		if (s <= 0) continue; // 0���� ������ continue..
		result += (s / second); // ���� result�� �����ְ�
		int f = s % second;  
		if (f != 0) result++; //�������� ������ �ΰ����� �Ѹ� �� ���Խ�Ų��..
	}
	// ���
	printf("%lld\n", result);
	return 0;
}