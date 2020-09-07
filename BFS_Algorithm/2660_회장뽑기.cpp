#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int N, a, b;
bool check[51];
int result;

typedef struct _pos {
	int n, c; // n : ��ȣ, c : ������� ��� ģ���� ����Ǵ���
}pos;
//����� ���� ����(�ּ��� ����� ������ �ռ������� ����)
bool cmp(const pos& p, const pos& q) {
	if (p.c == q.c) return p.n < q.n;
	return p.c < q.c;
}

vector<pos> link; // ������� ������ �ִ� vector
vector<int> Vec[51]; // ģ�����踦 ������ �ִ� vector
queue<int> Q;

void BFS(int start);

int main() {
	//�Է�
	scanf("%d", &N);
	while (1) {
		scanf("%d %d", &a, &b);
		if (a == -1 && b == -1) break;
		Vec[a].push_back(b); // a�� b�� ģ���� b�� a�� ģ���� �瓇����
		Vec[b].push_back(a);
	}
	//�� ȸ������ŭ BFS�� ���鼭 ������� ģ�������� �������� link������� �ִ´�.
	for (int i = 1; i <= N; i++) {
		BFS(i);
		//�ʱ�ȭ
		while (!Q.empty()) Q.pop();
		memset(check, false, sizeof(check));
	}
	// ����
	sort(link.begin(), link.end(), cmp);
	// ���
	for (int s = 0; s < link.size(); s++) {
		if (link[0].c == link[s].c) result++;
		else break;
	}
	printf("%d %d\n", link[0].c, result);
	for (int i = 0; i < result; i++) {
		printf("%d ", link[i].n);
	}
	printf("\n");
	return 0;
}

void BFS(int start) {
	check[start] = true;
	Q.push(start);
	int time = 0; // ����� ����� ģ���� �Ǵ��� �Ǵ��ϴ� ����
	int cnt = 1; // ����� ����Ǿ��ִ��� �Ǵ��ϴ� ���
	while (!Q.empty()) {
		int qsz = Q.size();
		for (int i = 0; i < qsz; i++) {
			int p = Q.front();
			Q.pop();
			int vsz = Vec[p].size();
			for (int s = 0; s < vsz; s++) {
				if (!check[Vec[p][s]]) {
					check[Vec[p][s]] = true;
					Q.push(Vec[p][s]);
					cnt++;
					if (cnt == N) { // ��� ȸ���� ����Ǿ������� ������� �ְ� return.
						time++;
						link.push_back(pos({ start, time }));
						return;
					}
				}
			}
		}
		time++;
	}
}