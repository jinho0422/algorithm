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
	printf("어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n");
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
			if (i == 0) printf("\"재귀함수가 뭔가요?\"");
			if (i == 1) printf("\"재귀함수는 자기 자신을 호출하는 함수라네\"");
			if (i == 2) printf("라고 답변하였지.");
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
				if (i == 0) printf("\"재귀함수가 뭔가요?\"");
				if (i == 1) printf("\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.");
				if (i == 2) printf("마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.");
				if (i == 3) printf("그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"");
				printf("\n");
			}
			DFS(depth + 1);
		}
	}
	if (flag) {
		for (int i = 0; i < depth * 4; i++) {
			printf("_");
		}
		
		printf("라고 답변하였지.\n");
		return;
	}

}