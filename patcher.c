/*
This utility patches MajorOperatingSystemVersion and MajorSubsystemVersion
headers of EXE files to 0x05 to make them run on NT 5.0

The release file got build using TDM-GCC64 10.3.0 and this command:
gcc -m32 -O2 -s -o patcher.exe patcher.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MOSV_OFFSET 0x40
#define MSV_OFFSET 0x48
#define NT5_MAJOR 0x5

int main(int argc, char **argv) {
    FILE *fp;
    int pe_offset = 0;
    char readBuf[3];

    if (argc != 2) {
        printf("Usage: %s <file_to_patch>\n", argv[0]);
        return 1;
    }
    
    fp = fopen(argv[1], "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    /* Search for the offset of PE header */
    for (int i = 0; pe_offset == 0; i++) {
        fseek(fp, i, SEEK_SET);
        fread(&readBuf, sizeof(char), 2, fp);
        if (strcmp(readBuf, "PE") == 0) {
            pe_offset = i;
        }
    }

    /* Patch MajorOperatingSystemVersion */
    fseek(fp, pe_offset + MOSV_OFFSET, SEEK_SET);
    putc(NT5_MAJOR, fp);

    /* Patch MajorSubsystemVersion */
    fseek(fp, pe_offset + MSV_OFFSET, SEEK_SET);
    putc(NT5_MAJOR, fp);

    /* Close the file and exit */
    fclose(fp);
    return 0;
}
