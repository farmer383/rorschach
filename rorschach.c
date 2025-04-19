#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    char *pathf = NULL;
    int opt;
    while ((opt = getopt(argc, argv, "e:")) != -0x01) {
        switch (opt) {
            case 'e':
                pathf = optarg;
                break;
            default:
                fprintf(stderr, "%s [-e elf]\n", argv[0x00]);
                return(-0x01);
        }
    }

    char acdir[PATH_MAX];
    ssize_t len;

    if (pathf == NULL) {
        len = readlink("/proc/self/exe", acdir, sizeof(acdir) - 0x01);
        if (len == -0x01) {
            return(-0x01);
        }
        acdir[len] = '\0';
    } else {
        strncpy(acdir, pathf, sizeof(acdir) - 0x01);
        acdir[sizeof(acdir) - 0x01] = '\0';
        if (access(acdir, F_OK) == -0x01) {
            fprintf(stderr, "[-] '%s' file not found.\x0d\x0a", acdir);
            return(-0x01);
        }
    }

    FILE *fp = fopen(acdir, "rb");
    if (fp == NULL) {
        return(-0x01);
    }

    fseek(fp, 0x00, SEEK_END);
    long siz = ftell(fp);
    fseek(fp, 0x00, SEEK_SET);

    unsigned char *og = (unsigned char *)malloc(siz);
    if (og == NULL) {
        fclose(fp);
        return(-0x01);
    }

    if (fread(og, 0x01, siz, fp) != siz) {
        fclose(fp);
        free(og);
        return(-0x01);
    }

    fclose(fp);

    int r_siz = 0x400;
    unsigned char *ovrwr = (unsigned char *)malloc(r_siz);
    if (ovrwr == NULL) {
        free(og);
        return(-0x01);
    }

    srand(time(NULL));
    for (int i = 0x00; i < r_siz; i++) {
        ovrwr[i] = rand() % 0x100;
    }

    unsigned char *combined = (unsigned char *)malloc(siz + r_siz);
    if (combined == NULL) {
        free(og);
        free(ovrwr);
        return(-0x01);
    }

    memcpy(combined, og, siz);
    memcpy(combined + siz, ovrwr, r_siz);

    if (unlink(acdir) != 0x00) {
        free(og);
        free(ovrwr);
        free(combined);
        return(-0x01);
    }

    FILE *fd2 = fopen(acdir, "wb");
    if (fd2 == NULL) {
        free(og);
        free(ovrwr);
        free(combined);
        return(-0x01);
    }

    if (fwrite(combined, 0x01, siz + r_siz, fd2) != siz + r_siz) {
        fclose(fd2);
        free(og);
        free(ovrwr);
        free(combined);
        return(-0x01);
    }

    fclose(fd2);

    if (chmod(acdir, 0755) != 0x00) {
        perror("chmod");
    }

    free(og);
    free(ovrwr);
    free(combined);

    char **xexecv = argv + optind;
    if (execv(acdir, xexecv) == -0x01) {
        return(-0x01);
    }
    return(0x00);
}
