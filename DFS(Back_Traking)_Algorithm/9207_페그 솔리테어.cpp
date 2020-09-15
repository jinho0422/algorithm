#define _CRT_SECURE_NO_WARNINGS
#define INF 2147000000
#define P pair<char,bool>
#define N 5
#define M 9

#include <cstdio>
#include <cstring>
#include <queue>

int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

using namespace std;

pair<int, int> res;
char map[N][M + 1];


void dfs(int move)
{
    bool flag = false;
    int cnt = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j] != 'o')
                continue;

            cnt++;

            for (int d = 0; d < 4; d++)
            {
                int x = i + dx[d], y = j + dy[d];
                if (x < 0 || x >= N || y < 0 || y >= M || map[x][y] != 'o')
                    continue;

                int xx = x + dx[d], yy = y + dy[d];
                if (xx < 0 || xx >= N || yy < 0 || yy >= M || map[xx][yy] != '.')
                    continue;

                map[i][j] = map[x][y] = '.';
                map[xx][yy] = 'o';
                dfs(move + 1);
                map[i][j] = map[x][y] = 'o';
                map[xx][yy] = '.';

            }
        }

    }

    if (!flag)
    {
        if (res.first > cnt)
            res = { cnt,move };
        return;
    }
}


int main()
{
    int Test;
    scanf("%d", &Test);

    for (int T = 1; T <= Test; T++)
    {
        res = { 0,0 };
        for (int i = 0; i < N; i++)
        {
            scanf("%s", &map[i]);
            for (int j = 0; j < M; j++)
                if (map[i][j] == 'o')
                    res.first++;
        }

        dfs(0);

        printf("%d %d\n", res.first, res.second);
    }

}