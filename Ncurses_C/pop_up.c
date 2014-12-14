#include <ncurses.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int ch, y, x;
	WINDOW *win;

	initscr();
	cbreak();
	noecho();
	nonl();

	win = newwin(4, 30, LINES/2-3, COLS/2-15);
	box(win, '|', '_');
	mvwaddstr(win, 1, 4, "This is another screen");
	mvwaddstr(win, 2, 2, "Press any key to continue");

	for (y = 1; y < 4-1; y++) {
		for (x = 1; x < 30-1; x++) {
			mvprintw(y+LINES/2-3, x+COLS/2-15, "@");
		}
	}

	while(1) {
		refresh();
		ch = getch();
		switch(ch) {
			case 'q':
				endwin();
				exit(0);
			case '\t':
				touchwin(win);
				wrefresh(win);
				getch();
				touchwin(stdscr);
				break;
			default:
				break;
		}
	}

	return 0;
}
