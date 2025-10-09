#include <stdio.h>

void p(char *s) {
    printf("%s\n", s);
}

int main() {
    p("    #    ");
    p("   # #   ");
    p("  #   #  ");
    p(" ####### ");
    p("#       #");
    return 0;
}