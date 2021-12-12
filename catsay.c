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
void get_options(int, char *[], char *);

int main(int argc, char *argv[])
{
    srand(time(0));
    char catname[9] = {'c', 'a', 't', 0, '.', 't', 'x', 't', '\0' };
    FILE *argstr = fopen("tmpargs","w+");
    if( !argstr) { perror("catsay: create tmpargs:"); exit(1); }
    FILE *stream = stdin;
    
    int o, index; 
    while (( o = getopt(argc, argv, "w:")) != -1)
        switch(o)
        {
            case 'w':
                if( isdigit(optarg[0]) ) 
                {
                    catname[3] = optarg[0];
                    if( optarg[1] != '\0' )
                        fprintf(stderr, "Option -w interpretted its argument as '%c', all other characters were ignored.\n", optarg[0]);
                }
                else
                    fprintf(stderr,"Option -w requires a number <1,2,3>\n");
                break;
            case '?':
                if (optopt == 'w')
                {
                    catname[3] = (rand()%3 + 1) + '0'; // A = 1, B = 3
                    fprintf (stderr, "Random cat chosen.\n");
                }
                    //fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                /*else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,"Unknown option character `\\x%x'.\n",optopt);*/
                break;
            default:
                abort();
        }
    for (index = optind; index < argc; index++)
    {
        fprintf(argstr, "%s", argv[index]);
        stream = argstr;
    }

    FILE *fp = fopen(catname, "rb");
    if( !fp) { perror("catsay: read catfile:"); exit(1);}
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

void get_options(int argc, char *argv[], char *catname)
{
    if(argv[1][0] == '-')
    {
        if( argv[1][1] == 'w') 
        {
            if(argv[2][0] == '1' || argv[2][0] == '2' || argv[2][0] == '3')
                catname[3] = argv[2][0];
            else
            {
                fprintf(stderr, "invalid choice of which cat, cat%c.txt; random cat chosen\n", argv[2][0]);
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
    }
    else
        catname[3] = (rand()%3 + 1) + '0'; // A = 1, B = 3
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
