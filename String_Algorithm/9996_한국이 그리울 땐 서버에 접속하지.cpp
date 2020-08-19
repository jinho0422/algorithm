#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

int N;
char str[102];
bool check[102];
bool checkFlag;
vector<char> F;
vector<char> E;

int main() {
	//입력
	scanf("%d", &N);
	scanf("%s", str);
	bool flag = false;
	// * 이전의 char 값은 F에 넣고 이후의 값은 E vector에 넣는다..
	for (int s = 0; str[s] != '\0'; s++) {
		if (str[s] == '*') {
			flag = true;
			continue;
		}
		if (!flag) F.push_back(str[s]);
		else E.push_back(str[s]);
	}
	for (int s = 0; s < N; s++) {
		scanf("%s", str);
		int cnt = 0;
		checkFlag = false;
		// string의 길이를 찾아서
		while (str[cnt] != '\0') cnt++;
		// 만약 string 파일의 길이가 F + E 의 값보다 더 작으면 판단할 수 없으므로 NE 출력
		if (cnt < F.size() + E.size()) {
			printf("NE\n");
			continue;
		}
		else {
			// 앞쪽의 스트링을 F와 비교하고
			for (int i = 0; i < F.size(); i++) {
				if (str[i] == F[i] && !check[i]) check[i] = true;
				else {
					checkFlag = true;
					break;
				}
			}
			// 뒤쪽의 스트링을 E와 비교해서
			for (int i = 0; i < E.size(); i++) {
				if (str[cnt - E.size() + i] == E[i] && !check[cnt - E.size() + i]) check[cnt - E.size() + i] = true;
				else {
					checkFlag = true;
					break;
				}
			}
		}
		//출력
		if (checkFlag) printf("NE\n");
		else printf("DA\n");
		memset(check, false, sizeof(check));
	}
	return 0;
}