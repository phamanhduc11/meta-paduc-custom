#include <stdio.h>
#include "mystatic.h"
#include "mydynamic.h"

int main() {
    printf("Hello world from Duc\n");
    myprint("Hello from mystatic\n");
    myprint_dynamic("Hello from dynamic\n");
    return 0;
}