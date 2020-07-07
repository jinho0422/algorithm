#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int result;

vector<int> bundle;
vector<int> single;

int main() {
	//입력값 6개 묶음값은 bundle, 1개 낱개값은 single Vector에 넣어준다..
	scanf("%d %d", &N, &M);
	for (int a, b, s = 0; s < M; s++) {
		scanf("%d %d", &a, &b);
		bundle.push_back(a);
		single.push_back(b);
	}
	//각각을 sort해준다(오름차순)
	sort(bundle.begin(), bundle.end());
	sort(single.begin(), single.end());

	// 만약 가장 작은 묶음(6개)가 가장작은 낱개(1개) 의 6배보다 작으면 N을 6개로 나눈 몫과 나머지와 낱개 값을 곱했을 때 묶음값보다 크거나 작음을 판단해서 결과값 반영
	if (bundle[0] <= single[0] * 6) {
		int share = N / 6;
		int remainder = N % 6;
		if (bundle[0] < remainder * single[0]) {
			result = (share + 1) * bundle[0];
		}
		else {
			result = share * bundle[0] + remainder * single[0];
		}
	}
	else result = N * single[0];
	printf("%d\n", result);
}