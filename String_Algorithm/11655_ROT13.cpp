#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>
using namespace std;

char str[105];

int main() {
	//�Է� ' '(����)�� ���Ե� ���ڿ��̹Ƿ� %[^\n]s�� Ȱ���Ͽ� ���鵵 ���� �־��ֵ��� �Ͽ���.
	scanf("%[^\n]s", str);
	for (int s = 0; str[s] != '\0'; s++) {
		//���ڿ��� ���鼭 a~z���� ���ڴ� �ٲ㼭 �ִµ� ���ڿ� +13�� �������� �� 127�� �Ѿ�� �̻��� ���ڰ� �����Ƿ� ������ �����Ѵ�.
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
		// 127�� �Ѿ�� �����Ƿ� A~Z������ ���ڸ� �ٲ��ش�.
		else if (str[s] >= 'A' && str[s] <= 'Z') {
			str[s] += 13;
			if (str[s] > 'Z') str[s] = str[s] - 'Z' + 'A' - 1;
			printf("%c", str[s]);
		}
		//�������� �״�� ����Ѵ�.
		else printf("%c", str[s]);
	}

	return 0;
}