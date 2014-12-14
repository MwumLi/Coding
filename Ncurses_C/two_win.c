#include <ncurses.h>
#include <curses.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int ch, y, x, i;
	WINDOW *win[2], *curwin, *helpwin;
	int nowwin;

	initscr();
	cbreak();
	noecho();
	nonl();

	win[0] = newwin(LINES/2-1, COLS-1, 0, 0);
	win[1] = newwin(LINES/2-1, COLS-1, LINES/2, 0);

	helpwin = newwin(3, 30, 2, COLS/2-15);
	box(helpwin, 0, 0);
	mvwaddstr(helpwin, 0, 10, "online help");
	mvwaddstr(helpwin, 1, 4, "Hit any key to continue");

	for (i = 0; i < COLS; i++) {
		mvaddch(LINES/2-1, i, '-');
		nowwin = 0;
		curwin = win[nowwin];
		getyx(curwin, y, x);
		move(0, 0);
		refresh();

		do {
			ch=getch();
			switch(ch) {
				case KEY_UP: --y; /* 判断是否"↑"键被按下 */
							 break;
				case KEY_DOWN: ++y; /* 判断是否"↓"键被按下 */
							   break;
				case KEY_RIGHT: ++x; /* 判断是否"→"键被按下 */
								break;
				case KEY_LEFT: --x; /* 判断是否"←"键被按下 */
							   break;
				case '\r': /* 判断是否 ENTER 键被按下 */
							   ++y;
							   x=0;
							   break;
				case '\t': /* 判断是否 TAB 键被按下 */
							   touchwin(helpwin);
							   wrefresh(helpwin); /* 呼叫 ONLINE HELP */
							   getch();
							   touchwin(win[1-nowwin]); /* 重画第一，二视窗 */
							   wrefresh(win[1-nowwin]);
							   touchwin(curwin);
							   wrefresh(curwin);
							   break;
				case 127:
					 wmove(curwin, y, (--x));
					waddch(curwin, ' ');
							   break;
				case 27 : nowwin=1-nowwin; /* [ESC] 键切换视窗 */
						  curwin=win[nowwin];
						  getyx(curwin, y, x);
					break;
				default:
						waddch(curwin, ch);
						  x++;
						  break;
			}
			wmove(curwin, y, x);
			wrefresh(curwin);
		} while (1);
	}

	return 0;
}
