#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

using namespace std;

char str[102];
char board[102][102];
int maxPalindrome;
int cnt;
int Palindrome;

int main() {
	int T;
	//freopen("test.txt", "r", stdin);
	for (int t = 1; t <= 10; t++) {
		// �ִ� ȸ�����ڱ��̸� �̱�����..
		maxPalindrome = 0;
		scanf("%d", &T);
		//�Է�
		for (int hang = 0; hang < 100; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < 100; yal++) {
				board[hang][yal] = str[yal];
			}
		}
		// ���ο��� ȸ���� �ִ� ���̸� ã������.. yal�� 98���� �� ������ �������� ���ؼ� ���Ƿ�.. 99��°�� ���� ���� ����.
		for (int hang = 0; hang < 100; hang++) {
			for (int yal = 0; yal < 99; yal++) {
				int tmpYal = yal;
				// ������ board���� ���� board���� ������ ¦������ ȸ�����̰� �����ǹǷ�.. ȸ������ 2�� �����ؼ� cnt�� �����ϸ� ó�� board�� yal������ �ڷ� cnt+, ������ cnt + 1�� ���ָ� ��
				if (board[hang][tmpYal] == board[hang][tmpYal + 1]) {
					Palindrome = 2;
					cnt = 1;
					while (1) {
						//������ �Ѿ�� �ִ밪�� �����ϰ� �������´�.
						if ((tmpYal - cnt) < 0 || (tmpYal + cnt + 1) > 99) {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}
						//������ ȸ���� �� +2 cnt++ 
						if (board[hang][tmpYal - cnt] == board[hang][tmpYal + cnt + 1]) {
							Palindrome += 2;
							cnt++;						
						}
						//�ٸ��� ȸ���� �ִ밪�� �����ϰ� �������´�.
						else {
							if (maxPalindrome < Palindrome ) maxPalindrome = Palindrome;
							break;
						}
					}
				}
				// Ȧ������ ȸ���� ���ö�..(board[hang][yal] != board[hang][yal+1)
				else {
					Palindrome = 1;
					cnt = 1;
					while (1) {
						// ������ �Ѿ�� �ִ밪�� �����ϰ� �������´�.
						if ((tmpYal - cnt) < 0 || (tmpYal + cnt) > 99) {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}
						//������ ȸ���� ���� +2, cnt + 1
						if (board[hang][tmpYal - cnt] == board[hang][tmpYal + cnt]) {
							Palindrome += 2;
							cnt++;					
						}
						// �ٸ��� �ִ밪�� �����ϰ� �������´�.
						else {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}
					}
				}
			}
		}
		//���θ� ���η� �ٲ��ְ� ���ϵ���..
		for (int yal = 0; yal < 100; yal++) {
			for (int hang = 0; hang < 99; hang++) {
				int tmpHang = hang;
				if (board[tmpHang][yal] == board[tmpHang + 1][yal]) {
					Palindrome = 2;
					cnt = 1;
					while (1) {
						if ((tmpHang - cnt) < 0 || (tmpHang + cnt + 1) > 99) {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}

						if (board[tmpHang - cnt][yal] == board[tmpHang + cnt + 1][yal]) {
							Palindrome += 2;
							cnt++;	
						}
						else {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome ;
							break;
						}
					}
				}
				else {
					Palindrome = 1;
					cnt = 1;
					while (1) {
						if ((tmpHang - cnt) < 0 || (tmpHang + cnt) > 99) {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}

						if (board[tmpHang - cnt][yal] == board[tmpHang + cnt][yal]) {
							Palindrome += 2;
							cnt++;				
						}
						else {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}
					}
				}
			}
		}
		printf("#%d %d\n", t, maxPalindrome);
	}

	return 0;
}