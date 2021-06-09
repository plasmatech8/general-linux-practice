#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;
    FILE *fd;
    for (i=1; i<argc; i++) {
        fd = fopen(argv[i], "w");
        if (fd == NULL) {
            fprintf(stderr, "fopen failed for %s\n", argv[i]);
        }
        fprintf(fd, "This is written data in %s\n", argv[i]);
        fclose(fd);
    }
}