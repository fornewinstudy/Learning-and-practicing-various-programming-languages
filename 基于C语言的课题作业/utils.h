#ifndef UTILS_H
#define UTILS_H

// 表示运动员的参赛信息
typedef struct Player Player;
struct Player {
	char name[30];
	char nation[20];
	int age;
	int weight;
	int height;
	char race[20];
	int engagementAge;
	double luckyFactor;
	char medal[15];
	double score;
};

// 计算运动员评分
double getScore(Player* player);

// 从文件中读取数据
void readDataFromFile(const char* filename, Player*** players, int* nPlayers,
	char*** races, int* nRaces);

// 计算各赛事的运动员评分榜
void calRatingList(Player** players, int nPlayers, char** races, int nRaces);

// 统计各国家金牌榜
void calGoldMedalList(Player** players, int nPlayers);

// 统计各国家奖牌榜
void calMedalList(Player** players, int nPlayers);

#endif // UTILS_H