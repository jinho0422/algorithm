#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <string>

using namespace std;

char str[21];
string s;

int main() {
	while (1) {
		//입력
		scanf("%s", str);
		s = str;
		// 입력이 end break;;
		if (str[0] == 'e' && str[1] == 'n' && str[2] == 'd' && s.length() == 3) {
			break;
		}
		bool vowel = false; // 모음 체크
		bool continuity = false; // 'e', 'o'를 제외하고 연속된 문자가 나오는지 체크
		bool cntCheck = false; // 자음 또는 모음이 연속되게 3번이상 나오는지 체크
		char beforChar = str[0]; // for문에서 이전 문자를 저장..
		int vowelcnt = 0; // 연속된 모음갯수 
		int consonantcnt = 0; // 연속된 자음갯수
		// 비밀번호를 보면서
		for (int i = 0; i < s.length(); i++) {
			//모음이 나타나면 vowel == true, 모음 연속갯수 증가, 자음 연속갯수 초기화
			if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
				vowel = true;
				vowelcnt++;
				consonantcnt = 0;
			}
			// 자으미면 모음 연속갯수 초기화 자음연속갯수 증가
			else {
				vowelcnt = 0;
				consonantcnt++;
			}
			// 만약 모음 또는 자음이 3번 연속되면 cntCheck true..
			if (vowelcnt == 3 || consonantcnt == 3) cntCheck = true;
			
			// 비밀번호의 처음이 아니고 현재의 문자가 e 나 o가 아니면 전의 문자와 비교해서 같으면 continuity true
			if (i != 0) {
				if (s[i] != 'e' && s[i] != 'o') {
					if (beforChar == s[i]) continuity = true;
				}
			}
			//이전문자 갱신..
			beforChar = str[i];
		}
		//출력
		printf("<");
		for (int j = 0; j < s.length(); j++) printf("%c", s[j]);	
		printf(">");
		if (vowel && !cntCheck && !continuity) printf(" is acceptable.\n");	
		else printf(" is not acceptable.\n");
	}
	return 0;
}