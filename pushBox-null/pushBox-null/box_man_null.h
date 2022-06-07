
#ifndef BOX_MAN_H
#define BOX_MAN_H



#define WINDOW_WIDTH  883		// ��Ϸ��Ļ��� - ����
#define WINDOW_HEIGHT 550		// ��Ϸ��Ļ�߶� - ����

#define MAP_LINE	9			// ��Ϸ��ͼ��������
#define MAP_COLUMN	12			// ��Ϸ��ͼ��������
#define MAP_IMAGES	6			// ��Ϸ��ͼͼƬ���߸���
#define RATIO		61			// ���߳ߴ� - ����

#define KEY_UP		'w'			// ��Ϸ�ȼ����� �ϼ�
#define KEY_DOWN	's'			// ��Ϸ�ȼ����� �¼�
#define KEY_LEFT	'a'			// ��Ϸ�ȼ����� ���
#define KEY_RIGHT	'd'			// ��Ϸ�ȼ����� �Ҽ�
#define KEY_END		'q'			// ��Ϸ�ȼ����� �˳���


// ����ö�ٶ���
// wall  ǽ��
// map_floor  �ذ�
// des Ŀ�ĵ�
// man ����
// box ����
enum material{			
	wall,
	map_floor,
	des,
	man,
	box
};

// �������߷���ö�ٶ���
// �ϡ��¡�����
enum DIRECTION{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct human_struct{
	int x;
	int y;
	material status;
	int stepCount = 0;
};

const unsigned short COUNT = 4;  // ͳ�Ʋ�����ʹ�õ��ڴ�ռ�

#endif // !BOX_MAN_H


