#ifndef __MAZE_H
#define __MAZE_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "stdint.h"

#define MAX_STEP 255
#define MAX_SIZE 16
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef struct {								// 迷路定義用構造体
	uint8_t maze_size_x;							// 迷路サイズ( X )
	uint8_t maze_size_y;							// 迷路サイズ( Y )
	uint8_t maze_goal_x;							// ゴールマス( X )
	uint8_t maze_goal_y;							// ゴールマス( Y )
}mazeDef_t;

typedef struct {								// 迷路情報
	uint8_t start_x;								// スタートマス
	uint8_t start_y;								// スタートマス
	uint8_t step[MAX_SIZE][MAX_SIZE];							// 歩数マップ
	uint8_t goal[MAX_SIZE][MAX_SIZE];
	uint8_t wall_north[MAX_SIZE][MAX_SIZE];						// 壁情報
	uint8_t wall_east[MAX_SIZE][MAX_SIZE];						// 壁情報
	uint8_t wall_south[MAX_SIZE][MAX_SIZE];						// 壁情報
	uint8_t wall_west[MAX_SIZE][MAX_SIZE];						// 壁情報
	uint8_t is_search[MAX_SIZE][MAX_SIZE];						// 探索済みフラグ
	uint8_t step_mode;								// 歩数マップ作成時の状態(探索用 最短走行用)
}maze_t;


extern mazeDef_t mazeDef;


void Init_maze(void);
void Maze_Set(void);
void MAZE_Create_Step(void);
void Maze_GetWall(void);
void Update_Position(int8_t next_motion);
void MAZE_Printf_Step(void);
void Maze_GoalCheck(uint8_t flag_goal_is);


#ifdef __cplusplus
}
#endif
#endif