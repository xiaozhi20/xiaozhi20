#include <iostream>
#include <string>
#include <stdlib.h>
#include <graphics.h>
#include <conio.h>

#include "box_man.h"


int MAP[MAP_LINE][MAP_COLUMN] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0},
	{0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
	{0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0},
	{0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0},
	{0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

IMAGE images[MAP_IMAGES];


// 初始化地图
void initMap();

// 游戏控制
void gameControl();

// 人物行走操作
void moveOperation(DIRECTION);

// 获取步数统计（待优化）
char * getStep(int);

bool isGameOver(){
	for(int i = 0; i < MAP_LINE; i++){
		for(int j = 0; j < MAP_COLUMN; j++){
			if(MAP[i][j] == 2){
				return false;
			}
		}
	}
	return true;
}

// 游戏结束
void gameIsOver(){
	cleardevice();
	settextstyle(20, 0, "宋体");
	outtextxy(350, 250, "恭喜过关！");
}

human_struct human = {5, 5, man, 0};

int main(){

	
	initMap();

	gameControl();

	system("pause");
	closegraph();
	return 0;

}

void initMap(){
	IMAGE bg_image;

	loadimage(&bg_image, "blackground.bmp", WINDOW_WIDTH, WINDOW_HEIGHT, true);
	loadimage(&images[wall], "wall_right.bmp", RATIO, RATIO, true);
	loadimage(&images[map_floor], "floor.bmp", RATIO, RATIO, true);
	loadimage(&images[des], "des.bmp", RATIO, RATIO, true);
	loadimage(&images[man], "man.bmp", RATIO, RATIO, true);
	loadimage(&images[box], "box.bmp", RATIO, RATIO, true);

	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);

	putimage(0, 0, &bg_image);

	for(int i = 0; i < MAP_LINE; i++){
		for(int j = 0; j < MAP_COLUMN; j++){
			putimage(RATIO * j, RATIO * i, &images[MAP[i][j]]);
		}
	}

	settextstyle(20, 0, "宋体");
	outtextxy(750, 80, "当前关卡：");
	outtextxy(750, 150, "当前步数：");
	outtextxy(850, 80, "1");
	outtextxy(850, 150, "0");

}


void gameControl(){

	bool gameOver = false;

	while(!gameOver){
		if(_kbhit()){
			char key = _getch();
			switch(key){
				case KEY_UP:
					moveOperation(UP);
					break;
				case KEY_DOWN:
					moveOperation(DOWN);
					break;
				case KEY_LEFT:
					moveOperation(LEFT);
					break;
				case KEY_RIGHT:
					moveOperation(RIGHT);
					break;
				case KEY_END:
					gameOver = true;
					cleardevice();
					exit(-1);
					break;
				default:
					break;
			}
			if(isGameOver()){
				gameOver = true;
				gameIsOver();
			}
		}
		Sleep(100);
	}
}


void moveOperation(DIRECTION directory){
	switch(directory){
		case UP:
			if(MAP[human.x - 1][human.y] >= 4 && MAP[human.x - 2][human.y] >= 1){

				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				putimage(RATIO * human.y, RATIO * (human.x - 1), &images[human.status]);
				putimage(RATIO * human.y, RATIO * (human.x - 2), &images[box]);	
				if(MAP[human.x - 1][human.y] == 5){
					MAP[human.x - 1][human.y] = 2;
				} else{
					MAP[human.x - 1][human.y] = 1;
				}
				
				if(MAP[human.x - 2][human.y] == 2){
					MAP[human.x - 2][human.y] = 5;
				} else{
					MAP[human.x - 2][human.y] = 4;
				}
				human.x--;
				human.stepCount++;
			} else if(MAP[human.x - 1][human.y] >= 1 && MAP[human.x - 1][human.y] < 4){
				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				
				putimage(RATIO * human.y, RATIO * (human.x - 1), &images[human.status]);
				human.x--;
				human.stepCount++;
			}
			
			break;
		case DOWN:
			if(MAP[human.x + 1][human.y] >= 4 && MAP[human.x + 2][human.y] >= 1){
				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				putimage(RATIO * human.y, RATIO * (human.x + 1), &images[human.status]);
				putimage(RATIO * human.y, RATIO * (human.x + 2), &images[box]);
				if(MAP[human.x + 1][human.y] == 5){
					MAP[human.x + 1][human.y] = 2;
				} else{
					MAP[human.x + 1][human.y] = 1;
				}
				if(MAP[human.x + 2][human.y] == 2){
					MAP[human.x + 2][human.y] = 5;
				} else{
					MAP[human.x + 2][human.y] = 4;
				}
				human.x++;
				human.stepCount++;

			} else if(MAP[human.x + 1][human.y] >= 1 && MAP[human.x + 1][human.y] < 4){
				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				putimage(RATIO * human.y, RATIO * (human.x + 1), &images[human.status]);
				human.x++;
				human.stepCount++;
			}
			break;
		case LEFT:
			if(MAP[human.x][human.y - 1] >= 4 && MAP[human.x][human.y - 2] >= 1){
				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				putimage(RATIO * (human.y - 1), RATIO * human.x, &images[human.status]);
				putimage(RATIO * (human.y - 2), RATIO * human.x, &images[box]);
				if(MAP[human.x][human.y - 1] == 5){
					MAP[human.x][human.y - 1] = 2;
				} else{
					MAP[human.x][human.y - 1] = 1;
				}
				
				if(MAP[human.x][human.y - 2] == 2){
					MAP[human.x][human.y - 2] = 5;
				} else{
					MAP[human.x][human.y - 2] = 4;
				}
				human.y--;
				human.stepCount++;
			} else if(MAP[human.x][human.y - 1] >= 1 && MAP[human.x][human.y - 1] < 4){
				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				putimage(RATIO * (human.y - 1), RATIO * human.x, &images[human.status]);
				human.y--;
				human.stepCount++;
			}
			break;
		case RIGHT:
			if(MAP[human.x][human.y + 1] >= 4 && MAP[human.x][human.y + 2] >= 1){
				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					int value = MAP[human.x][human.y];
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				putimage(RATIO * (human.y + 1), RATIO * human.x, &images[human.status]);
				putimage(RATIO * (human.y + 2), RATIO * human.x, &images[box]);
				if(MAP[human.x][human.y + 1] == 5){
					MAP[human.x][human.y + 1] = 2;
				} else{
					MAP[human.x][human.y + 1] = 1;
				}
				
				if(MAP[human.x][human.y + 2] == 2){
					MAP[human.x][human.y + 2] = 5;
				} else{
					MAP[human.x][human.y + 2] = 4;
				}
				human.y++;
				human.stepCount++;
			} else if(MAP[human.x][human.y + 1] >= 1 && MAP[human.x][human.y + 1] < 4){
				if(MAP[human.x][human.y] == 3){
					putimage(RATIO * human.y, RATIO * human.x, &images[map_floor]);
				} else{
					putimage(RATIO * human.y, RATIO * human.x, &images[MAP[human.x][human.y]]);
				}
				putimage(RATIO * (human.y + 1), RATIO * human.x, &images[human.status]);
				human.y++;
				human.stepCount++;
			}
			break;
		default:
			break;
	}
	char *str = getStep(human.stepCount);
	outtextxy(850, 150, str);
	delete [] str;
}



char * getStep(int step){
	if(!step){
		return NULL;
	}

	bool isDouble = false;
	char *p = NULL;
	int value = step % 10;
	int i = 1, j = 0;


	if(value == 0){
		isDouble = true;
		j = step;
	}

	while(step /= 10){
		value = value * 10 + step % 10;
		i++;
	}
	
	p = new char[i + 1];
	p[i] = 0;

	if(isDouble){
		while(--i){
			p[i] = 48;
		}
		value = j / 10;
	}

	i = 0;
	while(value){
		j = value % 10;
		switch(j){
			case 0:
				p[i] = 48;
				break;
			case 1:
				p[i] = 49;
				break;
			case 2:
				p[i] = 50;
				break;
			case 3:
				p[i] = 51;
				break;
			case 4:
				p[i] = 52;
				break;
			case 5:
				p[i] = 53;
				break;
			case 6:
				p[i] = 54;
				break;
			case 7:
				p[i] = 55;
				break;
			case 8:
				p[i] = 56;
				break;
			case 9:
				p[i] = 57;
				break;
			default:
				p[i] = 48;
				break;
		}
		i++;
		value /= 10;
	}
	   
	return p;
}
