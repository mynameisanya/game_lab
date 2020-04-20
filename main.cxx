#include "graphics.h"
#include "string.h"

#define _CRT_SECURE_NO_WARNINGS

#define MaxX 1280 // максимальное по X 
#define MaxY 720 // максимальное по Y

#define h 60 // размер клетки лабиринта, высота
#define L 60 // размер клетки лабиринта, длина
#define n 10 // размер лабиринта, количество строк и столбцов 
#define r 12 // радиус шарика (колобка)
#define x0 50 // точка начало поля лабиринта
#define y0 50 // точка начало поля лабиринта

#define ESC 27 // клавиша отмена

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
		strnset(s, word[i], 1); //копирует в переменную s одну букву
		s[1] = '\0';
		setcolor(Red);
		settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3); // стиль текста
		y = 500;
		outtextxy(x, y, s); //вывод текста
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
	char *autor[3] = { "Выполнила: Янпольская Анна", "группа 803 са1", "Преподаватель:Голкова Н.В." };
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
	sprintf(s, "%d", k); // функция преобразует число k в строку s
	setfillstyle(1, Black);  // чёрный цвет
	bar(MaxX - x, 30, MaxY - y, 50); // рисуем чёрный прямоугольник поверх числа
	setcolor(White); // белый цвет
	settextstyle(1, 0, 2); // стиль текста
	outtextxy(MaxX - x, y, s); // выводим число
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

int colision(int iBot, int jBot, int iHero, int jHero) { // Здесь все переменные – формальные параметры
	if ((iBot == iHero) && (jBot == jHero)) {
		return 1;
	}
	else {
		return 0;
	}
}

void moveBot(int &i, int &j, int pole[n][n]) { //Здесь i и j индексы клетки
	int x, y, ran;
	delay(100); //пауза 
	x = x0 + j*h;
	y = y0 + i*L;
	
	
	brick(x, y, Black);
	ran = rand() % 4 + 1;
	switch (ran) {
	case 1: if ((j < n - 1) && (pole[i][j + 1] == 0)) j++; break; //Вправо
	case 2: if ((i > 0) && (pole[i - 1][j] == 0))  i--; break; // Вверх
	case 3: if ((j > 0) && (pole[i][j - 1] == 0)) j--; break; //Влево
	case 4: if ((i < n - 1) && (pole[i + 1][j] == 0)) i++; break; // Вниз
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
	case 'a': if ((j > 0) && (pole[i][j - 1] != 1)) { j--; } break; // если нет стены или не край карты слева, то меняем положение (влево)
	case RIGHT:
	case 'd': if ((j < n - 1) && (pole[i][j + 1] != 1)) { j++; } break; // n=9 другая сторона карты
	case UP:
	case 'w': if ((i > 0) && (pole[i - 1][j] != 1)) { i--; } break;
	case DOWN:
	case 's': if ((i < n - 1) && (pole[i + 1][j] != 1)) { i++; } break;
	}
	x = x0 + j*h;
	y = y0 + i*L;
	load_hero(x, y);
	while (kbhit()) { getch(); } // цикл очистки буфера
}


