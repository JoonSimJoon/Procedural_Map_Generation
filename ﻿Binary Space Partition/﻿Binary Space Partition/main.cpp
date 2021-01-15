#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <string.h>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define Map_Size 100
struct Node {
	int x, y;
};

int arr[110][110];
int x, y, cnt;
char file_buff[101 * 101];
FILE* fp;
int dx[10] = { 0,0,0,1,1,1,-1,-1,-1 };
int dy[10] = { 1,0,-1,1,0,-1,1,0,-1 };
vector< pair<Node,Node> > mid_check;

void print_map();
void push_map();
void scan_map();
void bsp(Node st, Node en,int dis);
void connect();
void check_connected();
void opti();


int main() {
	srand(time(NULL));
	Node a, b;
	a = { 0,0 };
	b = { Map_Size,Map_Size };
	bsp(a, b, 0);
	print_map();
	push_map();
	printf("\n");
	connect();
	opti();
	print_map();
	return 0;
}

void print_map() {
	for (int i = 0; i < Map_Size; i++) {
		for (int j = 0; j < Map_Size; j++) {
			if (i == 0 || i == 99 || j == 0 || j == 99) arr[i][j] = 1;
			if (arr[i][j] == 0) printf("□");
			else if (arr[i][j] == 1) printf("■");
			else if (arr[i][j] == 2) printf("◆");
			else printf("%2d", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void push_map() {
	fp = fopen("test.txt", "w");
	for (int i = 0; i < Map_Size; i++) {
		memset(file_buff, 0, sizeof(file_buff));
		for (int j = 0; j < Map_Size; j++) {
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
		for (int j = 0; j < Map_Size; j++) {
			arr[x][j] = file_buff[j] - 48;
		}
		x++;
		memset(file_buff, 0, sizeof(file_buff));
	}
	fclose(fp);

}

void bsp(Node st,Node en,int dis) {
	int flag;
//	printf("%d %d %d %d", st.x, st.y, en.x, en.y);
	for (int i = st.x; i < en.x; i++) {
		for (int j = st.y; j<en.y; j++) {
			if (i == st.x || i == en.x - 1 || j == st.y || j == en.y - 1) arr[i][j] = 1;
		}
	}
	Node mid;
	Node nd1, nd2;
	mid.x = (st.x + en.x) / 2;
	mid.y = (st.y + en.y) / 2;
	if (abs(en.x - st.x) * abs(en.y - st.y) < 400 || (en.y - st.y < 10 && en.x - st.x < 10)) {
		for (int i = st.x + 1; i < en.x - 1; i++) {
			for (int j = st.y + 1; j < en.y - 1; j++) {
				if (i == st.x + 1 || i == en.x - 2 || j == st.y + 1 || j == en.y - 2) arr[i][j] = 1;
			}
		}
		mid_check.push_back({ st,en });
		return;
	}
	else {
		flag = rand() % 2;
		if (dis< -1 || en.y-st.y<5 || flag == 0) { //세로로 선 긋기
			if(en.x-st.x>5) mid.x = mid.x + (rand() % 3 - 1) * (en.x - st.x)/10;
			nd1 = st;
			nd2 = { mid.x + 1,en.y };
			bsp(nd1, nd2, dis + 1);
			nd1 = { mid.x,st.y };
			nd2 = en;
			bsp(nd1, nd2, dis + 1);
			
		}
		else if (dis>1 || en.x - st.x < 5 || flag==1){
			if (en.y - st.y > 5)mid.y = mid.y + (rand() % 3 - 1) *(en.y - st.y) /10;
			nd1 = st;
			nd2 = { en.x,mid.y + 1 };
			bsp(nd1, nd2, dis -1);
			nd1 = { st.x,mid.y};
			nd2 = en;
			bsp(nd1, nd2, dis -1);
			
		}
	}
	return;
}

void connect() {
	Node st,en,mid;
	int vl = mid_check.size();
	int dis;
	for (int i = 0; i < vl; i++) {
		dis = rand() % 4;
		st = mid_check[i].first;
		en = mid_check[i].second;
		en.x--;
		en.y--;
		mid = { (st.x + en.x) / 2,(st.y + en.y) / 2 };
		if (dis != 0) {
			for(int j=0;j<9;j++) arr[st.x+dx[j]][mid.y+dy[j]] = 0;
		}
		if (dis != 1) {
			for(int j=0;j<9;j++) arr[mid.x+dx[j]][en.y+dy[j]] = 0;
		}
		if (dis != 2) {
			for(int j=0;j<9;j++) arr[en.x+dx[j]][mid.y+dy[j]] = 0;
		}
		if (dis != 3) {
			for(int j=0;j<9;j++) arr[mid.x+dx[j]][st.y+dy[j]] = 0;
		}
		/*
		arr[st.x][st.y] = 2;
		arr[st.x][en.y] = 2;
		arr[en.x][st.y] = 2;
		arr[en.x][en.y] = 2;
		arr[st.x][mid.y] = (mid_check[i].first.x+ mid_check[i].first.y)%Map_Size;
		arr[mid.x][en.y] = (mid_check[i].first.x+ mid_check[i].first.y)%Map_Size;
		arr[en.x][mid.y] = (mid_check[i].first.x+ mid_check[i].first.y)%Map_Size;
		arr[mid.x][st.y] = (mid_check[i].first.x+ mid_check[i].first.y)%Map_Size;
		arr[mid.x][mid.y] = dis + 10;*/
	}
}

void check_connected() {
	queue<Node> q;
	Node now,next;
	q.push({ 1,1 });
	int dx2[5] = { 0,0,1,-1 };
	int dy2[5] = { 1,-1,0,0 };
	while (!q.empty()) {
		now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			next = { now.x + dx2[i],now.y + dy2[i] };
			if (arr[next.x][next.y] == 0) {
				arr[next.x][next.y] = 2;
				q.push(next);
			}
		}
	}
}

void opti() {
	for (int i = 0; i < Map_Size; i++) {
		for (int j = 0; j < Map_Size; j++) {
			if (i == 0 || i == 99 || j == 0 || j == 99 || i == 1 || i == 98 || j == 1 || j == 98) arr[i][j] = 1;
		}
	}
}