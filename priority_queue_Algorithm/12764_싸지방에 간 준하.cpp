#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int board[100001];


//�������� �̿��ϴ� ������� vector�� �ֱ�����
typedef struct _pos {
	int sa, en;
}pos;
// �������� �̿��ϴ� �ڸ��� ������ �ð��� priority_queue�� �ֱ�����
typedef struct _posQ {
	int n, e;
}posQ;
// �������� �̿��ϴ� ������ ���۽ð������� �����ϱ�����
bool cmp(const pos& p, const pos& q) {
	return p.sa < q.sa;
};
// �������� ������ �ð�������� �����ϱ�����..
struct cmp1 {
	bool operator() (posQ p, posQ q) {
		return p.e > q.e;
	}
};
// ���簡 ������ �ڸ� ��ġ�� ������ �ð��� �����Ͽ� ���� priority_queue
priority_queue<posQ, vector<posQ>, cmp1> location;
//�������� �̿��ϴ� ������ ���۽ð��� ������ �ð��� �����ϴ� vector
vector<pos> Vec;
// �̿��� �� �ִ� �ڸ��� ���ڸ����� �����ϱ� ���� priority_queue
priority_queue<int, vector<int>, greater<int>> bin;


int main() {
	//�Է�
	scanf("%d", &N);
	for (int start, endd, s = 0; s < N; s++) {
		scanf("%d %d", &start, &endd);
		Vec.push_back(pos({ start, endd }));
	}
	// ���۽ð��� ���� ������� ����..
	sort(Vec.begin(), Vec.end(), cmp);
	
	for (int s = 0; s < Vec.size(); s++) {
		// �����ϴ� ����� ������ �� ������ ���� �ڸ��� �̾ƿ��� ����..
		while (1) {
			if (location.size() == 0) break;
			posQ p = location.top();
			if (p.e < Vec[s].sa) {
				bin.push(p.n);
				location.pop();
			}
			else break;
		}

		int binSz = bin.size();
		//���ڸ��� ������ ���ο� �ڸ����� ����..
		if (binSz == 0) {
			int locationSz = location.size();
			board[locationSz]++;
			location.push(posQ({ locationSz, Vec[s].en }));
		}
		//���ڸ��� ������ �� ���ڸ��� ����..
		else {
			int q = bin.top();
			bin.pop();
			board[q]++;
			location.push(posQ({q, Vec[s].en}));
		}
	}
	//���..
	int maxSize = 0;
	while (1) {
		if (board[maxSize] == 0) break;
		maxSize++;
	}
	printf("%d\n", maxSize);
	for (int s = 0; s < maxSize; s++) {
		printf("%d ", board[s]);
	}
	printf("\n");
	return 0;
}