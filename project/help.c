#include <stdlib.h>
#include <stdio.h>

// Polecenie wypisujące pomoc z informacją o dostępnych poleceniach
int main(int argc, const char* argv[]) {
    puts("  help - show this help list\n"                              \
         "  sum x [y z ...] - sum 2 (or more) numbers\n"               \
         "  counter x - countdown from x to 0\n"                       \
         "  remainder x y - show result of x % y \n"                   \
         "  rectangle x y - print rectangle (x - high, y - width)\n"   \
         "  echo sth - print text sth\n"                               \
         "  ctrl+C - show commands history\n"                          \
         "  exit - exit the interpreter"                               \
);      
         
    return 0;
}