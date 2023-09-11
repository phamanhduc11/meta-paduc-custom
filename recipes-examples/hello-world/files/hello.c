#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
// #include "mystatic.h"
// #include "mydynamic.h"

int main() {
    printf("Hello world from Duc\n");
    // myprint("Hello from mystatic\n");
    // myprint_dynamic("Hello from dynamic\n");

    int fb_fd = 0;
    int abc = 0xaa;
    fb_fd = open("/dev/fb0", O_RDWR);
    if (fb_fd == -1) {
        perror("Không thể mở framebuffer device");
        exit(EXIT_FAILURE);
    }

    printf("[FromUserSpace] data address=%p\n", &abc);
    write(fb_fd, &abc, 1);
    printf("[FromUserSpace] Done\n", &abc);
    close(fb_fd);
    return 0;
}