#include "graphics.h"
#include "string.h"

#define _CRT_SECURE_NO_WARNINGS

#define MaxX 1280 // ������������ �� X 
#define MaxY 720 // ������������ �� Y

#define h 60 // ������ ������ ���������, ������
#define L 60 // ������ ������ ���������, �����
#define n 10 // ������ ���������, ���������� ����� � �������� 
#define r 12 // ������ ������ (�������)
#define x0 50 // ����� ������ ���� ���������
#define y0 50 // ����� ������ ���� ���������

#define ESC 27 // ������� ������

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
enum Color {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};



void zastavka() {
	char word[17] = "Battle of Mobile", s[2];
	int x = 50, y, dx = 20;
	for (int i = 0; i < 18; i++) {
		strnset(s, word[i], 1); //�������� � ���������� s ���� �����
		s[1] = '\0';
		setcolor(Red);
		settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3); // ����� ������
		y = 500;
		outtextxy(x, y, s); //����� ������
		while (y > 300) {
			delay(25);
			setcolor(Black);
			outtextxy(x, y, s);
			y = y - dx;
			setcolor(Red);
			outtextxy(x, y, s);
		}
		x = x + 35;
	}
	char *autor[3] = { "���������: ���������� ����", "������ 803 ��1", "�������������:������� �.�." };
	int len, xA;
	y = 500, dx = 20;
	setcolor(White);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 1);
	for (int i = 0; i < 3; i++) {
		xA = 550;
		len = strlen(autor[i]);
		for (int j = 0; j < len; j++) {
			strncpy(s, autor[i] + j, 1);
			s[1] = '\0';
			outtextxy(xA, y, s);
			delay(35);
			xA = xA + dx;
		}
		y = y + 30;
	}
}
void counter(int k, int x, int y) {
	char s[10];
	sprintf(s, "%d", k); // ������� ����������� ����� k � ������ s
	setfillstyle(1, Black);  // ������ ����
	bar(MaxX - x, 30, MaxY - y, 50); // ������ ������ ������������� ������ �����
	setcolor(White); // ����� ����
	settextstyle(1, 0, 2); // ����� ������
	outtextxy(MaxX - x, y, s); // ������� �����
}

void ball(int x, int y, Color c) 
{
	setcolor(c);
	setfillstyle(1, c);
	fillellipse(x, y, r, r);
}
void load_hero(int x, int y)
{
	readimagefile("2.gif", x, y, x - h+1, y - L+1);
}
void load_zlo(int x, int y)
{
	readimagefile("1.gif", x, y, x-h+1, y-L+1);
}
void load_priz(int x, int y)
{
	readimagefile("3.gif", x, y, x - h + 1, y - L + 1);
}
//void load_stena(int x, int y)
//{
//	readimagefile("4.gif", x - h + 1, y - L + 1);
//}
//void load_dver(int x, int y)
//{
//	readimagefile("5.gif", x, y, x - h , y - L);
//}

void brick(int x, int y, Color c) {
	setcolor(c);
	setfillstyle(1, c);
	bar(x, y, x + L, y + h);
}

int colision(int iBot, int jBot, int iHero, int jHero) { // ����� ��� ���������� � ���������� ���������
	if ((iBot == iHero) && (jBot == jHero)) {
		return 1;
	}
	else {
		return 0;
	}
}

void moveBot(int &i, int &j, int pole[n][n]) { //����� i � j ������� ������
	int x, y, ran;
	delay(100); //����� 
	x = x0 + j*h;
	y = y0 + i*L;
	
	
	brick(x, y, Black);
	ran = rand() % 4 + 1;
	switch (ran) {
	case 1: if ((j < n - 1) && (pole[i][j + 1] == 0)) j++; break; //������
	case 2: if ((i > 0) && (pole[i - 1][j] == 0))  i--; break; // �����
	case 3: if ((j > 0) && (pole[i][j - 1] == 0)) j--; break; //�����
	case 4: if ((i < n - 1) && (pole[i + 1][j] == 0)) i++; break; // ����
	}
	x = x0 + j*h;
	y = y0 + i*L;
	load_zlo(x, y);
}

void moveKolobok(int &i, int &j, int pole[][10], char key) {
	int x, y;
	x = x0 + j*h;
	y = y0 + i*L;

	brick(x, y, Black);
	switch (key) {
	case LEFT:
	case 'a': if ((j > 0) && (pole[i][j - 1] != 1)) { j--; } break; // ���� ��� ����� ��� �� ���� ����� �����, �� ������ ��������� (�����)
	case RIGHT:
	case 'd': if ((j < n - 1) && (pole[i][j + 1] != 1)) { j++; } break; // n=9 ������ ������� �����
	case UP:
	case 'w': if ((i > 0) && (pole[i - 1][j] != 1)) { i--; } break;
	case DOWN:
	case 's': if ((i < n - 1) && (pole[i + 1][j] != 1)) { i++; } break;
	}
	x = x0 + j*h;
	y = y0 + i*L;
	load_hero(x, y);
	while (kbhit()) { getch(); } // ���� ������� ������
}


