#include "lp.h"

int main(argc, argv)
    int             argc;
    char           *argv[];
{
    int             status;
    char            fname[80];		   /* solution file name */
    CORBO          *kp, *openlp();

    kp = openlp();
    if (kp == NULL) {
	fprintf(stderr, "cannot open another LP problem\n");
	exit(1);
    }
    argc--;
    argv++;
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
	   "+----------------------------------------------------------------------+",
	   "|                                                                      |",
	   "|      AT&T Bell Labs CORBO LP Package : Version 0.25 : April 1990     |",
	   "|                                                                      |",
	   "|      ******** Proprietary to AT&T Bell Laboratories ********         |",
	   "|                                                                      |",
	   "|      Author:  Robert J. Vanderbei                                    |",
	   "|               AT&T Bell Laboratories                                 |",
	   "|               600 Mountain Ave.                                      |",
	   "|               Murray Hill , N. J. 07974                              |",
	   "|               U. S. A.                                               |",
	   "|                                                                      |",
	   "+----------------------------------------------------------------------+");
    fflush(stdout);

    readlp(argc, argv, kp);

    status = optlp(kp);

    strcpy(fname, kp->name);
    strcat(fname, ".out");
    writesol(kp, fname);

    closelp(kp);

}