void game() {
	cleardevice();
	FILE *f;
	int level = 1; //всегда начинаем с 1 уровня
	int pole[n][n], i, j, iHero, jHero, k, t;
	int iBot[3], jBot[3], iPriz[7], jPriz[7]; // массивы номеров клеток Ботов и Призов
	int x, y; // экранные координаты
	char key = 0;
	do {
		switch (level) {
		case 1: f = fopen("map1.txt", "r"); break; // загружаем файл
		case 2: f = fopen("map2.txt", "r"); break;
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				fscanf(f, "%d", &pole[i][j]); //считываем файл в поле (fscanf - считывает с файла)
			}
		}
		fclose(f); //закрываем файл
		int count = 0;
		int k = 0, t = 0; //счетчик количества врагов, t для количества призов
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				x = x0 + j*h; // преобразование номера столбца в экранную координату  X. Точка верхнего легого угла клетки. 
				// х0 у0 отвечает за отступ от левого верхнего угла при отрисовки h и l это масштаб блоков пикселей
				y = y0 + i*L; // преобразование номера строки в экранную координату Y. Точка верхнего легого угла клетки. 
				switch (pole[i][j]) {
				case 1: 
					
					brick(x, y, DarkGray); break; //рисует темно серый квадрат
				case 2: 
					load_hero(x, y);
					iHero = i;    //  Запоминаем координаты героя
					jHero = j;
					pole[i][j] = 0;
					break;
				case 3: //если в клетке массива стоит 3, значит это враг
					//ball(x + r, y + r, LightBlue); //отрисовка синего круга (враг)
					load_zlo(x, y);
					iBot[k] = i;
					jBot[k] = j;
					k++; //считаем колво врагов
					pole[i][j] = 0;
					break;
				case 4: // Призы
					load_priz(x, y);
					iPriz[t] = i;
					jPriz[t] = j;
					t++;
					break;
				case 5: // Дверь
					brick(x, y, Brown);break;
				} // switch
			}  // for
		}
		int p = 0;
		int life = 3;
		setcolor(White);
		settextstyle(1, 0, 2);
		outtextxy(MaxX - 130, 10, "Жизни: ");
		outtextxy(MaxX - 130, MaxY - 920, "Счёт: ");// выводим текст Счёт:
		counter(life, 80, 40);
		counter(count, 80, 120);
		do {
			for (int i = 0; i < 3; i++) {  // передвигаем врагов по очереди
				moveBot(iBot[i], jBot[i], pole);
			}
			if (kbhit()) {
				key = getch(); //если клавиша была нажата, то двигаем колобка
				if (key == NULL) {
					key = getch();
				}
				moveKolobok(iHero, jHero, pole, key); // передвигаем героя
			}
			k = 0;
			for (i = 0; i < 3; i++)
			{
				if (colision(iBot[i], jBot[i], iHero, jHero)) {
			life--; //если координаты колобка и врага совпали, то значит произошло столкновение и отнимаем жизнь
					counter(life, 80, 40); //перерисовка счета
					x = x0 + jHero*h; // преобразование номера столбца в экранную координату  X. Точка верхнего легого угла клетки. 
					y = y0 + iHero*L;
					 // если герой столкнулся, то стираем героя
					
					
					brick(x, y, Black);
					iHero = 3;
					jHero = 0; //возвращаем на начальную позицию
					x = x0 + jHero*h; // преобразование номера столбца в экранную координату  X. Точка верхнего легого угла клетки. 
					y = y0 + iHero*L;
					load_hero(x, y); //перерисовываем
				}
			}
			for (i = 0; i < 7; i++) //перебор призов
			{
				if (colision(iPriz[i], jPriz[i], iHero, jHero)) {
					pole[iPriz[i]][jPriz[i]] = 0; //
					x = x0 + jPriz[i] * h; // преобразование номера столбца в экранную координату  X. Точка верхнего легого угла клетки. 
					y = y0 + iPriz[i] * L;
					brick(x, y, Black);
						load_hero(x, y);
					iPriz[i] = 0; //в массиве текущий приз стираем
					jPriz[i] = 0;
					count++; //счетчик очков (увеличиваем)
					counter(count, 80, 120); //перерисовать очки
				}
			}
		} while ((life > 0) && (pole[iHero][jHero] != 5) &&(key !=ESC)); //если жизней больше 0, пока не выход или пока не нажата клавиша esc
		if (pole[iHero][jHero] == 5) {
			level++;
			cleardevice(); //очищение всего поля
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
	outtextxy(20, 50, "         ЦЕЛЬ ИГРЫ:"); 
	outtextxy(30, 100, "СЪЕСТЬ ВСЮ ПИЦЦУ"); 
	outtextxy(30, 150, "И НЕ БЫТЬ УБИТОЙ"); 
	outtextxy(30, 200, "ПРИЯТНОЙ ИГРЫ!"); 
	getch();
}
int menu(int &num) {
	cleardevice();
	int x = 500, ym = 100, y, dx = 50;
	char key = 0;
	setcolor(LightGreen);
	settextstyle(1, 0, 2);
	outtextxy(x, ym, "GAME"); // вывод текста
	outtextxy(x, ym + 50, "HELP"); // вывод текста
	outtextxy(x, ym + 100, "EXIT"); // вывод текста
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
		case 'ц':
		case UP: if (num > 1) {
			num = num - 1;
		}
				 else {
					 num = 3;
				 }
				 break;
		case 's':
		case 'ы':
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