#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, L;
int station;
int startA, endA;
bool check[100001];

typedef struct _pos {
	int bus, cnt; // bus : ������ ��ȣ, cnt : ȯ�� Ƚ��
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.cnt > q.cnt;
	}
};
priority_queue<pos, vector<pos>, cmp> Q; // �ּҷ� ȯ���� �ͺ��� ���� ���� priority_queue���

vector<int> stationBus[100001]; // ������ Ż �� �ִ� ���� ��ȣ�� ����..
vector<int> nosion[100001]; // �� ������ �� �� �ִ� ���� ����..

int BFS(int startA);

int main() {
	//�Է�
	scanf("%d %d", &N, &L);
	for (int i = 0; i < L; i++) {
		while (1) {
			scanf("%d", &station);
			if (station == -1) break;
			stationBus[station].push_back(i); // ������ Ż �� �ִ� ���� ����..
			nosion[i].push_back(station); // ������ �� �� �ִ� ���� ����..
		}
	}
	scanf("%d %d", &startA, &endA);
	//���
	printf("%d\n", BFS(startA));
	
	return 0;
}

int BFS(int startA) {
	check[startA] = true;
	// �����ϴ� ������ Ż �� �ִ� ������ priorityQueue�� ����..
	for (int i = 0; i < stationBus[startA].size(); i++) {
		Q.push(pos({ stationBus[startA][i], 0 }));
	}
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.top();
			Q.pop();
			int bussz = nosion[p.bus].size();
			// ź ������ �� �� �ִ� ��� ���� ����..
			for (int j = 0; j < bussz; j++) {
				// �����ϴ� ���� ��Ÿ���� return ȯ�� Ƚ����..
				if (nosion[p.bus][j] == endA) return p.cnt;
				if (!check[nosion[p.bus][j]]) {
					check[nosion[p.bus][j]] = true;
					// ���� �� ������ �ٸ� ������ ����Ż �� ������
					if (stationBus[nosion[p.bus][j]].size() != 1) {
						for (int i = 0; i < stationBus[nosion[p.bus][j]].size(); i++) {
							if (stationBus[nosion[p.bus][j]][i] != p.bus) { // ������ ������ �ƴϸ� �� ������ ��ȣ�� ȯ�°����� �������� Q�� �ִ´�.
								Q.push(pos({ stationBus[nosion[p.bus][j]][i], p.cnt + 1 }));
							}
						}
					}
				}
			}
		}
	}
	return -1;
}