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
	//�Է�
	scanf("%d", &N);
	scanf("%s", str);
	bool flag = false;
	// * ������ char ���� F�� �ְ� ������ ���� E vector�� �ִ´�..
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
		// string�� ���̸� ã�Ƽ�
		while (str[cnt] != '\0') cnt++;
		// ���� string ������ ���̰� F + E �� ������ �� ������ �Ǵ��� �� �����Ƿ� NE ���
		if (cnt < F.size() + E.size()) {
			printf("NE\n");
			continue;
		}
		else {
			// ������ ��Ʈ���� F�� ���ϰ�
			for (int i = 0; i < F.size(); i++) {
				if (str[i] == F[i] && !check[i]) check[i] = true;
				else {
					checkFlag = true;
					break;
				}
			}
			// ������ ��Ʈ���� E�� ���ؼ�
			for (int i = 0; i < E.size(); i++) {
				if (str[cnt - E.size() + i] == E[i] && !check[cnt - E.size() + i]) check[cnt - E.size() + i] = true;
				else {
					checkFlag = true;
					break;
				}
			}
		}
		//���
		if (checkFlag) printf("NE\n");
		else printf("DA\n");
		memset(check, false, sizeof(check));
	}
	return 0;
}