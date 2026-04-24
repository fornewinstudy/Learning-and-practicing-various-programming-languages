#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

// 计算运动员评分
double getScore(Player* player) {
	double score = 0.0;
	score = 2 * player->height + 8 * player->engagementAge -
		(player->age - 32.5) * (player->age - 32.5) -
		(player->weight - 80) * (player->weight - 80) + player->luckyFactor;
	return score;
}

// 从文件中读取数据
void readDataFromFile(const char* filename, Player*** players, int* nPlayers,
	char*** races, int* nRaces) {
	*nPlayers = 0;
	*nRaces = 0;
	char buf[256];
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		perror("ERROR");
		exit(1);
	}
	fgets(buf, 255, fp);
	// 读取每一行并构建结构体变量
	while (fgets(buf, 255, fp)) {
		(*nPlayers)++;
		*players = (Player**)realloc(*players, (*nPlayers) * sizeof(Player*));
		(*players)[(*nPlayers) - 1] = calloc(1, sizeof(Player));
		Player* player = (*players)[(*nPlayers) - 1];
		sscanf(buf, "%[^,],%[^,],%d,%d,%d,%[^,],%d,%lf,", player->name, player->nation,
			&player->age, &player->weight, &player->height, player->race, &player->engagementAge,
			&player->luckyFactor);
		player->score = getScore(player);
		// 记录比赛项目
		bool exists = false;
		for (int i = 0; i < *nRaces; i++) {
			if (strcmp((*races)[i], player->race) == 0) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			(*nRaces)++;
			*races = (char**)realloc(*races, (*nRaces) * sizeof(char*));
			(*races)[(*nRaces) - 1] = (char*)calloc(strlen(player->race) + 1, sizeof(char));
			strcpy((*races)[(*nRaces) - 1], player->race);
		}
	}
	fclose(fp);
}

// 计算各赛事的运动员评分榜
void calRatingList(Player** players, int nPlayers, char** races, int nRaces) {
	for (int k = 0; k < nRaces; k++) {
		// 对赛事进行排序
		for (int i = 0; i < nPlayers; i++) {
			if (strcmp(players[i]->race, races[k]) != 0) continue;
			double maxScore = players[i]->score;
			// 找到最大的分数对应的运动员
			int idx = i;
			for (int j = i; j < nPlayers; j++) {
				if (strcmp(players[j]->race, races[k]) != 0) continue;
				if (maxScore < players[j]->score) {
					maxScore = players[j]->score;
					idx = j;
				}
			}
			// 交换
			if (idx != i) {
				Player* player = players[i];
				players[i] = players[idx];
				players[idx] = player;
			}
		}
		// 打印结果
		printf("===============%s的评分榜=============\n", races[k]);
		int lastIdx = -1;
		for (int i = 0, w = 0; i < nPlayers; i++) {
			if (strcmp(players[i]->race, races[k]) != 0) continue;
			strcpy(players[i]->medal, "");
			// 设置运动员的奖牌
			if (lastIdx >= 0 && players[i]->score != players[lastIdx]->score) {
				w++;
			}
			if (w == 0) {
				strcpy(players[i]->medal, "金牌");
			}
			else if (w == 1) {
				strcpy(players[i]->medal, "银牌");
			}
			else if (w == 2) {
				strcpy(players[i]->medal, "铜牌");
			}
			lastIdx = i;
			printf("%d: %-25s%-10s%-8.2lf%s\n", w+1, players[i]->name, players[i]->nation,
				players[i]->score, players[i]->medal);
		}
		printf("==========================================\n\n");
	}
}

// 统计各国家金牌榜
void calGoldMedalList(Player** players, int nPlayers) {
	char** nations = NULL;
	int nNations = 0;
	for (int i = 0; i < nPlayers; i++) {
		// 找到所有国家
		bool exists = false;
		for (int k = 0; k < nNations; k++) {
			if (strcmp(nations[k], players[i]->nation) == 0) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			nNations++;
			nations = (char**)realloc(nations, nNations * sizeof(char*));
			nations[nNations - 1] = (char*)calloc(strlen(players[i]->nation) + 1, sizeof(char));
			strcpy(nations[nNations - 1], players[i]->nation);
		}
	}
	// 统计各国家金牌榜
	int* cnt = (int*)calloc(nNations, sizeof(int));
	for (int k = 0; k < nNations; k++) {
		for (int i = 0; i < nPlayers; i++) {
			if (strcmp(players[i]->nation, nations[k]) != 0) continue;
			if (strcmp(players[i]->medal, "金牌") == 0) {
				cnt[k]++;
			}
		}
	}
	// 打印结果
	printf("==================金牌榜==================\n");
	for (int i = 0; i < nNations; i++) {
		int maxValue = cnt[i];
		int idx = i;
		for (int j = i; j < nNations; j++) {
			if (maxValue < cnt[j]) {
				maxValue = cnt[j];
				idx = j;
			}
		}
		// 交换
		if (idx != i) {
			int tmp = cnt[i];
			cnt[i] = cnt[idx];
			cnt[idx] = tmp;
			char buf[255];
			strcpy(buf, nations[i]);
			strcpy(nations[i], nations[idx]);
			strcpy(nations[idx], buf);
		}
		printf("%-10s%d\n", nations[i], cnt[i]);
	}
	printf("==========================================\n\n");
	// 释放内存
	free(cnt);
	for (int i = 0; i < nNations; i++) {
		free(nations[i]);
	}
	free(nations);
}

// 统计各国家奖牌榜
void calMedalList(Player** players, int nPlayers) {
	char** nations = NULL;
	int nNations = 0;
	for (int i = 0; i < nPlayers; i++) {
		// 找到所有国家
		bool exists = false;
		for (int k = 0; k < nNations; k++) {
			if (strcmp(nations[k], players[i]->nation) == 0) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			nNations++;
			nations = (char**)realloc(nations, nNations * sizeof(char*));
			nations[nNations - 1] = (char*)calloc(strlen(players[i]->nation) + 1, sizeof(char));
			strcpy(nations[nNations - 1], players[i]->nation);
		}
	}
	// 统计各国家金牌榜
	int* cnt = (int*)calloc(nNations, sizeof(int));
	for (int k = 0; k < nNations; k++) {
		for (int i = 0; i < nPlayers; i++) {
			if (strcmp(players[i]->nation, nations[k]) != 0) continue;
			if (strlen(players[i]->medal) > 0) {
				cnt[k]++;
			}
		}
	}
	// 打印结果
	printf("==================奖牌榜==================\n");
	for (int i = 0; i < nNations; i++) {
		int maxValue = cnt[i];
		int idx = i;
		for (int j = i; j < nNations; j++) {
			if (maxValue < cnt[j]) {
				maxValue = cnt[j];
				idx = j;
			}
		}
		// 交换
		if (idx != i) {
			int tmp = cnt[i];
			cnt[i] = cnt[idx];
			cnt[idx] = tmp;
			char buf[255];
			strcpy(buf, nations[i]);
			strcpy(nations[i], nations[idx]);
			strcpy(nations[idx], buf);
		}
		printf("%-10s%d\n", nations[i], cnt[i]);
	}
	printf("==========================================\n\n");
	// 释放内存
	free(cnt);
	for (int i = 0; i < nNations; i++) {
		free(nations[i]);
	}
	free(nations);
}
