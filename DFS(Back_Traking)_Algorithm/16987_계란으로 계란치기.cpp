/*
	������� ���ġ��� ���ʺ��� ���������� ����� �̵��ϸ鼭 ����� �������ִ�
	�������� ���Ը� �������� �������� �ȱ����� �Ǵ��ϴ� �����̴�.

	���Ʈ����(���)�� �̿��Ͽ� Ǯ��Ҵ�.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;


int N;
bool check[8];
int result;

typedef struct _pos {// ��� ������ �������� ���Ը� �ޱ�����..
	int S, W;
}pos;

vector<pos> Vec; // ������ ����� ���Կ� �������� ����..

void solve(int depth);

int main() {
	scanf("%d", &N);
	for (int s, w, i = 0; i < N; i++) {
		scanf("%d %d", &s, &w);
		Vec.push_back(pos({ s, w }));
	}

	solve(0);
	printf("%d\n", result);


	return 0;
}

void solve(int depth) { // depth�� ���ʰ������ ���������� ����� ����..

	if (depth == N) { // �� ������ ����� ������ ���� ����������� �Ǵ�.
		int cnt = 0;
		for (int i = 0; i < depth; i++) {
			if (check[i]) cnt++;
		}
		if (result < cnt) result = cnt;
		return;
	}

	if (check[depth]) solve(depth + 1); // ����� �տ� ����� �� ��������̸� �Ѿ��.


	else {
		bool flag = false;

		for (int s = 0; s < Vec.size(); s++) {// �տ� ����ִ°������ �� �� �ִ� ��� ��� �Ǵ�..

			if (depth == s) continue; // �տ� ����ִ� ����� ���� ����̸� �Ѿ��..

			if (!check[s]) {
				flag = true;
				int prevFirst = Vec[depth].S;
				int prevSecond = Vec[s].S;

				Vec[depth].S -= Vec[s].W; // �տ� ����ִ°�� ������..
				Vec[s].S -= Vec[depth].W; // �տ� ����ִ� ������� �ϳ��� ����� �� ������..

				if (Vec[depth].S <= 0) check[depth] = true; // ����� �������� check == true
				if (Vec[s].S <= 0) check[s] = true;

				solve(depth + 1); 
				check[depth] = false; // recover..
				check[s] = false;
				Vec[depth].S = prevFirst;
				Vec[s].S = prevSecond;
			}
		}

		if (!flag) solve(depth + 1); // �ƹ��͵� �� ���� ���� �� �׳� �������� ���..
	}
}