#include <stdlib.h>
#include <stdio.h>


int main(int argc, const char* argv[]) {
    
    puts("  help - show this help list\n"                              \
         "  sum [x y z ...] - sum 2 (or more) numbers\n"               \
         "  counter x - countdown from x to 0\n"
         "  history - show commands history\n"                         \
         "  exit - exit the interpreter");
         
    return 0;
}