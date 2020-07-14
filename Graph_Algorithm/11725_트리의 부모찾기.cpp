#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N;
int board[100001];
int check[100001];

// ���⼺�� ���� ������ vector�� �ֱ�����
vector<int> Vec[100001];
// �θ� ���� ���� �ڽĵ��� �����ϱ� ����..
queue<int> Q;

void solve(int start);

int main() {
	//�Է�
	scanf("%d", &N);
	for (int a, b, i = 1; i < N; i++) {
		scanf("%d %d", &a, &b);
		Vec[a].push_back(b);
		Vec[b].push_back(a);
	}
	solve(1);
	//���
	for (int s = 2; s <= N; s++) {
		printf("%d\n", board[s]);
	}
	return 0;
}
// �����θ��� 1���� ����..
void solve(int start) {
	check[start] = true;
	Q.push(start);

	while (!Q.empty()) {
		// �θ� ���� ���� �ڽĵ��� �θ� �Ǿ ���� �ڽĵ��� ã�� �� �ֵ���..(�������ʰ�) Q_size�� �����ش�.
		int Qsz = Q.size();
		for (int s = 0; s < Qsz; s++) {
			int p = Q.front();
			Q.pop();
			// �� �θ� ���� �ڽ��� �� �� �ִ����� �Ǵ��ؼ� Q�� �־��ش�.
			for (int i = 0; i < Vec[p].size(); i++) {
				int son = Vec[p][i];
				// ���� check�迭�� true ���ٸ� �����θ�κ��� �����ؼ� ���� �ڽ����� �Ǹ��� �� ����� ����.
				if (!check[son]) {
					check[son] = true;
					Q.push(son);
					board[son] = p;
				}
			}
		}
	}
}