#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <queue>

using namespace std;

int N, L;
int station;
int startA, endA;
bool check[100001];

typedef struct _pos {
	int bus, cnt; // bus : 버스의 번호, cnt : 환승 횟수
}pos;

struct cmp {
	bool operator() (pos p, pos q) {
		return p.cnt > q.cnt;
	}
};
priority_queue<pos, vector<pos>, cmp> Q; // 최소로 환승한 것부터 보기 위해 priority_queue사용

vector<int> stationBus[100001]; // 역에서 탈 수 있는 버스 번호를 저장..
vector<int> nosion[100001]; // 각 버스가 갈 수 있는 역을 저장..

int BFS(int startA);

int main() {
	//입력
	scanf("%d %d", &N, &L);
	for (int i = 0; i < L; i++) {
		while (1) {
			scanf("%d", &station);
			if (station == -1) break;
			stationBus[station].push_back(i); // 역에서 탈 수 있는 버스 저장..
			nosion[i].push_back(station); // 버스가 갈 수 있는 역을 저장..
		}
	}
	scanf("%d %d", &startA, &endA);
	//출력
	printf("%d\n", BFS(startA));
	
	return 0;
}

int BFS(int startA) {
	check[startA] = true;
	// 시작하는 역에서 탈 수 있는 버스를 priorityQueue에 저장..
	for (int i = 0; i < stationBus[startA].size(); i++) {
		Q.push(pos({ stationBus[startA][i], 0 }));
	}
	while (!Q.empty()) {
		int sz = Q.size();
		for (int s = 0; s < sz; s++) {
			pos p = Q.top();
			Q.pop();
			int bussz = nosion[p.bus].size();
			// 탄 버스로 갈 수 있는 모든 역을 간다..
			for (int j = 0; j < bussz; j++) {
				// 가야하는 역이 나타나면 return 환승 횟수를..
				if (nosion[p.bus][j] == endA) return p.cnt;
				if (!check[nosion[p.bus][j]]) {
					check[nosion[p.bus][j]] = true;
					// 만약 간 역에서 다른 버스로 갈아탈 수 있으면
					if (stationBus[nosion[p.bus][j]].size() != 1) {
						for (int i = 0; i < stationBus[nosion[p.bus][j]].size(); i++) {
							if (stationBus[nosion[p.bus][j]][i] != p.bus) { // 현재의 버스가 아니면 그 버스의 번호와 환승갯수를 증가시켜 Q에 넣는다.
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