#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
using namespace std;

char str[105];

int main() {
	//입력 ' '(공백)이 포함된 문자열이므로 %[^\n]s를 활용하여 공백도 같이 넣어주도록 하였다.
	scanf("%[^\n]s", str);
	for (int s = 0; str[s] != '\0'; s++) {
		//문자열을 돌면서 a~z안의 문자는 바꿔서 넣는데 문자에 +13을 더해줬을 때 127이 넘어가면 이상한 문자가 나오므로 나눠서 생각한다.
		if (str[s] >= 'a' && str[s] <= 'r') {
			str[s] += 13;
			if (str[s] > 'z') {
				str[s] = str[s] - 'z' + 'a' -1;
			}
			printf("%c", str[s]);
		}
		else if (str[s] > 'r' && str[s] <= 'z') {
			str[s] = str[s] - 'z' + 'a' +12;
			printf("%c", str[s]);
		}
		// 127이 넘어가지 않으므로 A~Z까지의 문자를 바꿔준다.
		else if (str[s] >= 'A' && str[s] <= 'Z') {
			str[s] += 13;
			if (str[s] > 'Z') str[s] = str[s] - 'Z' + 'A' - 1;
			printf("%c", str[s]);
		}
		//나머지는 그대로 출력한다.
		else printf("%c", str[s]);
	}

	return 0;
}