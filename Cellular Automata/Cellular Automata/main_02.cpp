#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;
struct Node {
	int x, y;
};

int arr[110][110];
int x, y, cnt, componentcnt;
char file_buff[101 * 101];
FILE* fp;
queue<Node> q;
void print_map();
void Cellular_Automata();
void push_map();
void scan_map();
void ccc();
void bfs(int x, int y);
void print_map_num();

int main() {
	int hcase, N;
	printf("생성 :1 \n사용: 2 ");
	scanf("%d", &hcase);
	if (hcase == 1) {
		srand(time(NULL));
		for (int i = 0; i < 100 * 100 / 100 * 50; i++) { //100*300맵의 40퍼센트
			while (1) {
				x = rand() % 99 + 1;
				y = rand() % 99 + 1;
				if (arr[x][y] == 0) {
					arr[x][y] = 1;
					break;
				}
			}
		}
		
	}
	else if (hcase == 2) {
		scan_map();
		print_map();
	}
	printf("세포 자동자 횟수 입력: ");
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		print_map();
		push_map();
		Cellular_Automata();
	}
	ccc();
	print_map_num();
	return 0;
}

void print_map() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (i == 0 || i == 99 || j == 0 || j == 99) arr[i][j] = 1;
			if (arr[i][j] == 0) printf("□");
			else if (arr[i][j] == 1) printf("■");
		}
		printf("\n");
	}
	printf("\n");
}

void print_map_num() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			printf("%2d", arr[i][j]);
		}
		printf("\n");
	}
	printf("%d\n",componentcnt);
}


void Cellular_Automata() {
	int map_new[110][110];
	int dx[10] = { 1,1,1,0,0,0,-1,-1,-1 };
	int dy[10] = { 1,0,-1,1,0,-1,1,0,-1 };
	int z_cnt = 0;
	for (int i = 1; i < 99; i++) {
		for (int j = 1; j < 99; j++) {
			z_cnt = 0;
			for (int xcnt = 0; xcnt < 9; xcnt++) {
				if (arr[i + dx[xcnt]][j + dy[xcnt]] == 0) z_cnt++;
			}
			if (z_cnt > 4) map_new[i][j] = 0;
			else map_new[i][j] = 1;
		}
	}
	memcpy(arr, map_new, sizeof(map_new));
}

void push_map() {
	fp = fopen("test.txt", "w");
	for (int i = 0; i < 100; i++) {
		memset(file_buff, 0, sizeof(file_buff));
		for (int j = 0; j < 100; j++) {
			file_buff[strlen(file_buff)] = arr[i][j] + 48;
		}
		file_buff[strlen(file_buff)] = '\n';
		fputs(file_buff, fp);
	}
	fclose(fp);
}

void scan_map() {
	int x = 0;
	fp = fopen("test.txt", "r");
	memset(file_buff, 0, sizeof(file_buff));
	while (fgets(file_buff, sizeof(file_buff), fp) != NULL) {
		printf("%s", file_buff - 48);
		for (int j = 0; j < 100; j++) {
			arr[x][j] = file_buff[j] - 48;
		}
		x++;
		memset(file_buff, 0, sizeof(file_buff));
	}
	fclose(fp);

}

void ccc() {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (arr[i][j] == 1) printf("■");
			else printf("□");
			if (arr[i][j] == 0) bfs(i, j) ;

		}
		printf("\n");
	}
}

void bfs(int x, int y) {
	Node now,next;
	int dx[5] = { 1,-1,0,0 };
	int dy[5] = { 0,0,1,-1 };
	now.x = x;
	now.y = y;
	q.push(now);
	//printf("%d %d", x, y);
	while (!q.empty()) {
		now = q.front();
		q.pop();
		arr[now.x][now.y] = componentcnt + 2;
		for (int i = 0; i < 4; i++) {
			next.x = now.x + dx[i];
			next.y = now.y + dy[i];
			if (next.x > 0 && next.x < 99 && next.y >= 0 && next.y < 99 && arr[next.x][next.y] == 0) {
				q.push(next);
				arr[next.x][next.y] = componentcnt + 2;
			}
		}
	}
	componentcnt++;
}