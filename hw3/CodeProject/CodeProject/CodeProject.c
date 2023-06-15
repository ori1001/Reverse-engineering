#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MY_LEN 1000

int main2()
{
    char inp[MY_LEN];
    FILE *fptr = fopen("input.txt", "r");
    int i = 0;
    char c;
    do
    {
        c = getc(fptr);
        inp[i++] = c;
    } while (c != EOF);
    inp[i] = EOF;
    fclose(fptr);
    i = 0;
    while (inp[i] != EOF)
    {
        if (inp[i] == '\n')
        {
            printf("\n");
            i++;
        }
        else
        {
            int int_let = 0;
            for (int j = 0; j < 2; j++)
            {
                if (inp[i + 1] == '+')
                {
                    int_let += inp[i] - '0' + inp[i + 2] - '0';
                    i += 3;
                }
                else if (inp[i + 1] == '-')
                {
                    i += 3;
                }
                else if (inp[i] >= '2' && inp[i] <= '9')
                {
                    int_let += inp[i] - '0';
                    i++;
                }
                else
                {
                    switch (inp[i])
                    {
                    case 'A':
                        int_let += 1;
                        break;
                    case 'J':
                        int_let += 10;
                        break;
                    case 'Q':
                        int_let += 11;
                        break;
                    case 'K':
                        int_let += 12;
                        break;
                    default:
                        int_let += inp[i];
                    }
                    i++;
                }
                if (j == 0) {
                    int_let = int_let << 4;
                }
            }
            printf("%c", int_let);
        }
    }
}