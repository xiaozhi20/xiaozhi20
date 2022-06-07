#include<iostream>

using namespace std;

#define LINE   48
#define COLUMN 48

//�����û���Ϣ�Ľṹ��
typedef struct _userinfo
{
	int id;//�û�ID
	string username;
	string password;
	int level_id;

}userinfo;

typedef struct _levelinfo
{
	int id;//�ؿ�ID
	string name;
	int map_row;
	int map_column;
	string map_data;
	int next_level_id;

}levelinfo;


//��ͷ�ļ������� ����  
bool fetch_user_info(userinfo &user);
bool fetch_level_info(levelinfo& level, int level_id);
bool transform_map_db2array(levelinfo& level, int map[LINE][COLUMN]);
