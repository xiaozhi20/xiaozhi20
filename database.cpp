#include "database.h"
#include<mysql.h>
#include<stdio.h>

#define DB_NAME "box_man"
#define DB_HOST "127.0.0.1"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_USER_PASSWD "root"

static int debug = 1;//����ģʽ1  ����ģʽ0

bool connect_db(MYSQL& mysql);//��������

/******************
���ܣ�ͨ���û����������ȡ��Ϣ
���룺
		user-�û���Ϣ�ṹ��

����ֵ��
		�ɹ�true   ����false

*/
bool fetch_user_info(userinfo& user) {
	MYSQL mysql;//���ݿ���
	MYSQL_RES* res;
	MYSQL_ROW row;
	char sql[256];
	bool ret = false;

	//1.���ӵ����ݿ�
	if (connect_db(mysql) == false) {
		return false;
	}


	//2.�����û����������ȡ�û���Ϣ��id  level_id��select * from users where username='zzb'&&password=md5('123zzb');
	snprintf(sql,256,"select id, level_id from users where username='%s' and password=md5('%s')",user.username.c_str(),user.password.c_str());
	ret = mysql_query(&mysql,sql);//��ȷ������

	if (ret) {
		printf("���ݿ����ӳ���%s ����ԭ��%s\n", sql,mysql_error(&mysql));
		mysql_close(&mysql);
		return false;
	}
	//3.��ȡ���
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	
	if (row == NULL) {
		mysql_free_result(res);//�ͷŽ����
		mysql_close(&mysql);
		return false;
	}
	user.id = atoi(row[0]);//atoi �ַ���תΪ����
	user.level_id = atoi(row[1]);

	if (debug) {
		printf("userid: %d  level_id: %d\n", user.id, user.level_id);
	}

	//4.���ؽ��
	mysql_free_result(res);//�ͷŽ����
	mysql_close(&mysql);//�ر����ݿ�
	return true;

}

/******************
���ܣ�ͨ���ؿ�ID��ȡ�����Ĺؿ���Ϣ�����ͼ����һ�صȣ�
���룺
		level-����ؿ���Ϣ�ṹ�����
		level_id-Ҫ��ȡ�Ĺؿ�id

����ֵ��
		�ɹ�true   ����false

*/
bool fetch_level_info(levelinfo& level, int level_id) {
	MYSQL mysql;//���ݿ���
	MYSQL_RES* res;
	MYSQL_ROW row;
	char sql[256];
	bool ret = false;

	//1.���ӵ����ݿ�
	if (connect_db(mysql) == false) {
		return false;
	}

	//2.���ݹؿ�id��ѯ���ݿ��ȡ�ؿ���ͼ��Ϣ
	snprintf(sql,256,"select name, map_row, map_column, map_data, next_level_id from levels where id =%d",level_id);
	ret = mysql_query(&mysql, sql);//��ȷ������

	if (ret) {
		printf("���ݿ����ӳ���%s ����ԭ��%s\n", sql, mysql_error(&mysql));
		mysql_close(&mysql);
		return false;
	}

	//3.��ȡ���
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	if (row == NULL) {
		mysql_free_result(res);//�ͷŽ����
		mysql_close(&mysql);
		return false;
	}

	level.id = level_id;
	level.name = row[0];
	level.map_row = atoi(row[1]);//�ַ���תΪ����
	level.map_column = atoi(row[2]);
	level.map_data = row[3];
	level.next_level_id = atoi(row[5]);

	if (debug) {
		printf("level id: %d name: %s map_row: %d map_column: %d map_data: %s next_level_id: %d\n", level.id, level.name.c_str(), level.map_row, level.map_column, level.map_data.c_str(), level.next_level_id);
	}

	//4.���ؽ��
	mysql_free_result(res);//�ͷŽ����
	mysql_close(&mysql);//�ر����ݿ�
	return true;
 

}


bool connect_db(MYSQL& mysql) {
	//��ʼ�����
	mysql_init(&mysql);

	//�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//�������ݿ�
	//mysql_real_connect(&mysql,"127.0.0.1","root","root","box_man", 3306, NULL,0);//�˴�ѡ��궨��
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_USER_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL) {
		printf("���ݿ����ӳ�������ԭ��%s\n", mysql_error(&mysql));
		return false;
	}


	return true;
}

bool transform_map_db2array(levelinfo& level, int map[LINE][COLUMN]) {
	if (level.map_row > LINE || level.map_column > COLUMN) {
		printf("��ͼ�������������ã�\n");
		return false;
	}
	if (level.map_data.length() < 1) {
		printf("��ͼ�����������������ã�\n");
		return false;
	}

	int start = 0, end = 0;
	int row = 0, column = 0;

	do {
		end = level.map_data.find('|', start);// ��start��ʼ����  �����֡�|����������λ���±�
		if (end < 0) {

			end = level.map_data.length();
		}
		if (start >= end) break;
		string line = level.map_data.substr(start,end-start);
		printf("get line: %s\n",line.c_str());

		//���е�ͼ���ݽ��н���
		char* next_token = NULL;
		char* item = strtok_s((char*)line.c_str(), ",", &next_token);//��������ȡ����

		column = 0;
		while (item && column<level.map_column) {

			printf("%s ",item);
			map[row][column] = atoi(item);
			column++;
			item = strtok_s(NULL,",",&next_token);
		}

		if (column < level.map_column) {
			printf("��ͼ����������ֹ��\n");
			return false;
		}

		printf("\n");
		row++;

		if (row >= level.map_row) {
			break;
		}

		start = end + 1;
	} while (1 == 1);
	
	if (row < level.map_row) {
		printf("��ͼ���������趨��%d(need: %d),��ֹ��\n",row,level.map_row);
		return false;
	}
	
	return true;
}