#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

int N, M;
int board[15001];
bool check[10000001];
int result;

int main() {
	//�Է�
	scanf("%d %d", &N, &M);
	// ����� ������ȣ�� board�� �־��ְ� ��ᰡ �ִ� ��ȣ�� check = true���ش�..
	for (int a, s = 0; s < N; s++) {
		scanf("%d", &a);
		board[s] = a;
		check[a] = true;
	}
	// ��� ��Ḧ ���鼭
	for (int s = 0; s < N; s++) {
		// ������ ����µ� �ʿ��� ��ȣ���� ����
		int first = M - board[s];
		// ������ ��ȣ�̹Ƿ� ������ ���� �� ���� ������ ���� �����̹Ƿ� continue.. ������ ������ continue(����������Ƿ�)
		if (first == board[s] || first <= 0) {
			continue;
		}
		if (check[M - board[s]]) result++;
	}
	// ������ �� �� ����̹Ƿ� ��������� /2�� ���ش�.
	printf("%d\n", result / 2);

	return 0;
}