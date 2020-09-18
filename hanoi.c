#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <stdarg.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_a 97
#define KEY_b 98
#define KEY_c 99

WINDOW *w_frame = NULL;
int arra[10], sizea=0;
int arrb[10], sizeb=0;
int arrc[10], sizec=0;
int lift_a = 0;
int lift_b = 0;
int lift_c = 0;
int total_line = 0;

int draw_one(int num, int posx, int posy, int len, int color);
int free_game();
int down_to(int flag);
int lift_top(int flag);
int init_game();
int draw_all();
int init_interface();

int main()
{
	int key = 0;
	int flag = 0;
	int ret = 0;


	init_game();

	for(total_line=1; total_line<=10; total_line++) {
		init_interface();

		while(1) {
			draw_all();

			if(sizec==total_line) {
				mvwaddstr(w_frame, 8, COLS/2-21, "        Press Enter to Next Level!        ");
				wrefresh(w_frame);
				getch();
				break;
			}

			do{
				key = wgetch(w_frame);
			} while(key!=KEY_A && key!=KEY_B && key!=KEY_C && key!=KEY_a && key!=KEY_b && key!=KEY_c);

			switch(key) {
				case KEY_A:
				case KEY_a:
					if(flag==0) {
						ret = lift_top(1);
						if(ret==0) flag = 1;
					} else {
						ret = down_to(1);
						if(ret==0) flag = 0;
					}
					break;
				case KEY_B:
				case KEY_b:
					if(flag==0) {
						ret = lift_top(2);
						if(ret==0) flag = 1;
					} else {
						ret = down_to(2);
						if(ret==0) flag = 0;
					}
					break;
				case KEY_C:
				case KEY_c:
					if(flag==0) {
						ret = lift_top(3);
						if(ret==0) flag = 1;
					} else {
						ret = down_to(3);
						if(ret==0) flag = 0;
					}
					break;
				default : break;
			}
		}
	}

	free_game();
	return 0;
}

int init_game()
{
	int i = 0;

	initscr();
	curs_set(0);
	noecho();
	refresh();

	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
	init_pair(4, COLOR_BLACK, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_BLUE);
	init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(7, COLOR_BLACK, COLOR_CYAN);
	init_pair(8, COLOR_WHITE, COLOR_RED);
	init_pair(9, COLOR_WHITE, COLOR_GREEN);
	init_pair(10, COLOR_WHITE, COLOR_YELLOW);

	w_frame = newwin(LINES, COLS, 0, 0);
	keypad(w_frame, TRUE);
	wrefresh(w_frame);

	return 0;
}

int init_interface()
{ 
	int i = 0;

	for(i=0; i<total_line; i++) {
		arra[i] = i+1; 
		arrb[i] = 0;
		arrc[i] = 0;
	}

	sizea = total_line;
	sizeb = 0;
	sizec = 0;

	return 0;
}

int free_game()
{
	delwin(w_frame);
	endwin();
	return 0;
}

