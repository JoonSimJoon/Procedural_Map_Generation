#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;
struct Node {
	int x, y;
};

int arr[110][110];
int x, y, cnt;
char file_buff[101 * 101];
FILE* fp;

void print_map();
void push_map();
void scan_map();
void bsp(Node st, Node en);

int main() {
	srand(time(NULL));
	Node a, b;
	a.x = 0;
	a.y = 0;
	b.x = 100;
	b.y = 100;
	bsp(a, b);
	print_map();
	push_map();
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

void bsp(Node st,Node en) {
//	printf("%d %d %d %d", st.x, st.y, en.x, en.y);
	for (int i = st.x; i < en.x; i++) {
		for (int j = st.y; j<en.y; j++) {
			if (i == st.x || i == en.x - 1 || j == st.y || j == en.y - 1) arr[i][j] = 1;
		}
	}
	Node mid;
	mid.x = (st.x + en.x) / 2;
	mid.y = (st.y + en.y) / 2;
	if (abs(en.x - st.x) * abs(en.y - st.y) < 400) {
		return;
	}
	else {
		if (rand() % 2 == 0) { //세로로 선 긋기
			if (en.x - st.x > 8) {
				mid.x -= 3;
				mid.x += rand() % 7;
			}
			for (int i = st.y; i < en.y; i++) {
				arr[mid.x][i] = 1;
			}
		}
		else {
			if (en.y - st.y > 8) {
				mid.y -= 3;
				mid.y += rand() % 7;
			}
			for (int i = st.x; i < en.x; i++) { //가로로 선 긋기
				arr[i][mid.y] = 1;
			}
		}
//		printf(" %d %d\n", mid.x, mid.y);
		Node nd1, nd2;
		nd1 = st;
		nd2 = { mid.x + 1,mid.y + 1 };
		bsp(nd1, nd2); //좌측상단
		nd1 = { mid.x,st.y };
		nd2 = { en.x,mid.y+1 };
		bsp(nd1, nd2); //좌측하단
		nd1 = { st.x,mid.y };
		nd2 = { mid.x+1,en.y};
		bsp(nd1, nd2); //우측상단
		nd1 = { mid.x,mid.y};
		nd2 = en;
		bsp(nd1, nd2); //우측 하단


	}
	return;
}