
if __name__ == '__main__':
    N, M = map(int, input().split())
    board = []
    queue = []
    dirY = [-1, 0, 0, 1]
    dirX = [0, -1, 1, 0]

    for i in range(N):
        board.append(list(input()))

    queue = [[0, 0]]
    board[0][0] = 1
    while queue:
        a, b = queue[0][0], queue[0][1]
        del queue[0]
        for dir in range(4):
            newY = a + dirY[dir]
            newX = b + dirX[dir]

            if 0 <= newY < N and 0 <= newX < M and board[newY][newX] =="1":
                queue.append([newY, newX])
                board[newY][newX] = board[a][b] + 1
    print(board[N -1][M -1])
