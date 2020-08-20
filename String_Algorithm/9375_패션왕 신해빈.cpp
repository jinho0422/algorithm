#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int T;
char name[23];
char type[23];
int result;

//타입의 종류의 개수를 등록하기 위한 map
map<string, int> types;

int main() {
	scanf("%d", &T);
	for (int N, t = 0; t < T; t++) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			// 패션의 이름과 타입을 각각 받아서 map에 타입의 갯수를 저장한다.
			scanf("%s %s", name, type);
			types[type] += 1;
		}
		result = 1;
		// map을 처음부터 끝까지 갯수를 보면서 안입는거까지 +1를 하고 곱해준다.
		for (auto s = types.begin(); s != types.end(); s++) {
			int cnt = s->second;
			cnt++;
			result = result * cnt;
		}
		// 아무것도 안입은 것을 빼고 결과값 출력
		printf("%d\n", result - 1);
		//map을 초기화 시켜준다(다음 테스트를 위해)
		types.clear();
	}
	return 0;
}