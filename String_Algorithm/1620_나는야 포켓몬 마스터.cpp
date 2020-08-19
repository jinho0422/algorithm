#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int N, M;
char str[21];

string poket[100001];
map<string, int> poketmon; // map을 통해 포켓몬과 그에 맞는 번호를 만들어주기위해.

int main() {
	//입력
	scanf("%d %d", &N, &M);
 	for(int i = 1; i <= N; i++) {
		scanf("%s", str);
		poket[i] = str;
		poketmon.insert(make_pair(poket[i], i));
	}
	for (int i = 0; i < M; i++) {
		scanf("%s", str);
		if (str[0] >= '0' && str[0] <= '9') {
			int sum = 0;
			// 숫자이면 atoi를 통해 char를 int로 바꿔준다.
			sum = atoi(str);
			for (int s = 0; s < poket[sum].length(); s++) {
				printf("%c", poket[sum][s]);
			}
			printf("\n");
		}
		//포켓몬 이름이면 그에 맞는 번호를 뽑아준다.
		else printf("%d\n", poketmon.find(str)->second);
	}
	return 0;
}