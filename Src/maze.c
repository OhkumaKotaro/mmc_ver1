#include "maze.h"
#include "gpio.h"
#include "global.h"


/**************variable**********************/
mazeDef_t mazeDef;
maze_t maze;



/****************************************************************************************************
 * outline : input maze size , goal point
 * argument : void
 * return : void
******************************************************************************************************/
void Maze_Set(void){
    mazeDef.maze_size_x = 15;
    mazeDef.maze_size_y = 15;
    mazeDef.maze_goal_x = 1;
    mazeDef.maze_goal_y = 0;
}

/****************************************************************************************************
 * outline : initialize maze date
 * argument : void
 * return : void
******************************************************************************************************/
void Init_maze(void) {
	//init wall and is_search
	for (uint8_t i = 0; i <= mazeDef.maze_size_y; i++)
	{
		for (uint8_t j = 0; j <= mazeDef.maze_size_x; j++)
		{
			maze.wall_east[i][j] = 0;
			maze.wall_north[i][j] = 0;
			maze.wall_south[i][j] = 0;
			maze.wall_west[i][j] = 0;
			maze.is_search[i][j] = 0;
			maze.goal[i][j] = 0;
		}
	}
	//input start wall
	maze.wall_east[0][0] = 1;
	maze.wall_west[1][0] = 1;
	//input outer
	for (uint8_t i = 0; i <= mazeDef.maze_size_x; i++)
	{
		maze.wall_east[mazeDef.maze_size_y][i] = 1;
		maze.wall_west[0][i] = 1;
        maze.wall_south[i][0] = 1;
		maze.wall_north[i][mazeDef.maze_size_x] = 1;
	}
}


/****************************************************************************************************
 * outline : create map
 * argument : void
 * return : void
******************************************************************************************************/
void MAZE_Create_Step(void) {
	maze.goal[mazeDef.maze_goal_y][mazeDef.maze_goal_x] = 1;
	for (uint8_t i = 0; i <= mazeDef.maze_size_y; i++)
	{
		for (uint8_t j = 0; j <= mazeDef.maze_size_x; j++)
		{
			if (maze.goal[i][j] == 1) {
				maze.step[i][j] = 0;
			}
			else
			{
				maze.step[i][j] = MAX_STEP;
			}

		}
	}

	short end_flag = 1;
	uint8_t stepNum = 0;
	while (end_flag==1) {
		end_flag = 0;
		for (uint8_t i = 0; i <= mazeDef.maze_size_y; i++)
		{
			for (uint8_t j = 0; j <= mazeDef.maze_size_x; j++)
			{
				if (maze.step[i][j] == MAX_STEP) 
				{
					if (j < mazeDef.maze_size_x) //north wall
					{
						if (maze.wall_north[i][j] == 0 && maze.step[i][j+1] == stepNum) 
						{
							maze.step[i][j] = stepNum + 1;
							end_flag = 1;
						}
					}
					if (i < mazeDef.maze_size_y)//east wall
					{
						if (maze.wall_east[i][j] == 0 && maze.step[i+1][j] == stepNum) 
						{
							maze.step[i][j] = stepNum + 1;
							end_flag = 1;
						}
					}
					if (j>0)//south wall
					{
						if (maze.wall_south[i][j] == 0 && maze.step[i][j-1]==stepNum)
						{
							maze.step[i][j] = stepNum + 1;
							end_flag = 1;
						}
					}
					if (i>0)//west wall
					{
						if (maze.wall_west[i][j] == 0 && maze.step[i-1][j]==stepNum)
						{
							maze.step[i][j] = stepNum + 1;
							end_flag = 1;
						}
					}
				}
			}
		}
		stepNum ++;
	}
}

void Maze_GetWall(void){
	switch(position.dir){
		case NORTH:
			if(sensor.wall[5]==true){
				
			}
			break;
		case EAST:

			break;
		case SOUTH:

			break;
		case WEST:

			break;
	}
}

void Update_Position(int8_t next_motion){
	switch(next_motion){
		case LEFT:
			switch(position.dir){
				case NORTH:
					position.x --;
					position.dir = WEST;
					break;
				case EAST:
					position.y ++;
					position.dir = NORTH;
					break;
				case SOUTH:
					position.x ++;
					position.dir = EAST;
					break;
				case WEST:
					position.y --;
					position.dir = SOUTH;
					break;
			}
			break;
		case STRAIGHT:
			switch(position.dir){
				case NORTH:
					position.y ++;
					break;
				case EAST:
					position.x ++;
					break;
				case SOUTH:
					position.y --;
					break;
				case WEST:
					position.x --;
					break;
			}
			break;
		case RIGHT:
			switch(position.dir){
				case NORTH:
					position.x ++;
					position.dir = EAST;
					break;
				case EAST:
					position.y --;
					position.dir = SOUTH;
					break;
				case SOUTH:
					position.x --;
					position.dir = WEST;
					break;
				case WEST:
					position.y ++;
					position.dir = NORTH;
					break;
			}
			break;
		case UTURN:
			switch(position.dir){
				case NORTH:
					position.y --;
					position.dir = SOUTH;
					break;
				case EAST:
					position.x --;
					position.dir = WEST;
					break;
				case SOUTH:
					position.y ++;
					position.dir = NORTH;
					break;
				case WEST:
					position.x ++;
					position.dir = EAST;
					break;
			}
			break;
	}
}


/****************************************************************************************************
 * outline : output step
 * argument : void
 * return : void
******************************************************************************************************/
void MAZE_Printf_Step(void) {
	for (uint8_t i = 0; i <= mazeDef.maze_size_y; i++)
	{
		for (uint8_t j = 0; j <= mazeDef.maze_size_x; j++)
		{
			printf("+");
			if (maze.wall_west[i][j] == 1)
			{
				printf("---");
			}
			else if(maze.wall_west[i][j] == 0)
			{
				printf("   ");
			}
		}
		printf("+\r\n");
		for (uint8_t j = 0; j <= mazeDef.maze_size_x; j++)
		{
			if (maze.wall_south[i][j] == 1)
			{
				printf("|");
			}
			else
			{
				printf(" ");
			}
			printf("%3d", maze.step[i][j]);
		}
		printf("|\r\n");
	}
	for (uint8_t j = 0; j <= mazeDef.maze_size_x; j++)
	{
		printf("+");
		printf("---");
	}
	printf("+\r\n\n");
}

void Maze_GoalCheck(uint8_t flag_goal_is){
	if(position.x==mazeDef.maze_goal_x && position.y==mazeDef.maze_goal_y){
		flag_goal_is = true;
	}
}