#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, L;
int board[100][100];
int result;
bool check[201];

int main() {
	scanf("%d %d", &N, &L);
	for (int hang = 0; hang < N; hang++) {
		for (int yal = 0; yal < N; yal++) {
			scanf("%d", &board[hang][yal]);
		}
	}
	//행의 첫번째부터 열의 첫번째 부터 보는 방식..
	for (int hang = 0; hang < N; hang++) {
		int temp = board[hang][0]; // 초기값 저장..
		int cnt = 1; // 같은 크기의 칸을 세기위해..
		int curve = 0; // 바뀌기 전의 경사가 몇이였는지 판단..
		for (int yal = 1; yal < N; yal++) {
			if (temp == board[hang][yal]) {// 경사의 크기가 같으면 cnt++
				cnt++;
				continue;
			}

			if (temp == board[hang][yal] - 1) {// 경사가 커질 때..		
				if (cnt < L) break; // 경사로의 길이가 L보다 작다면 break..
				if (curve == board[hang][yal]) { // 3 3 2 2 3 3 같은 곳을 보기 위해 ..

					if (cnt / 2 >= L) { // 경사로의 길이를 반으로 나눴을 때 L보다 크다면 가능..
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}

					else { // 경사로의 길이를 반으로 나눴을 때 L보다 작다면 불가능..
						cnt = 0;
						break;
					}
				}
				if (cnt >= L) { // 1 1 2 2 3 3 , 1 1 2 2 2 2 ,같은 경우만 판단..
					curve = temp;
					temp = board[hang][yal];
					cnt = 1;
					continue;
				}

			}

			if (temp == board[hang][yal] + 1) { // 경사가 작아질 때..
				if (curve != 0) { // 3 3 2 2 1 1 
					if (cnt < L && curve != board[hang][yal]) break;
					else {
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}
				}

				curve = temp;
				temp = board[hang][yal];
				cnt = 1;
				continue;
			}

			if (temp > board[hang][yal] + 1) { // 경사의 크기가 1보다 큰경우..
				cnt = 0;
				break;
			}
			if (temp < board[hang][yal] - 1) { // 경사의 크기가 1보다 큰경우..
				cnt = 0;
				break;
			}
		}
		if (cnt >= L) { // 열이 다 끝났을 때 경사로가 L보다 크면 결과값을 올려주고 hang은 더이상 안봐도 된다고 체크..
			result++;
			check[hang] = true;
		}
	}
	// 열의 첫번째부터 행의 첫번째를 보는 방법..
	for (int yal = 0; yal < N; yal++) {
		int temp = board[0][yal];
		int cnt = 1;
		int curve = 0;
		for (int hang = 1; hang < N; hang++) {
			if (temp == board[hang][yal]) {
				cnt++;
				continue;
			}
			if (temp == board[hang][yal] - 1) {// 보드가 커질 때..		
				if (cnt < L) break;
				if (curve == board[hang][yal]) {
					if (cnt / 2 >= L) {
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}
					else {
						cnt = 0;
						break;
					}
				}
				if (cnt >= L) {
					curve = temp;
					temp = board[hang][yal];
					cnt = 1;
					continue;
				}
			}
			if (temp == board[hang][yal] + 1) { // 보드가 작아질 때..
				if (curve != 0) {
					if (cnt < L && curve != board[hang][yal]) break;
					else {
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}
				}
				curve = temp;
				temp = board[hang][yal];
				cnt = 1;
				continue;
			}

			if (temp > board[hang][yal] + 1) {
				cnt = 0;
				break;
			}
			if (temp < board[hang][yal] - 1) {
				cnt = 0;
				break;
			}
		}
		if (cnt >= L) {
			result++;
			check[yal + 100] = true;
		}
	}


	//행의첫번째부터 열의 마지막부터 보는 방법..
	for (int hang = 0; hang < N; hang++) {
		if (check[hang]) continue;
		int temp = board[hang][N - 1];
		int cnt = 1;
		int curve = 0;
		for (int yal = N - 2; yal >= 0; yal--) {
			if (temp == board[hang][yal]) {
				cnt++;
				continue;
			}
			if (temp == board[hang][yal] - 1) {// 보드가 커질 때..		
				if (cnt < L) break;
				if (curve == board[hang][yal]) {

					if (cnt / 2 >= L) {
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}
					else {
						cnt = 0;
						break;
					}
				}
				if (cnt >= L) {
					curve = temp;
					temp = board[hang][yal];
					cnt = 1;
					continue;
				}
			}
			if (temp == board[hang][yal] + 1) { // 보드가 작아질 때..
				if (curve != 0) {
					if (cnt < L && curve != board[hang][yal]) break;
					else {
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}
				}
				curve = temp;
				temp = board[hang][yal];
				cnt = 1;
				continue;
			}
			if (temp > board[hang][yal] + 1) {
				cnt = 0;
				break;
			}
			if (temp < board[hang][yal] - 1) {
				cnt = 0;
				break;
			}
		}
		if (cnt >= L) {
			result++;
			check[hang] = true;
		}
	}

	//열의 첫번째부터 행의 마지막부터 보는방법 ..
	for (int yal = 0; yal < N; yal++) {
		if (check[100 + yal]) continue;
		int temp = board[N - 1][yal];
		int cnt = 1;
		int curve = 0;
		for (int hang = N - 2; hang >= 0; hang--) {
			if (temp == board[hang][yal]) {
				cnt++;
				continue;
			}
			if (temp == board[hang][yal] - 1) {// 보드가 커질 때..		
				if (cnt < L) break;
				if (curve == board[hang][yal]) {

					if (cnt / 2 >= L) {
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}
					else {
						cnt = 0;
						break;
					}
				}
				if (cnt >= L) {
					curve = temp;
					temp = board[hang][yal];
					cnt = 1;
					continue;
				}

			}
			if (temp == board[hang][yal] + 1) { // 보드가 작아질 때..
				if (curve != 0) {
					if (cnt < L && curve != board[hang][yal]) break;
					else {
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}
				}
				curve = temp;
				temp = board[hang][yal];
				cnt = 1;
				continue;
			}

			if (temp > board[hang][yal] + 1) {
				cnt = 0;
				break;
			}

			if (temp < board[hang][yal] - 1) {
				cnt = 0;
				break;
			}
		}
		if (cnt >= L) {
			result++;
			check[yal + 100] = true;
		}
	}

	printf("%d\n", result);
	return 0;
}