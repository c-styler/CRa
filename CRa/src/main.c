/*
 * main.c
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 */

#include "code.h"
#include "common.h"
#include "debug.h"
#include "scanner.h"
#include "vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void repl();
static void run_file(const char* path);

static VM vm = {0};

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
    }
    else if (argc == 2)
    {
    }

    Scanner scanner = {0};
    scanner_init(&scanner, "struct my_struct;\nreturn true;");
    while (true)
    {
        Token token = scanner_scan_token(&scanner);
        if (token.type == TOKEN_EOF)
        {
            break;
        }

        if (token.type == TOKEN_ERROR)
        {
            printf("Syntax Error: %s\n", token.start);
            break;
        }

        printf("TOKTYPE %d : ", token.type);
        for (int i = 0; i < token.length; i++)
        {
            printf("%c", token.start[i]);
        }
        printf("\n");
    }

    return 0;
}

static void repl()
{
    char line[256];

    while (true)
    {
        printf("> ");
        fgets(line, sizeof(line), stdin);

        line[strlen(line) - 1] = '\0'; // strip the \n

        if (strcmp(line, ".q") == 0)
        {
            break;
        }

        vm_interpret(&vm, line);
    }
}

static void run_file(const char* path)
{
    FILE* fp = fopen(path, "rb");
    if (!fp)
    {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        return;
    }

    fseek(fp, 0L, SEEK_END);
    size_t file_size = ftell(fp);
    rewind(fp);

    char* file_string = malloc(sizeof(char) * (file_size + 1));
    if (file_string == NULL)
    {
        fprintf(stderr, "Not enough memory to read \"%s\"\n", path);
        return;
    }

    size_t characters_read =
        fread(file_string, sizeof(char), file_size, fp);
    file_string[characters_read] = '\0';

    fclose(fp);

    vm_interpret(&vm, file_string);

    free(file_string);
}
