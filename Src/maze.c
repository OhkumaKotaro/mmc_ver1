#include "maze.h"
#include "gpio.h"


/**************variable**********************/
mazeDef_t mazeDef;
maze_t maze;



/****************************************************************************************************
 * outline : input maze size , goal point
 * argument : void
 * return : void
******************************************************************************************************/
void Maze_Set(void){
    mazeDef.maze_size_x = 7;
    mazeDef.maze_size_y = 7;
    mazeDef.maze_goal_x = 3;
    mazeDef.maze_goal_y = 3;
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


/****************************************************************************************************
 * outline : output step
 * argument : void
 * return : void
******************************************************************************************************/
void MAZE_Out_Step(void) {
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