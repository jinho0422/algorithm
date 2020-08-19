#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
#include <map>

using namespace std;

int N, M;
char str[21];

string poket[100001];
map<string, int> poketmon; // map�� ���� ���ϸ�� �׿� �´� ��ȣ�� ������ֱ�����.

int main() {
	//�Է�
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
			// �����̸� atoi�� ���� char�� int�� �ٲ��ش�.
			sum = atoi(str);
			for (int s = 0; s < poket[sum].length(); s++) {
				printf("%c", poket[sum][s]);
			}
			printf("\n");
		}
		//���ϸ� �̸��̸� �׿� �´� ��ȣ�� �̾��ش�.
		else printf("%d\n", poketmon.find(str)->second);
	}
	return 0;
}