int draw_all()
{
	int i = 0;
	werase(w_frame);
	box(w_frame, 0, 0);

	mvwaddstr(w_frame, 2, COLS/2-18, "##  ##                          ##");
	mvwaddstr(w_frame, 3, COLS/2-18, "##  ##   ####   ######  ######    ");
	mvwaddstr(w_frame, 4, COLS/2-18, "######  ## ##   ##  ##  ##  ##  ##");
	mvwaddstr(w_frame, 5, COLS/2-18, "##  ##  ## ##   ##  ##  ##  ##  ##");
	mvwaddstr(w_frame, 6, COLS/2-18, "##  ##   #####  ##  ##  ######  ##");

	mvwaddstr(w_frame, 8, COLS/2-21, "       A-->C, Press A/B/C to move!        ");

	for(i=3; i<54; i++) mvwaddch(w_frame, LINES/2+15, i, ACS_HLINE);
	for(i=58; i<109; i++) mvwaddch(w_frame, LINES/2+15, i, ACS_HLINE);
	for(i=113; i<164; i++) mvwaddch(w_frame, LINES/2+15, i, ACS_HLINE);

	mvwaddstr(w_frame, LINES/2+17, 3+25-3, "  **  ");
	mvwaddstr(w_frame, LINES/2+18, 3+25-3, " *  * ");
	mvwaddstr(w_frame, LINES/2+19, 3+25-3, "*    *");
	mvwaddstr(w_frame, LINES/2+20, 3+25-3, "******");
	mvwaddstr(w_frame, LINES/2+21, 3+25-3, "*    *");
	mvwaddstr(w_frame, LINES/2+22, 3+25-3, "*    *");

	mvwaddstr(w_frame, LINES/2+17, 3+25*3+5-3, "***** ");
	mvwaddstr(w_frame, LINES/2+18, 3+25*3+5-3, "*    *");
	mvwaddstr(w_frame, LINES/2+19, 3+25*3+5-3, "***** ");
	mvwaddstr(w_frame, LINES/2+20, 3+25*3+5-3, "*    *");
	mvwaddstr(w_frame, LINES/2+21, 3+25*3+5-3, "*    *");
	mvwaddstr(w_frame, LINES/2+22, 3+25*3+5-3, "***** ");

	mvwaddstr(w_frame, LINES/2+17, 3+25*5+5*2-3, "  ****");
	mvwaddstr(w_frame, LINES/2+18, 3+25*5+5*2-3, " *    ");
	mvwaddstr(w_frame, LINES/2+19, 3+25*5+5*2-3, "*     ");
	mvwaddstr(w_frame, LINES/2+20, 3+25*5+5*2-3, "*     ");
	mvwaddstr(w_frame, LINES/2+21, 3+25*5+5*2-3, " *    ");
	mvwaddstr(w_frame, LINES/2+22, 3+25*5+5*2-3, "  ****");

	for(i=LINES/2-10; i<LINES/2+15; i++) mvwaddch(w_frame, i, 3+25, ACS_VLINE);
	for(i=LINES/2-10; i<LINES/2+15; i++) mvwaddch(w_frame, i, 3+25*3+5, ACS_VLINE);
	for(i=LINES/2-10; i<LINES/2+15; i++) mvwaddch(w_frame, i, 3+25*5+5*2, ACS_VLINE);

	for(i=0; i<sizea&&arra[i]!=0; i++) draw_one(arra[i], 3+25-2*arra[i], LINES/2+15-2*(sizea-i), 2*2*arra[i]+1, arra[i]);
	for(i=0; i<sizeb&&arrb[i]!=0; i++) draw_one(arrb[i], 3+25*3+5-2*arrb[i], LINES/2+15-2*(sizeb-i), 2*2*arrb[i]+1, arrb[i]);
	for(i=0; i<sizec&&arrc[i]!=0; i++) draw_one(arrc[i], 3+25*5+5*2-2*arrc[i], LINES/2+15-2*(sizec-i), 2*2*arrc[i]+1, arrc[i]);

	if(lift_a!=0) draw_one(lift_a, 3+25-2*lift_a, LINES/2-10-4, 2*2*lift_a+1, lift_a);
	if(lift_b!=0) draw_one(lift_b, 3+25*3+5-2*lift_b, LINES/2-10-4, 2*2*lift_b+1, lift_b);
	if(lift_c!=0) draw_one(lift_c, 3+25*5+5*2-2*lift_c, LINES/2-10-4, 2*2*lift_c+1, lift_c);

	wrefresh(w_frame);

	return 0;
}


int draw_one(int num, int posx, int posy, int len, int color)
{
	int i = 0;
	char str[1024+1] = {0};

	wattron(w_frame, COLOR_PAIR(color));

	for(i=0; i<len; i++) strcat(str, " ");
	mvwaddstr(w_frame, posy, posx, str);

	sprintf(str, " %d", num);
	for(i=(num<10?2:3); i<len; i++) strcat(str, " ");
	mvwaddstr(w_frame, posy+1, posx, str);

	wattroff(w_frame, COLOR_PAIR(color));

	return 0;
}

int lift_top(int flag)
{
	int i = 0;

	if(flag==1) {
		if(arra[0]==0) return -1; 
		lift_a = arra[0];
		lift_b = 0;
		lift_c = 0;

		arra[0] = 0;
		for(i=1; i<total_line; i++) {
			arra[i-1] = arra[i]; 
			arra[i] = 0;
		}
		if(sizea>0) sizea--;
	} else if(flag==2) {
		if(arrb[0]==0) return -1; 
		lift_a = 0;
		lift_b = arrb[0];
		lift_c = 0;
		arrb[0] = 0;
		for(i=1; i<total_line; i++) {
			arrb[i-1] = arrb[i]; 
			arrb[i] = 0;
		}
		if(sizeb>0) sizeb--;

	} else {
		if(arrc[0]==0) return -1; 
		lift_a = 0;
		lift_b = 0;
		lift_c = arrc[0];
		arrc[0] = 0;
		for(i=1; i<total_line; i++) {
			arrc[i-1] = arrc[i]; 
			arrc[i] = 0;
		}
		if(sizec>0) sizec--;
	}

	return 0;
}

int down_to(int flag)
{
	int lift = (lift_a==0?(lift_b==0?lift_c:lift_b):lift_a);
	int i = 0;

	if(flag==1) {
		if(arra[0]!=0 && lift>arra[0]) return -1;

		for(i=sizea-1; i>=0; i--) arra[i+1] = arra[i];
		arra[0] = lift;
		lift_a = 0;
		lift_b = 0;
		lift_c = 0;
		sizea++;
	} else if(flag==2) {
		if(arrb[0]!=0 && lift>arrb[0]) return -1;

		for(i=sizeb-1; i>=0; i--) arrb[i+1] = arrb[i];
		arrb[0] = lift;
		lift_a = 0;
		lift_b = 0;
		lift_c = 0;
		sizeb++;
	} else {
		if(arrc[0]!=0 && lift>arrc[0]) return -1;

		for(i=sizec-1; i>=0; i--) arrc[i+1] = arrc[i];
		arrc[0] = lift;
		lift_a = 0;
		lift_b = 0;
		lift_c = 0;
		sizec++;
	}
	return 0;
}
