#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, K;
bool check[100003];
int parent[100003]; // �θ� �����ϱ� ���� �迭..
int result;
queue<int> Q;
vector<int> Vec; // ������ ã�� �� ���ݱ��� �Դ� ��θ� ã�� ����.

void BFS(int start);

int main() {
	//�Է�
	scanf("%d %d", &N, &K);
	BFS(N);
	//���
	printf("%d\n", result);
	for (int s = Vec.size() - 1; s >= 0; s--) {
		printf("%d ", Vec[s]);
	}
	printf("\n");
	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(start);

	while (!Q.empty()) {
		int sz = Q.size(); // �ð��� ���� �������� �ľ��ϱ����� Q.size��ŭ�� ������.
		for (int s = 0; s < sz; s++) {
			int p = Q.front();
			Q.pop();
			if (p == K) { // ���� ������ ã����
				Vec.push_back(K);
				int id = p; // ������ ��ġ���� �θ� ã�� �����Ͽ� Vector�� �ִ´�.
				while (id != N) {
					Vec.push_back(parent[id]);
					id = parent[id];
				}
				return;
			}
			// +1, -1, * 2�� �ϸ鼭 �θ� parent�迭�� ������ ����..
			if (p + 1 <= 100000) {
				if (!check[p + 1]) {
					check[p + 1] = true;
					Q.push(p + 1);
					parent[p + 1] = p;
				}
			}
			if (p - 1 >= 0) {
				if (!check[p - 1]) {
					check[p - 1] = true;
					Q.push(p - 1);
					parent[p - 1] = p;
				}
			}
			if (p * 2 <= 100000) {
				if (!check[p * 2]) {
					check[p * 2] = true;
					Q.push(p * 2);
					parent[p * 2] = p;
				}
			}
		}
		result++;
	}
}