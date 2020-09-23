#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int N, M;

// 내림차순을 위한 정렬
bool cmp(const int p, const int q) {
	if (p > q) return true;
	return false;
}
vector<int> crain; // 크레인이들어있는 vector
vector<int> box; // box의 무게가 들어있는 vector

int main() {
	//입력
	scanf("%d", &N);
	for (int a, i = 0; i < N; i++) {
		scanf("%d", &a);
		crain.push_back(a);
	}
	scanf("%d", &M);
	for (int a, i = 0; i < M; i++) {
		scanf("%d", &a);
		box.push_back(a);
	}
	// 각각 내림차순 정렬
	sort(crain.begin(), crain.end(), cmp);
	sort(box.begin(), box.end(), cmp);
	//만약 크레인이 옮길수없는 박스무게가 있으면 -1 출력
	if (crain[0] < box[0]) {
		printf("-1\n");
		return 0;
	}
	int time = 0; // 결과값
	// 크레인 당 박스를 보며 만약 박스의 크기가 크레인의 크기보다 작거나 같으면
	while (1) {
		for (int i = 0; i < crain.size(); i++) {
			for (int j = 0; j < box.size(); j++) {
				if (crain[i] >= box[j]) {
					box.erase(box.begin() + j); // vector의 erase를 통해 제거
					break;
				}
			}
		}
		time++;
		if (box.size() == 0) break; // 박스를 모두 옮겼으면 break..
	}
	//출력
	printf("%d\n", time);
	return 0;
}