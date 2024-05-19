/*
This utility patches MajorOperatingSystemVersion and MajorSubsystemVersion
headers of EXE files to 0x05 to make them run on NT 5.0

The release file got build using TDM-GCC64 10.3.0 and this command:
gcc -m32 -O2 -s -o patcher.exe patcher.c
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <ctype.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define MOSV_OFFSET 0x40 /* MajorOperatingSystemVersion */
#define MSV_OFFSET 0x48 /* MajorSubsystemVersion */
#define NT5_MAJOR 0x5 /* NT 5.0 (W2K) */
#define GAME_NAME_BUF 16
#define GAMES_COUNT 4

const char GAMES[GAMES_COUNT][GAME_NAME_BUF] = {"th17.exe", "th18.exe", "th185.exe", "custom.exe"};

bool choice() {
    char in = tolower(getch());
    if (in == 'y') {
        return true;
    }
    return false;
}

void loudExit(int code) {
    printf("Press any key to exit...\n");
    getch();
    exit(code);
}

void patchGame(const char *gameName) {
    FILE *fp;
    int pe_offset = 0;
    char readBuf[3];

    /* Get full file path */
    char fullFilePath[MAX_PATH];
    GetFullPathName(gameName, MAX_PATH, fullFilePath, NULL);
    
    /* Open the file */
    fp = fopen(fullFilePath, "rb+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
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

    /* Close the file  */
    fclose(fp);
}

int main(int argc, char **argv) {
    printf("Welcome to TouhouXP!\n\n");

    /* Find games */
    printf("Found games: ");
    char foundGames[GAMES_COUNT][GAME_NAME_BUF];
    int foundGamesCount = 0;
    for (int i = 0; i < GAMES_COUNT; i++) {
        if (_access(GAMES[i], 0) == 0) {
            printf("%s ", GAMES[i]);
            strncpy(foundGames[foundGamesCount], GAMES[i], GAME_NAME_BUF);
            foundGamesCount++;
        }
    }

    if (foundGamesCount == 0) {
        printf("\rCouldn't find any games. Exitting...\n"); /* Overrides the "Found games" line */
        loudExit(-1);
    }

    printf("\nPatch all of them? (y/n)\n");
    if (!choice()) {
        printf("Exitting...\n");
        loudExit(1);
    }

    printf("!!! IF IT TAKES MORE THAN 10 SECONDS TO PATCH A FILE, RESTART THE PATCHER !!!\n");

    /* Patch */
    for (int i = 0; i < foundGamesCount; i++) {
        printf("Patching %s\n", foundGames[i]);
        patchGame(foundGames[i]);
    }
    printf("All patched!\n");

    loudExit(0);
}
