#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, Q;
bool check[5001];
int finalResult;

typedef struct _pos {
	int B, W;
}pos;

vector<pos> Vec[5001]; // ����� �������� usado�� �־� ���´�.. 
vector<int> result[5001]; // �� �����󿡼� ������ ��������� usado�� �ּҸ� �ִ´�.
queue<pos> Qq;

void BFS(int start,int maxU);

int main() {
	//�Է�
	scanf("%d %d", &N, &Q);
	for (int p, q, r, i = 0; i < N - 1; i++) {
		scanf("%d %d %d", &p, &q, &r);
		Vec[p].push_back(pos({ q, r }));
		Vec[q].push_back(pos({ p, r }));
	}
	// �� �����󿡼� ������ �������� ���絵�� �ּҸ� ã�´�.
	for (int i = 1; i <= N; i++) {
		memset(check, false, sizeof(check)); // �� �����󿡼� �� �������� ���絵�� ã������ �湮 �ʱ�ȭ..
		BFS(i, 1000000001);
	}
	//���
	for (int k, v, i = 0; i < Q; i++) {
		finalResult = 0; // �����
		scanf("%d %d", &k, &v);
		for (int j = 0; j < result[v].size(); j++) {
			if (k <= result[v][j]) finalResult++;
		}
		printf("%d\n", finalResult);
	}
	return 0;
}

void BFS(int start, int maxU) {

	check[start] = true;
	Qq.push(pos({ start, maxU }));

	while (!Qq.empty()) {
		pos p = Qq.front();
		Qq.pop();

		int sz = Vec[p.B].size();

		for (int s = 0; s < sz; s++) {
			int first = Vec[p.B][s].B;
			int second = Vec[p.B][s].W;

			if (!check[first]) {
				check[first] = true;
				// ���� ������ �����󿡼� ����� ���������ΰ��� ���絵�� �� ���� ����� ���絵 ���� Ŭ��..
				if (second > p.W) {
					result[start].push_back(p.W);
					Qq.push(pos({ first, p.W }));
				}
				// ���� ��
				else {
					result[start].push_back(second);
					Qq.push(pos({ first, second }));
				}
			}
		}
	}
}