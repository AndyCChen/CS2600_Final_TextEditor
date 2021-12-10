#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios original_termios;

// terminal

void die(const char *s) 
{
  perror(s);
  exit(1);
}

void disableRawMode()
{
   if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios) == -1)
   {
      die("tcsetattr");
   }
}

void enableRawMode()
{
   if (tcgetattr(STDIN_FILENO, &original_termios) == -1)
   {
      die("tcgetattr");
   }
   atexit(disableRawMode);

   struct termios raw = original_termios;
   raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
   raw.c_oflag &= ~(OPOST);
   raw.c_cflag |= (CS8);
   raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

   raw.c_cc[VMIN] = 0;
   raw.c_cc[VTIME] = 1;

   tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char editorReadKey()
{
   int nread;
   char c;
   while ((nread = read(STDIN_FILENO, &c, 1)) != 1) 
   {
      if (nread == -1 && errno != EAGAIN) die("read");
   }
   return c;
}

// output

void editorRefreshScreen()
{
   write(STDOUT_FILENO, "\x1b[23", 4);
}

// intput

void editorProcessKeypress() 
{
  char c = editorReadKey();

  switch (c) 
  {
    case CTRL_KEY('q'):
      exit(0);
      break;
  }
}

int main()
{
   enableRawMode();

   char c;
   while (1)
   {
      editorRefreshScreen();
      editorProcessKeypress();
   }

   return 0;
}