#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>

using namespace std;

int N;
vector<int> Vec;

int main() {
	//입력
	scanf("%d", &N);
	// 666부터 int 최대치까지 돌리면서 만약 값을 저장한 Vec의 값이 10000(N의 최대가 10000이므로)이면 break;
	for (int s = 666; s <= 2147000000; s++) {
		if (Vec.size() == 10001) break;
		int checkCnt = 0; // 연속된 6의 숫자를 세기위해
		int share = s; // 몫
		bool flag = false; // 연속된 6이 3개이상인지 판단하기위해
		while (1) {
			int remainder = share % 10; // 나머지
			share /= 10; 
			
			if (remainder == 6) { // 나머지가 6이면 checkCnt++
				checkCnt++;
				if (checkCnt == 3) flag = true; // 연속된 6이 3번이 나왔으므로 결과값으로 성립되므로flag ==ture;
				
			}
			if (share == 0) break;

			if (remainder != 6) {
				checkCnt = 0;
			}
			
		}
		// 결과값이 성립되면 vector에 넣어준다..
		if (flag) Vec.push_back(s);
	}
	//출력
	printf("%d\n", Vec[N - 1]);
	return 0;
}
