#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int N, M;
typedef struct _pos {
	int n, f; // n : ������ �ִ� ��ġ, f : �߿䵵
}pos;

bool cmp(const int& p, const int& q) { // �������� ����
	return p > q;
};

deque<pos> Q;
vector<int> Vec; // �߿䵵 ����vector..

int BFS();

int main() {
	//�Է�
	int T; scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		scanf("%d %d", &N, &M);
		for (int a, i = 0; i < N; i++) {
			scanf("%d", &a);
			Q.push_back(pos({ i, a }));
			Vec.push_back(a);
		}
		sort(Vec.begin(), Vec.end(), cmp); // �������� ����
		int result = BFS();
		//���
		printf("%d\n", result);
		//�ʱ�ȭ..
		while (!Q.empty()) Q.pop_back();
		Vec.clear();
	}
	return 0;
}

int BFS() {
	int time = 0; // �����
	int check = 0; // Vec�� �߿䵵�� �ٷ������..
	while (!Q.empty()) {
		pos p = Q.front();
		Q.pop_front();
		if(p.f == Vec[check] && p.n == M) { // �߿䵵�� ���� �˰���� �����̸�..
			time++;
			return time;
		}
		else if (p.f == Vec[check] && p.n != M) { // �߿䵵�� ������ �˰���� ������ �ƴҽ�
			time++;
			check++;
		}
		else if (p.f != Vec[check]) { // �߿䵵�� ���� ������..
			Q.push_back(pos({ p.n, p.f }));
		}
	}
}