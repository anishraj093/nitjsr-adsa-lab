
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define SIZE (N * N)
#define MAX_QUEUE 1000000
#define MAX_VISITED 1000000

typedef struct
{
    int board[N][N];
    int blank_x, blank_y;
    int g;
    int h;
    int f;
} Node;

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

Node pq[MAX_QUEUE];
int pq_size = 0;

unsigned int visited_hashes[MAX_VISITED];
int visited_count = 0;

void swap_nodes(Node *a, Node *b)
{
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(Node node)
{
    int i = pq_size++;
    pq[i] = node;
    while (i > 0 && pq[(i - 1) / 2].f > pq[i].f)
    {
        swap_nodes(&pq[i], &pq[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

Node pop()
{
    Node root = pq[0];
    pq[0] = pq[--pq_size];
    int i = 0;
    while (1)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < pq_size && pq[left].f < pq[smallest].f)
            smallest = left;
        if (right < pq_size && pq[right].f < pq[smallest].f)
            smallest = right;
        if (smallest == i)
            break;
        swap_nodes(&pq[i], &pq[smallest]);
        i = smallest;
    }
    return root;
}

int manhattan(int board[N][N])
{
    int dist = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int val = board[i][j];
            if (val == 0)
                continue;
            val--;
            dist += abs(i - val / N) + abs(j - val % N);
        }
    }
    return dist;
}

int is_goal(int board[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j] != goal[i][j])
                return 0;
    return 1;
}

unsigned int hash_board(int board[N][N])
{
    unsigned int h = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            h = h * 31 + board[i][j];
    return h;
}

int visited(int board[N][N])
{
    unsigned int h = hash_board(board);
    for (int i = 0; i < visited_count; i++)
    {
        if (visited_hashes[i] == h)
            return 1;
    }
    if (visited_count < MAX_VISITED)
        visited_hashes[visited_count++] = h;
    return 0;
}

void print_board(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void solve(int start_board[N][N])
{
    Node start;
    memcpy(start.board, start_board, sizeof(int) * SIZE);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (start.board[i][j] == 0)
            {
                start.blank_x = i;
                start.blank_y = j;
            }
    start.g = 0;
    start.h = manhattan(start.board);
    start.f = start.g + start.h;

    push(start);

    while (pq_size > 0)
    {
        Node curr = pop();

        if (is_goal(curr.board))
        {
            printf("Solution found! Cost: %d\n", curr.g);
            print_board(curr.board);
            return;
        }

        if (visited(curr.board))
            continue;

        int x = curr.blank_x;
        int y = curr.blank_y;

        for (int d = 0; d < 4; d++)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (nx >= 0 && nx < N && ny >= 0 && ny < N)
            {
                Node next = curr;
                next.board[x][y] = next.board[nx][ny];
                next.board[nx][ny] = 0;
                next.blank_x = nx;
                next.blank_y = ny;
                next.g = curr.g + 1;
                next.h = manhattan(next.board);
                next.f = next.g + next.h;

                if (!visited(next.board))
                {
                    push(next);
                }
            }
        }
    }

    printf("No solution found.\n");
}

int main()
{
    int start_board[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 15, 14, 0}};

    printf("Starting board:\n");
    print_board(start_board);

    solve(start_board);

    return 0;
}
