#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXBUF 5000

//CAT ASCII art images found on https://www.asciiart.eu/animals/cats
//credit/signatures left in image originally containing them

void print_loop(char, int);

int main(int argc, char *argv[])
{
    srand(time(0));
    char catname[9] = {'c', 'a', 't', 0, '.', 't', 'x', 't', '\0' };
    //
    if(argc == 3 && argv[1][1] == 'w')
        catname[3] = argv[2][0];
    else
    {
        if(argc > 1)
            fprintf(stderr, "unknown option: %s\n", argv[1]);
        catname[3] = (rand()%3 + 1) + '0'; // A = 1, B = 3
    }
    FILE *fp = fopen(catname, "rb");

    char buf[MAXBUF] = {};
    int c, col = 0, max_col = 0, i = 0, tabcnt = 0;

    while( (c = getchar()) != EOF)
    {
        buf[i] = c;
        if(c == '\t') { col = ((col + 8) / 8 * 8); tabcnt++; }
        if(c == '\n') { max_col = col > max_col ? col : max_col; col = 0;}
        col++; i++;
    }
    buf[i+1] = '\0';
    max_col+= 2;
        
    /*printf("There are %i tabs in the buffer\nmax_col = %i\n...\n\n",tabcnt, max_col);
    for(int i = 0; buf[i] != '\0'; ++i)
    {
        printf("%0x ", buf[i]);
        if(i%9 == 0)
            putchar('\n');
    }
    putchar('\n');*/

    putchar(' '); print_loop('_', max_col); putchar(' ');
    printf("\n/"); print_loop(' ', max_col); printf("\\\n| ");
    i = 0; col = 0, tabcnt = 0;
    int lineno = 0, tabline = -1;

    while(1)
    {
        if(buf[i] == '\t')
        {   
            tabcnt++;
            tabline = lineno;
            col = ((col + 8) / 8 * 8);
        }
        if((buf[i] == '\n' && (max_col > col)) || (buf[i+1] == '\0'))
        {
            if(tabline == lineno)
                print_loop(' ', max_col - col + 2);
            else if(lineno == 0)
                print_loop(' ', max_col - col - 1);
            else
                print_loop(' ', max_col - col);
            putchar('|');
            putchar(buf[i]);
            if(buf[i+1] == '\0') break;
            printf("| ");
            col = 0;
            lineno++;
        }
        else putchar(buf[i]);
        i++; col++;
    }
    putchar('\\'); print_loop('_', max_col); printf("/\n");

    while( (c = fgetc(fp)) != EOF) putchar(c);
    putchar('\n');
    fclose(fp);
    return 0;
}

void print_loop(char c, int cnt)
{
    if(cnt > 0)
    {
        putchar(c);
        cnt--;
        print_loop(c, cnt);
    }
    else return;
}
