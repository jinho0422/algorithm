#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

int N;
int oper[13]; // ��ȣ�� �Ǵ��ϱ� ����..
bool check[13];
char str[25];
int tmp[13]; // ��ȣ�� �´� ��ȣ�� �ֱ� ����..
long long minResult; // �ּ� �����
long long maxResult; // �ִ� �����

queue<char> minQ;
queue<char> maxQ;

void DFS(int depth);

int main() {
	//�Է�
	minResult = 9876543210;
	scanf("%d ", &N);
	scanf("%[^\n]s", str);
	int num = 0;
	for (int s = 0; str[s] != '\0'; s++) {
		if (str[s] == '<') oper[num++] = 0; // '<' �̸� oper == 0 '>' �̸� oper == 1
		else if (str[s] == '>') oper[num++] = 1;
	}

	DFS(0);
	//���
	while (!maxQ.empty()) {
		printf("%c", maxQ.front());
		maxQ.pop();
	}
	printf("\n");
	while (!minQ.empty()) {
		printf("%c", minQ.front());
		minQ.pop();
	}
	printf("\n");
	return 0;
}
// ��ȣ�� �´� �������� �Ǵ�..
bool equel(int i) {
	if (oper[i] == 0) {
		if (tmp[i] < tmp[i + 1]) return true;
	}
	else if (oper[i] == 1) {
		if (tmp[i] > tmp[i + 1]) return true;
	}
	return false;
}

void DFS(int depth) {
	if (depth == N + 1) {
		bool resultFlag = false;
		for (int i = 0; i < depth - 1; i++) {
			str[i] = tmp[i] + '0';
			bool flag = equel(i);
			if (!flag) {
				resultFlag = true;
				break;
			}
		}
		// ���� ��ȣ�� ��ġ�Ѵٸ�
		if (!resultFlag) {
			str[depth - 1] = tmp[depth - 1] + '0';
			long long numbers = 0; // numbers�� ���ڸ� �ְ� min���� max���� ã�´�
			for (int s = 0; s < depth; s++) numbers += (tmp[s] * pow(10, depth - s - 1));
			
			if (minResult > numbers) {
				minResult = numbers;
				while(!minQ.empty()) minQ.pop();
				for (int s = 0; s < depth; s++) minQ.push(str[s]);		
			}
			if (maxResult < numbers) {
				maxResult = numbers;
				while (!maxQ.empty()) maxQ.pop();
				for (int s = 0; s < depth; s++) maxQ.push(str[s]);		
			}
		}
		return;
	}
	//������ ���� ��������
	for (int s = 0; s < 10; s++) {
		if (!check[s]) {
			check[s] = true;
			tmp[depth] = s;
			DFS(depth + 1);
			tmp[depth] = 0;
			check[s] = false;
		}
	}
}