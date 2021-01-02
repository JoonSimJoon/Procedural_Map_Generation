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
	int arr[100][100];
	int x, y, cnt;

	void print_map();
	void Cellular_Automata();

	int main() {
		srand(time(NULL));
		for (int i = 0; i < 100 * 100 / 100 * 50; i++) { //100*300¸ÊÀÇ 40ÆÛ¼¾Æ®
			while (1) {
				x = rand() % 99+1;
				y = rand() % 99+1;
				if (arr[x][y] == 0) {
					arr[x][y] = 1;
					break;
				}
			}
		}
		print_map();
		for (int i = 0; i < 10;i++) {
			Cellular_Automata();
			print_map();

		}
		return 0;
	}

	void print_map() {
		for (int i = 0; i < 100; i++) {
			for (int j = 0; j < 100; j++) {
				if (i == 0 || i == 99 || j == 0 || j == 99) arr[i][j] = 1;
				if (arr[i][j] == 0) printf("¡à");
				else if (arr[i][j] == 1) printf("¡á");
			}
			printf("\n");
		}
		printf("\n");
	}
	void Cellular_Automata() {
		int map_new[100][100];
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
