#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>

using namespace std;

char str[21];
string s;

int main() {
	while (1) {
		//�Է�
		scanf("%s", str);
		s = str;
		// �Է��� end break;;
		if (str[0] == 'e' && str[1] == 'n' && str[2] == 'd' && s.length() == 3) {
			break;
		}
		bool vowel = false; // ���� üũ
		bool continuity = false; // 'e', 'o'�� �����ϰ� ���ӵ� ���ڰ� �������� üũ
		bool cntCheck = false; // ���� �Ǵ� ������ ���ӵǰ� 3���̻� �������� üũ
		char beforChar = str[0]; // for������ ���� ���ڸ� ����..
		int vowelcnt = 0; // ���ӵ� �������� 
		int consonantcnt = 0; // ���ӵ� ��������
		// ��й�ȣ�� ���鼭
		for (int i = 0; i < s.length(); i++) {
			//������ ��Ÿ���� vowel == true, ���� ���Ӱ��� ����, ���� ���Ӱ��� �ʱ�ȭ
			if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
				vowel = true;
				vowelcnt++;
				consonantcnt = 0;
			}
			// �����̸� ���� ���Ӱ��� �ʱ�ȭ �������Ӱ��� ����
			else {
				vowelcnt = 0;
				consonantcnt++;
			}
			// ���� ���� �Ǵ� ������ 3�� ���ӵǸ� cntCheck true..
			if (vowelcnt == 3 || consonantcnt == 3) cntCheck = true;
			
			// ��й�ȣ�� ó���� �ƴϰ� ������ ���ڰ� e �� o�� �ƴϸ� ���� ���ڿ� ���ؼ� ������ continuity true
			if (i != 0) {
				if (s[i] != 'e' && s[i] != 'o') {
					if (beforChar == s[i]) continuity = true;
				}
			}
			//�������� ����..
			beforChar = str[i];
		}
		//���
		printf("<");
		for (int j = 0; j < s.length(); j++) printf("%c", s[j]);	
		printf(">");
		if (vowel && !cntCheck && !continuity) printf(" is acceptable.\n");	
		else printf(" is not acceptable.\n");
	}
	return 0;
}