void game() {
	cleardevice();
	FILE *f;
	int level = 1; //������ �������� � 1 ������
	int pole[n][n], i, j, iHero, jHero, k, t;
	int iBot[3], jBot[3], iPriz[7], jPriz[7]; // ������� ������� ������ ����� � ������
	int x, y; // �������� ����������
	char key = 0;
	do {
		switch (level) {
		case 1: f = fopen("map1.txt", "r"); break; // ��������� ����
		case 2: f = fopen("map2.txt", "r"); break;
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				fscanf(f, "%d", &pole[i][j]); //��������� ���� � ���� (fscanf - ��������� � �����)
			}
		}
		fclose(f); //��������� ����
		int count = 0;
		int k = 0, t = 0; //������� ���������� ������, t ��� ���������� ������
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				x = x0 + j*h; // �������������� ������ ������� � �������� ����������  X. ����� �������� ������ ���� ������. 
				// �0 �0 �������� �� ������ �� ������ �������� ���� ��� ��������� h � l ��� ������� ������ ��������
				y = y0 + i*L; // �������������� ������ ������ � �������� ���������� Y. ����� �������� ������ ���� ������. 
				switch (pole[i][j]) {
				case 1: 
					
					brick(x, y, DarkGray); break; //������ ����� ����� �������
				case 2: 
					load_hero(x, y);
					iHero = i;    //  ���������� ���������� �����
					jHero = j;
					pole[i][j] = 0;
					break;
				case 3: //���� � ������ ������� ����� 3, ������ ��� ����
					//ball(x + r, y + r, LightBlue); //��������� ������ ����� (����)
					load_zlo(x, y);
					iBot[k] = i;
					jBot[k] = j;
					k++; //������� ����� ������
					pole[i][j] = 0;
					break;
				case 4: // �����
					load_priz(x, y);
					iPriz[t] = i;
					jPriz[t] = j;
					t++;
					break;
				case 5: // �����
					brick(x, y, Brown);break;
				} // switch
			}  // for
		}
		int p = 0;
		int life = 3;
		setcolor(White);
		settextstyle(1, 0, 2);
		outtextxy(MaxX - 130, 10, "�����: ");
		outtextxy(MaxX - 130, MaxY - 920, "����: ");// ������� ����� ����:
		counter(life, 80, 40);
		counter(count, 80, 120);
		do {
			for (int i = 0; i < 3; i++) {  // ����������� ������ �� �������
				moveBot(iBot[i], jBot[i], pole);
			}
			if (kbhit()) {
				key = getch(); //���� ������� ���� ������, �� ������� �������
				if (key == NULL) {
					key = getch();
				}
				moveKolobok(iHero, jHero, pole, key); // ����������� �����
			}
			k = 0;
			for (i = 0; i < 3; i++)
			{
				if (colision(iBot[i], jBot[i], iHero, jHero)) {
			life--; //���� ���������� ������� � ����� �������, �� ������ ��������� ������������ � �������� �����
					counter(life, 80, 40); //����������� �����
					x = x0 + jHero*h; // �������������� ������ ������� � �������� ����������  X. ����� �������� ������ ���� ������. 
					y = y0 + iHero*L;
					 // ���� ����� ����������, �� ������� �����
					
					
					brick(x, y, Black);
					iHero = 3;
					jHero = 0; //���������� �� ��������� �������
					x = x0 + jHero*h; // �������������� ������ ������� � �������� ����������  X. ����� �������� ������ ���� ������. 
					y = y0 + iHero*L;
					load_hero(x, y); //��������������
				}
			}
			for (i = 0; i < 7; i++) //������� ������
			{
				if (colision(iPriz[i], jPriz[i], iHero, jHero)) {
					pole[iPriz[i]][jPriz[i]] = 0; //
					x = x0 + jPriz[i] * h; // �������������� ������ ������� � �������� ����������  X. ����� �������� ������ ���� ������. 
					y = y0 + iPriz[i] * L;
					brick(x, y, Black);
						load_hero(x, y);
					iPriz[i] = 0; //� ������� ������� ���� �������
					jPriz[i] = 0;
					count++; //������� ����� (�����������)
					counter(count, 80, 120); //������������ ����
				}
			}
		} while ((life > 0) && (pole[iHero][jHero] != 5) &&(key !=ESC)); //���� ������ ������ 0, ���� �� ����� ��� ���� �� ������ ������� esc
		if (pole[iHero][jHero] == 5) {
			level++;
			cleardevice(); //�������� ����� ����
			if (level > 2)
			{
				getch();
			}
		}
		cleardevice();
	} while (level <= 2 &&(key !=ESC));
	cleardevice();
	getch();
}

void help() {
	cleardevice();
	outtextxy(20, 50, "         ���� ����:"); 
	outtextxy(30, 100, "������ ��� �����"); 
	outtextxy(30, 150, "� �� ���� ������"); 
	outtextxy(30, 200, "�������� ����!"); 
	getch();
}
int menu(int &num) {
	cleardevice();
	int x = 500, ym = 100, y, dx = 50;
	char key = 0;
	setcolor(LightGreen);
	settextstyle(1, 0, 2);
	outtextxy(x, ym, "GAME"); // ����� ������
	outtextxy(x, ym + 50, "HELP"); // ����� ������
	outtextxy(x, ym + 100, "EXIT"); // ����� ������
	num = 1;
	y = ym + r + (num - 1)*dx;
	ball(x - 50, y, Yellow);
	do {
		key = getch();
		if (key == 0) {
			key = getch();
		}
		ball(x - 50, y, Black);
		switch (key) {
		case 'w':
		case '�':
		case UP: if (num > 1) {
			num = num - 1;
		}
				 else {
					 num = 3;
				 }
				 break;
		case 's':
		case '�':
		case DOWN: if (num < 3) {
			num = num + 1;
		}
				   else {
					   num = 1;
				   }
				   break;
		}
		y = ym + r + (num - 1)*dx;
		ball(x - 50, y, Yellow);
	} while (key != ENTER);
	return num;
}

int main() 
{
	initwindow(MaxX, MaxY, "Battle of Mobile");
	zastavka();
	getch();
	int num = 0;
	do {
		num = menu(num);
		switch (num) {
		case 1: game(); break;
		case 2: help(); break;
		}
	} while (num != 3);
	return 0;
}