#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXBUF 5000

//CAT ASCII art images found on https://www.asciiart.eu/animals/cats
//credit/signatures left in images originally containing them

void print_loop(char, int);

int main(int argc, char *argv[])
{
    srand(time(0));
    char catname[9] = {'c', 'a', 't', 0, '.', 't', 'x', 't', '\0' };

    FILE *argstr = fopen("tmpargs","w+");
    int opt_end = 0;
    FILE *stream = stdin;
    if(argv[1][0] == '-')
    {
        if( argv[1][1] == 'w') 
        {
            if(argv[2][0] == '1' || argv[2][0] == '2' || argv[2][0] == '3')
                catname[3] = argv[2][0];
            else
            {
                fprintf(stderr, "invalid choice of which cat, cat%c.txt, random cat chosen\n", argv[2][0]);
                catname[3] = (rand()%3 + 1) + '0'; // A = 1, B = 3
            }
        }    
        else
        {
            if(argc > 1) {
                fprintf(stderr, "unknown option: %s\n", argv[1]);
                exit(1);
            }
            catname[3] = (rand()%3 + 1) + '0'; // A = 1, B = 3
        }
        opt_end++;
    }
    if( argc >= 2)
    {
        for( int i = opt_end + 1; i < argc; i++)
            fprintf(argstr,"%s",argv[i]);
        stream = NULL;
        stream = argstr;
    }
    FILE *fp = fopen(catname, "rb");

    char buf[MAXBUF] = {};
    int c, col = 0, max_col = 0, i = 0, tabcnt = 0;

    while( (c = getc(stream)) != EOF)
    {
        buf[i] = c;
        if(c == '\t') { col = ((col + 8) / 8 * 8); tabcnt++; }
        if(c == '\n') { max_col = col > max_col ? col : max_col; col = 0;}
        col++; i++;
    }
    buf[i+1] = '\0';
    max_col+= 2;

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
    fclose(argstr);
    remove("tmpargs");
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
