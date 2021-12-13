#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <error.h>

#define MAXBUF 5000

//CAT ASCII art images found on https://www.asciiart.eu/animals/cats
//credit/signatures left in images originally containing them
//
//getopt usage from https://www.gnu.org

void print_loop(char, int);
void print_cat(int);

int main(int argc, char *argv[])
{
    srand(time(0));
    int catname = catname = (rand()%3 + 1);
    FILE *tmpargs = tmpfile();
    if( !tmpargs) { perror("catsay: create tmpfile"); exit(1); }
    FILE *stream = stdin;
    
    int o, index; 
    while (( o = getopt(argc, argv, "w:")) != -1)
        switch(o)
        {
            case 'w':
                if( isdigit(optarg[0]) ) 
                {
                    catname = optarg[0] - '0';
                    if( optarg[1] != '\0' )
                        fprintf(stderr, "Option -w interpretted its argument as '%c', all other characters were ignored.\n", optarg[0]);
                }
                else
                    fprintf(stderr,"Option -w requires a number <1,2,3>\n");
                break;
            case '?':
                if (optopt == 'w')
                {
                    catname = (rand()%3 + 1); // A = 1, B = 3
                    fprintf (stderr, "Random cat chosen.\n");
                }
                break;
            default:
                abort();
        }
    for (index = optind; index < argc; index++)
    {
        fprintf(tmpargs, "%s", argv[index]);
        printf("%s",argv[index]);
        stream = tmpargs;
        if( argc-index == 1 ) 
            catname = (rand()%3 + 1);
    }

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

    print_cat(catname);
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

void print_cat(int cat_type) 
{
START:
    switch(cat_type) 
    {
        case(1):
            printf("           \\           /)\n            \\  /\\___/\\ ((\n               \\`@_@'/  ))\n               {_:Y:.}_//\n hjw ----------{_}^-'{_}----------");
            break;
        case(2):
            printf("          /\n         /              | \\\n        /               | |\n       /                | |\n   |\\                   | |\n  /, ~\\                / /\n X     `-.....-------./ /\n  ~-. ~  ~              |\n     \\             /    |\n      \\  /_     ___\\   /\n      | /\\ ~~~~~   \\ |\n      | | \\        || |\n      | |\\ \\       || )\n     (_/ (_/      ((_/");
            break;
        case(3):
            printf("     \\\n      \\   \\`*-.\n       \\   )  _`-.\n          .  : `. .\n          : _   '  \\\n          ; *` _.   `*-._\n          `-.-'          `-.\n            ;       `       `.\n            :.       .        \\\n            . \\  .   :   .-'   .\n            '  `+.;  ;  '      :\n            :  '  |    ;       ;-.\n            ; '   : :`-:     _.`* ;\n   [bug] .*' /  .*' ; .*`- +'  `*'\n         `*-*   `*-*  `*-*'");
            break;
        default:
            goto DEFAULT_ERROR;
            break;
    }
    putchar('\n');
    return;
DEFAULT_ERROR:
    cat_type = (rand()%3 + 1);
    fprintf(stderr,"%s() chose a random cat.\n",__func__);
    goto START;
}
