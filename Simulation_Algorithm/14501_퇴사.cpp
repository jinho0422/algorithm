#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
using namespace std;

int N;
int result;

typedef struct _pos {
	int t, m; // t : ������ �ʿ��� �ð� m : �޴� ��
}pos;
vector<pos> Vec;

void DFS(int depth, int sum);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int a, b, i = 0; i < N; i++) {
		scanf("%d %d", &a, &b);
		Vec.push_back(pos({ a, b }));
	}
	DFS(0, 0);
	printf("%d\n", result);
	return 0;
}

void DFS(int depth, int sum) {
	if (depth <= N) { // ����� �������� ����� ����..
		if (result < sum) result = sum;
	}
	if (depth >= N) return; // ������� �Ѿ�� return..
	//�� �ñ⿡ ���� �ϴ°��
	if(depth + Vec[depth].t <= N) DFS(depth + Vec[depth].t, sum + Vec[depth].m);
	//���� ���ϰ� �Ѿ�� ���
	if (depth + 1 <= N) DFS(depth + 1, sum);
}