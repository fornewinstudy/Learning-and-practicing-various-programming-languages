#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

int main() {
	Player** players = NULL;
	char** races = NULL;
	int nPlayers = 0;
	int nRaces = 0;
	// 读取数据
	readDataFromFile("data.txt", &players, &nPlayers, &races, &nRaces);

	// 计算各赛事的运动员评分榜
	calRatingList(players, nPlayers, races, nRaces);
	// 统计各国家金牌榜
	calGoldMedalList(players, nPlayers);
	// 统计各国家奖牌榜
	calMedalList(players, nPlayers);

	// 释放内存
	for (int i = 0; i < nPlayers; i++) {
		free(players[i]);
	}
	for (int i = 0; i < nRaces; i++) {
		free(races[i]);
	}
	free(races);
	free(players);
	return 0;
}
