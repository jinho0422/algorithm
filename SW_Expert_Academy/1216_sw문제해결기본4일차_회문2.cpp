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
		// 최대 회문문자길이를 뽑기위해..
		maxPalindrome = 0;
		scanf("%d", &T);
		//입력
		for (int hang = 0; hang < 100; hang++) {
			scanf("%s", str);
			for (int yal = 0; yal < 100; yal++) {
				board[hang][yal] = str[yal];
			}
		}
		// 가로에서 회문의 최대 길이를 찾기위해.. yal을 98까지 한 이유는 다음번과 비교해서 들어가므로.. 99번째는 비교할 값이 없다.
		for (int hang = 0; hang < 100; hang++) {
			for (int yal = 0; yal < 99; yal++) {
				int tmpYal = yal;
				// 현재의 board값과 다음 board값이 같으면 짝수개의 회문길이가 생성되므로.. 회문길이 2로 시작해서 cnt를 증가하며 처음 board의 yal값에서 뒤로 cnt+, 앞으로 cnt + 1을 해주며 비교
				if (board[hang][tmpYal] == board[hang][tmpYal + 1]) {
					Palindrome = 2;
					cnt = 1;
					while (1) {
						//범위를 넘어가면 최대값을 갱신하고 빠져나온다.
						if ((tmpYal - cnt) < 0 || (tmpYal + cnt + 1) > 99) {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}
						//같으면 회문의 수 +2 cnt++ 
						if (board[hang][tmpYal - cnt] == board[hang][tmpYal + cnt + 1]) {
							Palindrome += 2;
							cnt++;						
						}
						//다른면 회문의 최대값을 갱신하고 빠져나온다.
						else {
							if (maxPalindrome < Palindrome ) maxPalindrome = Palindrome;
							break;
						}
					}
				}
				// 홀수개의 회문이 나올때..(board[hang][yal] != board[hang][yal+1)
				else {
					Palindrome = 1;
					cnt = 1;
					while (1) {
						// 범위를 넘어가면 최대값을 갱신하고 빠져나온다.
						if ((tmpYal - cnt) < 0 || (tmpYal + cnt) > 99) {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}
						//같으면 회문의 길이 +2, cnt + 1
						if (board[hang][tmpYal - cnt] == board[hang][tmpYal + cnt]) {
							Palindrome += 2;
							cnt++;					
						}
						// 다르면 최대값을 갱신하고 빠져나온다.
						else {
							if (maxPalindrome < Palindrome) maxPalindrome = Palindrome;
							break;
						}
					}
				}
			}
		}
		//가로를 세로로 바꿔주고 이하동일..
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