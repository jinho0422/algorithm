#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
int board[100001];


//싸지방을 이용하는 병사들을 vector에 넣기위해
typedef struct _pos {
	int sa, en;
}pos;
// 싸지방을 이용하는 자리와 끝나는 시간을 priority_queue에 넣기위해
typedef struct _posQ {
	int n, e;
}posQ;
// 싸지방을 이용하는 병사의 시작시간순으로 정렬하기위해
bool cmp(const pos& p, const pos& q) {
	return p.sa < q.sa;
};
// 싸지방이 끝나는 시간순서대로 정렬하기위해..
struct cmp1 {
	bool operator() (posQ p, posQ q) {
		return p.e > q.e;
	}
};
// 병사가 싸지방 자리 위치와 끝나는 시간을 정렬하여 넣은 priority_queue
priority_queue<posQ, vector<posQ>, cmp1> location;
//싸지방을 이용하는 병사의 시작시간과 끝나는 시간을 저장하는 vector
vector<pos> Vec;
// 이용할 수 있는 자리를 앞자리부터 정렬하기 위한 priority_queue
priority_queue<int, vector<int>, greater<int>> bin;


int main() {
	//입력
	scanf("%d", &N);
	for (int start, endd, s = 0; s < N; s++) {
		scanf("%d %d", &start, &endd);
		Vec.push_back(pos({ start, endd }));
	}
	// 시작시간이 빠른 순서대로 정렬..
	sort(Vec.begin(), Vec.end(), cmp);
	
	for (int s = 0; s < Vec.size(); s++) {
		// 시작하는 사람이 들어왔을 때 끝나고 나간 자리를 뽑아오기 위해..
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
		//빈자리가 없으면 새로운 자리에서 시작..
		if (binSz == 0) {
			int locationSz = location.size();
			board[locationSz]++;
			location.push(posQ({ locationSz, Vec[s].en }));
		}
		//빈자리가 있으면 맨 앞자리에 착석..
		else {
			int q = bin.top();
			bin.pop();
			board[q]++;
			location.push(posQ({q, Vec[s].en}));
		}
	}
	//출력..
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