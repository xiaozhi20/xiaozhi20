#include "database.h"
#include<mysql.h>
#include<stdio.h>

#define DB_NAME "box_man"
#define DB_HOST "127.0.0.1"
#define DB_PORT 3306
#define DB_USER "root"
#define DB_USER_PASSWD "root"

static int debug = 1;//调试模式1  运行模式0

bool connect_db(MYSQL& mysql);//函数声明

/******************
功能：通过用户名和密码获取信息
输入：
		user-用户信息结构体

返回值：
		成功true   否则false

*/
bool fetch_user_info(userinfo& user) {
	MYSQL mysql;//数据库句柄
	MYSQL_RES* res;
	MYSQL_ROW row;
	char sql[256];
	bool ret = false;

	//1.连接到数据库
	if (connect_db(mysql) == false) {
		return false;
	}


	//2.根据用户名和密码获取用户信息（id  level_id）select * from users where username='zzb'&&password=md5('123zzb');
	snprintf(sql,256,"select id, level_id from users where username='%s' and password=md5('%s')",user.username.c_str(),user.password.c_str());
	ret = mysql_query(&mysql,sql);//正确返回零

	if (ret) {
		printf("数据库连接出错%s 错误原因：%s\n", sql,mysql_error(&mysql));
		mysql_close(&mysql);
		return false;
	}
	//3.获取结果
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);
	
	if (row == NULL) {
		mysql_free_result(res);//释放结果集
		mysql_close(&mysql);
		return false;
	}
	user.id = atoi(row[0]);//atoi 字符串转为整型
	user.level_id = atoi(row[1]);

	if (debug) {
		printf("userid: %d  level_id: %d\n", user.id, user.level_id);
	}

	//4.返回结果
	mysql_free_result(res);//释放结果集
	mysql_close(&mysql);//关闭数据库
	return true;

}

/******************
功能：通过关卡ID获取完整的关卡信息（如地图，下一关等）
输入：
		level-保存关卡信息结构体变量
		level_id-要获取的关卡id

返回值：
		成功true   否则false

*/
bool fetch_level_info(levelinfo& level, int level_id) {
	MYSQL mysql;//数据库句柄
	MYSQL_RES* res;
	MYSQL_ROW row;
	char sql[256];
	bool ret = false;

	//1.连接到数据库
	if (connect_db(mysql) == false) {
		return false;
	}

	//2.根据关卡id查询数据库获取关卡地图信息
	snprintf(sql,256,"select name, map_row, map_column, map_data, next_level_id from levels where id =%d",level_id);
	ret = mysql_query(&mysql, sql);//正确返回零

	if (ret) {
		printf("数据库连接出错%s 错误原因：%s\n", sql, mysql_error(&mysql));
		mysql_close(&mysql);
		return false;
	}

	//3.获取结果
	res = mysql_store_result(&mysql);
	row = mysql_fetch_row(res);

	if (row == NULL) {
		mysql_free_result(res);//释放结果集
		mysql_close(&mysql);
		return false;
	}

	level.id = level_id;
	level.name = row[0];
	level.map_row = atoi(row[1]);//字符串转为整数
	level.map_column = atoi(row[2]);
	level.map_data = row[3];
	level.next_level_id = atoi(row[5]);

	if (debug) {
		printf("level id: %d name: %s map_row: %d map_column: %d map_data: %s next_level_id: %d\n", level.id, level.name.c_str(), level.map_row, level.map_column, level.map_data.c_str(), level.next_level_id);
	}

	//4.返回结果
	mysql_free_result(res);//释放结果集
	mysql_close(&mysql);//关闭数据库
	return true;
 

}


bool connect_db(MYSQL& mysql) {
	//初始化句柄
	mysql_init(&mysql);

	//设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//连接数据库
	//mysql_real_connect(&mysql,"127.0.0.1","root","root","box_man", 3306, NULL,0);//此处选择宏定义
	if (mysql_real_connect(&mysql, DB_HOST, DB_USER, DB_USER_PASSWD, DB_NAME, DB_PORT, NULL, 0) == NULL) {
		printf("数据库连接出错，错误原因：%s\n", mysql_error(&mysql));
		return false;
	}


	return true;
}

bool transform_map_db2array(levelinfo& level, int map[LINE][COLUMN]) {
	if (level.map_row > LINE || level.map_column > COLUMN) {
		printf("地图超大，请重新设置！\n");
		return false;
	}
	if (level.map_data.length() < 1) {
		printf("地图数据有误，请重新设置！\n");
		return false;
	}

	int start = 0, end = 0;
	int row = 0, column = 0;

	do {
		end = level.map_data.find('|', start);// 从start开始查找  到发现‘|’，返回其位置下标
		if (end < 0) {

			end = level.map_data.length();
		}
		if (start >= end) break;
		string line = level.map_data.substr(start,end-start);
		printf("get line: %s\n",line.c_str());

		//对行地图数据进行解析
		char* next_token = NULL;
		char* item = strtok_s((char*)line.c_str(), ",", &next_token);//将数字提取出来

		column = 0;
		while (item && column<level.map_column) {

			printf("%s ",item);
			map[row][column] = atoi(item);
			column++;
			item = strtok_s(NULL,",",&next_token);
		}

		if (column < level.map_column) {
			printf("地图解析出错，终止！\n");
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
		printf("地图行数少于设定，%d(need: %d),终止！\n",row,level.map_row);
		return false;
	}
	
	return true;
}