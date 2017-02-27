#include <curses.h>
int main() {
  initscr();
  box(stdscr, ACS_VLINE, ACS_HLINE);
  move(LINES/2, COLS/2);
  waddstr(stdscr,"Hello, world!");
  refresh();
  getch();
  endwin();
  return 0;
}
