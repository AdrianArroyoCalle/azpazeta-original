/*#include <stdio.h>
#include <unistd.h>
#include <windows.h>

int main(){
printf("\007");
Beep(587,500);

return 0;
}*/


#include <stdio.h>
#include <unistd.h>
#include <curses.h>
#if !(WIN32)
#define beep(x,y)
#endif

int main()
{

    puts("using winAPI Beep(frequency_hrz, duration_ms)...");
  beep(523,5000);  /* 523 hertz (C5) for 500 milliseconds*/
  beep(587,5000);
  beep(659,5000);
  beep(698,5000);
  beep(784,5000);
  usleep(500000);    
  puts("\n\\a makes a beep on the internal speaker too ...");
  usleep(500000);
  puts("\a");
  usleep(500000);
  puts("\a");
  
  getchar(); 
  return 0;
}
