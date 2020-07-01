#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <math.h>

using namespace std;

int T;
bool check[53];
bool flag;

void DFS(int depth);

int main() {
	scanf("%d", &T);
	printf("��� �� ��ǻ�Ͱ��а� �л��� ������ �������� ã�ư� ������.\n");
	DFS(0);

	return 0;
}

void DFS(int depth) {


	if (depth == T) {
		flag = true;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < depth * 4; j++) {
				printf("_");
			}
			if (i == 0) printf("\"����Լ��� ������?\"");
			if (i == 1) printf("\"����Լ��� �ڱ� �ڽ��� ȣ���ϴ� �Լ����\"");
			if (i == 2) printf("��� �亯�Ͽ���.");
			printf("\n");
		}
		return;
	}
	for (int s = 0; s < T; s++) {
		if (!check[s]) {
			check[s] = true;
			int operatorNumber = depth * 4;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < operatorNumber; j++) {
					printf("_");
				}
				if (i == 0) printf("\"����Լ��� ������?\"");
				if (i == 1) printf("\"�� ����. �������� �� �� ����⿡ �̼��� ��� ������ ����� ������ �־���.");
				if (i == 2) printf("���� ������� ��� �� ���ο��� ������ ������ �߰�, ��� �����Ӱ� ����� �־���.");
				if (i == 3) printf("���� ���� ��κ� �ǾҴٰ� �ϳ�. �׷��� ��� ��, �� ���ο��� �� ���� ã�ƿͼ� ������.\"");
				printf("\n");
			}
			DFS(depth + 1);
		}
	}
	if (flag) {
		for (int i = 0; i < depth * 4; i++) {
			printf("_");
		}
		
		printf("��� �亯�Ͽ���.\n");
		return;
	}

}