#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N, M;
int board[501][501];
int numbers[10001];

//������ ��ȣ(number)��, ������ ��ŷ����(cnt)
typedef struct _pos {
	int number, cnt;
}pos;


// ������ ������ �����ϱ����ؼ�.. ��ŷ������ ��������, ��ŷ������ ���ٸ� ���� ��ȣ�� ������������..
bool cmp (const pos& p, const pos& q) {
	if (p.cnt == q.cnt) return p.number < q.number;
	return p.cnt > q.cnt;
}
pos second[10001];

int main() {
	while (1) {
		//�Է�
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break;
		//���� ��ȣ�� ������� �ִ��� �Ǵ��ϱ� ���ؼ�
		int max_num = 0;
		for (int hang = 0; hang < N; hang++) {
			for (int yal = 0; yal < M; yal++) {
				scanf("%d", &board[hang][yal]);
				if (max_num < board[hang][yal]) max_num = board[hang][yal];
				numbers[board[hang][yal]]++;
			}
		}
		int player = 0;
		for (int i = 1; i <= max_num; i++) {
			if (numbers[i] != 0) {
				second[player++] = { i, numbers[i] };
			}
		}
		// cmp ������ ���� �����ϰ�, ��ŷ�� �ִ밪�� ���� �ϳ��̹Ƿ� ���� �� ��ŷ ���� ���� ������ ��������� print..
		sort(second, second + player, cmp);
		int secondFirst = second[1].cnt;
		for (int s = 1; s < player; s++) {
			if (second[s].cnt == secondFirst) {
				printf("%d ", second[s].number);
			}
			else break;
		}
		printf("\n");
		// ���� ���̽��� ���� ������ ������ ����ִ� numbers�迭 �ʱ�ȭ.
		memset(numbers, 0, sizeof(numbers));
	}

	return 0;
}