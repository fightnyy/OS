
/**********************************************************************
 * Copyright (c) 2020
 *  Sang-Hoon Kim <sanghoonkim@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

/* Suppress security errors on Visual Studio */
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

#define MAX_NR_TOKENS 32 /* Maximum number of tokens in a command */
#define MAX_TOKEN_LEN 64 /* Maximum length of single token */
#define MAX_COMMAND 256  /* Maximum length of command string */

typedef unsigned char bool;
#define true 1
#define false 0

/***********************************************************************
 * parse_command
 *
 * DESCRIPTION
 *    Parse @command, put each command token into @tokens[], and
 *    set @nr_tokens with the number of tokens.
 *
 * A command token is defined as a string without any whitespace (i.e., *space*
 * and *tab* in this programming assignment). Suppose @command as follow;
 *
 *   @command = "  Hello world   Ajou   University!!  "
 *
 * Then, @nr_tokens = 4 and @tokens should be
 *
 *   tokens[0] = "Hello"
 *   tokens[1] = "world"
 *   tokens[2] = "Ajou"
 *   tokens[3] = "University!!"
 *
 * Another exmaple is;
 *   command = "ls  -al   /home/operating_system /hw0  "
 *
 * then, nr_tokens = 4, and tokens is
 *   tokens[0] = "ls"
 *   tokens[1] = "-al"
 *   tokens[2] = "/home/operating_system"
 *   tokens[3] = "/hw0"
 *
 *
 * RETURN VALUE
 *    Return 0 after filling in @nr_tokens and @tokens[] properly
 *
 */

char *slice(const char *input, int start, int end)
{
    int length = end - start;
    char *dst = (char *)malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++)
        dst[i] = input[i + start];
    dst[length] = '\0';

    return dst;
}
static int parse_command(const char *command, int *nr_tokens, char *tokens[])
{
    int count=0;
    int start = -1;
    int i;
    for (i = 0; command[i] != '\0'; i++)
    {
        if (isspace(command[i]))
        {
            if (start != -1)
            {
                tokens[count++] = slice(command, start, i);
                start = -1;
            }
        }
        else if (start == -1)
            start = i;
    }
    if (start != -1)
        tokens[count++] = slice(command, start, i);
    *nr_tokens=count;
    

    return 0;
}

/***********************************************************************
 * The main function of this program.
 * SHOULD NOT CHANGE THE CODE BELOW THIS LINE
 */
int main(int argc, char *argv[])
{
    char line[MAX_COMMAND] = {'\0'};
    FILE *input = stdin;

    if (argc == 2)
    {
        input = fopen(argv[1], "r");
        if (!input)
        {
            fprintf(stderr, "No input file %s\n", argv[1]);
            return -EINVAL;
        }
    }

    while (fgets(line, sizeof(line), input))
    {
        char *tokens[MAX_NR_TOKENS] = {NULL};
        int nr_tokens = 0;

        parse_command(line, &nr_tokens, tokens);

        fprintf(stderr, "nr_tokens = %d\n", nr_tokens);
        for (int i = 0; i < nr_tokens; i++)
        {
            fprintf(stderr, "tokens[%d] = %s\n", i, tokens[i]);
        }
        printf("\n");
    }

    if (input != stdin)
        fclose(input);
    return 0;
}
