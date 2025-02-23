/*
 * The routines in this file provide support for ANSI style terminals
 * over a serial line. The serial I/O services are provided by routines in
 * "termio.c". It compiles into nothing if not an ANSI device.
 */

#define	termdef	1			/* don't define "term" external */

#include        <stdio.h>
#include	"estruct.h"
#include        "edef.h"

#if     ANSI

#if	AMIGA
#define NROW    23                      /* Screen size.                 */
#define NCOL    77                      /* Edit if you want to.         */
#else
#define NROW    25                      /* Screen size.                 */
#define NCOL    80                      /* Edit if you want to.         */
#endif
#define	MARGIN	8			/* size of minimim margin and	*/
#define	SCRSIZ	64			/* scroll size for extended lines */
#define BEL     0x07                    /* BEL character.               */
#define ESC     0x1B                    /* ESC character.               */

extern  int     ttopen();               /* Forward references.          */
extern  int     ttgetc();
extern  int     ttputc();
extern  int     ttflush();
extern  int     ttclose();
extern  int     ansimove();
extern  int     ansieol();
extern  int     ansieop();
extern  int     ansibeep();
extern  int     ansiopen();
extern	int	ansirev();
/*
 * Standard terminal interface dispatch table. Most of the fields point into
 * "termio" code.
 */
TERM    term    = {
        NROW-1,
        NCOL,
	MARGIN,
	SCRSIZ,
        ansiopen,
        ttclose,
        ttgetc,
        ttputc,
        ttflush,
        ansimove,
        ansieol,
        ansieop,
        ansibeep,
	ansirev
};

ansimove(row, col)
{
        ttputc(ESC);
        ttputc('[');
        ansiparm(row+1);
        ttputc(';');
        ansiparm(col+1);
        ttputc('H');
}

ansieol()
{
        ttputc(ESC);
        ttputc('[');
        ttputc('K');
}

ansieop()
{
        ttputc(ESC);
        ttputc('[');
        ttputc('J');
}

ansirev(state)		/* change reverse video state */

int state;	/* TRUE = reverse, FALSE = normal */

{
	ttputc(ESC);
	ttputc('[');
	ttputc(state ? '7': '0');
	ttputc('m');
}

ansibeep()
{
        ttputc(BEL);
        ttflush();
}

ansiparm(n)
register int    n;
{
        register int    q;

        q = n/10;
        if (q != 0)
                ansiparm(q);
        ttputc((n%10) + '0');
}

#endif

ansiopen()
{
#if     V7
        register char *cp;
        char *getenv();

        if ((cp = getenv("TERM")) == NULL) {
                puts("Shell variable TERM not defined!");
                exit(1);
        }
        if (strcmp(cp, "vt100") != 0) {
                puts("Terminal type not 'vt100'!");
                exit(1);
        }
#endif
	revexist = TRUE;
        ttopen();
}
