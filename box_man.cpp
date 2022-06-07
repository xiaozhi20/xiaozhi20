#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>

#include "box_man.h"
#include "database.h"

using namespace std;


IMAGE images[ALL];

struct _POS man;  //С���ڶ�ά�����е�λ��

/*��Ϸ��ͼ*/
int map[LINE][COLUMN] = {0};
/*int map[LINE][COLUMN] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
	{ 0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0 },
	{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0 },
	{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0 },
	{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0 },
	{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0 },
	{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};*/
//0,0,0,0,0,0,0,0,0,0,0,0|0,1,0,1,1,1,1,1,1,1,0,0|0,1,4,1,0,2,1,0,2,1,0,0|0,1,0,1,0,1,0,0,1,1,1,0|0,1,0,2,0,1,1,4,1,1,1,0
//|0,1,1,1,0,3,1,1,1,4,1,0|0,1,2,1,1,4,1,1,1,1,1,0|0,1,0,0,1,0,1,1,0,0,1,0|0,0,0,0,0,0,0,0,0,0,0,0
/**********************************************
*�ж���Ϸ�Ƿ����������������κ�һ������Ŀ�ĵأ��ʹ�����Ϸ����
*���룺 ��
*����ֵ�� 
*     true -  ��Ϸ����   false - ��Ϸ����
**********************************************/
bool isGameOver(){
	for(int i = 0; i< LINE; i++){
		for(int j = 0; j < COLUMN; j++){
			if(map[i][j] == BOX_DES) return false;
		}
	}
	return true;
}

/**********************************************
*��Ϸ���������������ͨ�غ���ʾ
*���룺 
*     bg - ����ͼƬ������ָ��
*����ֵ�� ��
**********************************************/
void gameOverScene(IMAGE *bg){
	putimage(0, 0, bg);
	settextcolor(WHITE);
	RECT rec = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	settextstyle(20, 0, _T("����"));
	drawtext(_T("��ϲ��~ \n�����ڳ�Ϊ��һ���ϸ�İ�������˾����"), &rec,  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/**********************************************
*�ı���Ϸ��ͼ��ͼ��һ���Ӧ���߲�������ʾ
*���룺
*     pos -   �����ڵ�ͼ����������±�
*     prop   - ���ߵ�����
*����ֵ�� ��
**********************************************/
void changeMap(POS *pos, PROPS prop){
	map[pos->x][pos->y] = prop;
	putimage(START_X + pos->y * RATIO, START_Y+ pos->x * RATIO, &images[prop]);
}

/**********************************************
*ʵ����Ϸ�ĸ������ϡ��¡����ң��Ŀ���
* ���룺
*  direct - ��ǰ������ 
* ����� ��
**********************************************/
void gameControl(DIRECTION direct){

	POS next_pos = man;
	POS next_next_pos = man;
	switch(direct){
	case UP:
		next_pos.x--;
		next_next_pos.x-=2;
		break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x+=2;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y-=2;
		break;
	case RIGHT:
		next_pos.y++;
		next_next_pos.y+=2;
		break;
	}
	//��չ�� next_pos.x>=0 && next_pos.x<LINE && next_pos.y>=0 && next_pos.y <COLUMN
	if( isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR ){//�˵�ǰ���ǵذ�
		changeMap(&next_pos, MAN); //С��ǰ��һ��
		changeMap(&man, FLOOR);
		man = next_pos;
	}else if(isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX){//�˵�ǰ��������
		//�������������ǰ���ǵذ����������Ŀ�ĵ�
		if( map[next_next_pos.x][next_next_pos.y] == FLOOR){
			changeMap(&next_next_pos, BOX);
			changeMap(&next_pos, MAN); //С��ǰ��һ��
			changeMap(&man, FLOOR);
			man = next_pos;
		}else if(map[next_next_pos.x][next_next_pos.y] == BOX_DES){
			changeMap(&next_next_pos, HIT);
			changeMap(&next_pos, MAN); //С��ǰ��һ��
			changeMap(&man, FLOOR);
			man = next_pos;
		}
	}
}

/*
ѭ����¼�ӿ�

*/
bool login(userinfo& user) {
	bool ret = false;
	int times = 0;//��½����
	do {
		cout << "�������û�����";
		cin >> user.username;

		cout << "���������룺";
		cin >> user.password;

		//�ӿ�  ��ȡ�û���Ϣ
		//����boolֵ  ��֤�Ƿ��ȡ�ɹ�
		ret = fetch_user_info(user);
		
		//��½�����ۼӣ��������޾�����ѭ��
		times++;
		if (times >= MAX_RETRY_TIMES) {
			break;
		}
		if ( ret== false) {
			cout << "��½ʧ�ܣ����������룡" << endl;

		}
	} while (!ret);

	return ret;
	
}


int main(void){
	//�����֤

	userinfo user;//�����û��ṹ��
	levelinfo level;//������û������ؿ�
	bool ret = false;

	//cout << "�������û�����";
	//cin >> user.username;

	//cout << "���������룺";
	//cin >> user.password;

	////�ӿ�  ��ȡ�û���Ϣ
	////����boolֵ  ��֤�Ƿ��ȡ�ɹ�
	//if (fetch_user_info(user) == false) {
	//	cout << "��½ʧ�ܣ������µ�¼��" << endl;
	//	::system("pause");
	//	exit(-1);
	//}
	if (!login(user)) {
		cout << "��½ʧ�ܣ������µ�¼��" << endl;
		::system("pause");
		exit(-1);
	}
	else {
		cout << "��¼�ɹ����û�id:"<<user.id<<"���ؿ�id:"<<user.level_id<<"���뿪ʼ���ı��ݣ�" << endl;
		::system("pause");
	}

	//�����û�ID��ȡ�ؿ�����
	ret = fetch_level_info(level, user.level_id);//��ȡ�ɹ�������

	if (!ret) {
		cout << "��ȡ�ؿ�����ʧ�ܣ������ԣ�"<<endl;
		::system("pause");
		exit(-1);
	}

	//�����ݿ��еĵ�ͼת����map��
	ret = transform_map_db2array(level, map);
	

	::system("pause");

	IMAGE bg_img;

	//��̨��Ϸ
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_img, _T("blackground.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_img);

	//���ص���ͼ��
	loadimage(&images[WALL], _T("wall_right.bmp"), RATIO, RATIO, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX_DES], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[MAN], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[BOX], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[HIT], _T("box.bmp"), RATIO, RATIO, true);

	for(int i = 0; i< level.map_row; i++){
		for(int j = 0; j < level.map_column; j++){
			if(map[i][j] == MAN) {
				man.x = i;
				man.y = j;
			}

			putimage(START_X+j*RATIO, START_Y+i*RATIO, &images[map[i][j]]);
		}
	}

	//��Ϸ����
	bool quit = false;

	do {
		if(_kbhit()){ //��Ұ���
			char ch = _getch();

			if(ch == KEY_UP){
				gameControl(UP);
			}else if(ch == KEY_DOWN){
				gameControl(DOWN);
			}else if(ch == KEY_LEFT){
				gameControl(LEFT);
			}else if(ch == KEY_RIGHT){
				gameControl(RIGHT);
			}else if(ch == KEY_QUIT){
				quit = true;
			}
			if(isGameOver()){
				gameOverScene(&bg_img);
				quit = true;
			}
		}
		Sleep(100);
	}while(quit==false); //!quit

	system("pause");

	//��Ϸ�������ͷ���Դ
	closegraph();
	return 0;
}