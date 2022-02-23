#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_CATS 4
#define MAXBUF 5000
enum errcode {NOT_IN_RANGE, NOT_A_NUMBER, HAS_ADDITIONAL_CHARS};

//CAT ASCII art images found on https://www.asciiart.eu/animals/cats
//credit/signatures left in images originally containing them
//
//getopt usage from https://www.gnu.org

void print_loop(char, int cnt);
void print_cat(int which);
void error(int errcode);
int get_random_cat();
int parse_catname_from_opts(int, char *[]);
FILE *safe_create_tmpfile();

int main(int argc, char *argv[])
{
    srand(time(0));
    FILE *tmpargs = safe_create_tmpfile();
    FILE *stream;

    int catname = parse_catname_from_opts(argc, argv);

    if (1) optind--;
    for (int index = optind; index < argc; index++)
    {
        fprintf(tmpargs, "%s", argv[index]);
        if( argc-index != 1)
        {
            fprintf(tmpargs, " ");
        }
    }

    // stream *verify_stream(tmpargs)
    fseek(tmpargs, 0, SEEK_END);
    if ( (ftell(tmpargs) == 0))
    {
        stream = stdin;
    }
    else
    {
        fprintf(tmpargs, "\n");
        stream = tmpargs;
    }
    fseek(tmpargs, 0, SEEK_SET);

    char buf[MAXBUF] = {};
    int c, col = 0, max_col = 0, i = 0, tabcnt = 0;

    while( (c = getc(stream)) != EOF)
    {
        buf[i] = c;
        if(c == '\t') { col = ((col + 8) / 8 * 8); tabcnt++; }
        if(c == '\n') { max_col = col > max_col ? col : max_col; col = 0;}
        col++; i++;
    }
    buf[i] = '\0';
    max_col+= 2;

    putchar(' '); print_loop('_', max_col); putchar(' ');
    printf("\n/"); print_loop(' ', max_col); printf("\\\n| ");
    i = 0; col = 0; tabcnt = 0;
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

int parse_catname_from_opts(int argc, char *argv[])
{
    int o, catname = -1;
    while (( o = getopt(argc, argv, "w:")) != -1)
    {
        switch(o)
        {
            case 'w':
                if( !isdigit(optarg[0]) ) 
                {
                    catname = optarg[0] - '0'; // atoi()
                    if( optarg[1] != '\0' )
                    {
                        error(HAS_ADDITIONAL_CHARS);
                    }
                    if( catname > MAX_CATS || catname <= 0 ) 
                    {
                        error(NOT_IN_RANGE);
                        catname = get_random_cat();
                    }
                }
                else
                {
                    catname = get_random_cat(); // decrement optind
                }
                break;
            case '?':
                if (optopt == 'w')
                {
                    error(NOT_A_NUMBER);
                    catname = get_random_cat();
                }
                break;
            default:
                abort();
        }
    }
    return catname;
}

FILE *safe_create_tmpfile()
{
    FILE *tmpargs = tmpfile();
    if(tmpargs == NULL) 
    { 
        perror("catsay: create tmpfile"); 
        exit(1); 
    }
    return tmpargs;
}

//  returns true if the error requires the generation of a random cat
//  returns false otherwise and can be ignored
void error(int errcode)
{
    if(errcode == NOT_IN_RANGE || errcode == NOT_A_NUMBER)
    {
        fprintf(stderr,"Option -w requires a number [1-4]\n");
    }
    else if (errcode == HAS_ADDITIONAL_CHARS)
    {
        fprintf(stderr, "Option -w interpretted its argument as '%c', all other characters were ignored.\n", optarg[0]);
    }
}

int get_random_cat()
{
    fprintf(stderr, "Random cat chosen.\n");
    return (rand()%MAX_CATS + 1);
}

void print_loop(char c, int cnt)
{
    // TODO :
    // for cnt do
        // generate string of " " w sizeof cnt
    if(cnt > 0)
    {
        putchar(c);
        cnt--;
        print_loop(c, cnt);
    }
    else return;
}

void print_cat(int which) 
{
START:
    switch(which) 
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
        case(4):
            printf("      \\ ^  /\\\n       )  ( ')\n      (  /  )\njgs    \\(__)|");
            break;
        default:
            goto DEFAULT_ERROR;
            break;
    }
    putchar('\n');
    return;
DEFAULT_ERROR:
    which = get_random_cat();
    goto START;
}
