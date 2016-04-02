/*
 *  terminal_io.h
 *  Author: Jakash3
 *  Date: 22 Dec 2011
 *  Some conio.h functions for GNU/Linux
 *
 *  Original source : https://jakash3.wordpress.com/2011/12/23/conio-h-for-linux/
 */
#ifndef CONIO_LINUX_H_
#define CONIO_LINUX_H_
 
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

namespace cpp_factory {
// Turns terminal line buffering on or off
    void terminal_lnbuf(int yn);

// Turns terminal keyboard echo on or off
    void terminal_echo(int yn);

// Get next immediate character input (no echo)
    int getch();

// Get next immediate character input (with echo)
    int getche();

// Check if a key has been pressed at terminal
    int kbhit();

// Set cursor position
    void gotoxy(int x, int y);

// Clear terminal screen and set cursor to top left
    void clrscr();

}
#endif