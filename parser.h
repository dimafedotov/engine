#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>

#define PARSER_ERROR 1

int
parse(char *name)
{
    FILE *fp;

    fp = fopen(name, "r");
    if (!fp)
    {
        printf("Can't read script\n");
        return 1;
    }

    char c;

    while((c = getc(fp)) != EOF)
    {
        printf("%c", c);
    }

    fclose(fp);

    printf("\n");

    return 0;
}

#endif // PARSER_H_
