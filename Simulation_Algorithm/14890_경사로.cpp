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
	//���� ù��°���� ���� ù��° ���� ���� ���..
	for (int hang = 0; hang < N; hang++) {
		int temp = board[hang][0]; // �ʱⰪ ����..
		int cnt = 1; // ���� ũ���� ĭ�� ��������..
		int curve = 0; // �ٲ�� ���� ��簡 ���̿����� �Ǵ�..
		for (int yal = 1; yal < N; yal++) {
			if (temp == board[hang][yal]) {// ����� ũ�Ⱑ ������ cnt++
				cnt++;
				continue;
			}

			if (temp == board[hang][yal] - 1) {// ��簡 Ŀ�� ��..		
				if (cnt < L) break; // ������ ���̰� L���� �۴ٸ� break..
				if (curve == board[hang][yal]) { // 3 3 2 2 3 3 ���� ���� ���� ���� ..

					if (cnt / 2 >= L) { // ������ ���̸� ������ ������ �� L���� ũ�ٸ� ����..
						curve = temp;
						temp = board[hang][yal];
						cnt = 1;
						continue;
					}

					else { // ������ ���̸� ������ ������ �� L���� �۴ٸ� �Ұ���..
						cnt = 0;
						break;
					}
				}
				if (cnt >= L) { // 1 1 2 2 3 3 , 1 1 2 2 2 2 ,���� ��츸 �Ǵ�..
					curve = temp;
					temp = board[hang][yal];
					cnt = 1;
					continue;
				}

			}

			if (temp == board[hang][yal] + 1) { // ��簡 �۾��� ��..
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

			if (temp > board[hang][yal] + 1) { // ����� ũ�Ⱑ 1���� ū���..
				cnt = 0;
				break;
			}
			if (temp < board[hang][yal] - 1) { // ����� ũ�Ⱑ 1���� ū���..
				cnt = 0;
				break;
			}
		}
		if (cnt >= L) { // ���� �� ������ �� ���ΰ� L���� ũ�� ������� �÷��ְ� hang�� ���̻� �Ⱥ��� �ȴٰ� üũ..
			result++;
			check[hang] = true;
		}
	}
	// ���� ù��°���� ���� ù��°�� ���� ���..
	for (int yal = 0; yal < N; yal++) {
		int temp = board[0][yal];
		int cnt = 1;
		int curve = 0;
		for (int hang = 1; hang < N; hang++) {
			if (temp == board[hang][yal]) {
				cnt++;
				continue;
			}
			if (temp == board[hang][yal] - 1) {// ���尡 Ŀ�� ��..		
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
			if (temp == board[hang][yal] + 1) { // ���尡 �۾��� ��..
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


	//����ù��°���� ���� ���������� ���� ���..
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
			if (temp == board[hang][yal] - 1) {// ���尡 Ŀ�� ��..		
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
			if (temp == board[hang][yal] + 1) { // ���尡 �۾��� ��..
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

	//���� ù��°���� ���� ���������� ���¹�� ..
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
			if (temp == board[hang][yal] - 1) {// ���尡 Ŀ�� ��..		
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
			if (temp == board[hang][yal] + 1) { // ���尡 �۾��� ��..
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