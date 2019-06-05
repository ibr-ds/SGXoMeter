#include "InputParser.h"

static const char *USAGE = "Usage:"
"  seeq [options] pattern inputfile\n"
"\n   MATCHING OPTIONS:\n"
"    -d --distance [#]    maximum Levenshtein distance [default 0]\n"
"    -i --invert          return only the non-matching lines\n"
"    -b --best            scan the whole line to find the best match [default: first match only]\n"
"    -a --all             returns all the matches (implies -m) [default: first match only]\n"
"    -x --nondna [0,1,2]  non-DNA characters: 0-skip line, 1-convert to 'N', 2-ignore. [default 0]\n"
"\n   FORMAT OPTIONS:\n"
"    -c --count           returns the count of matching lines\n"
"    -m --match-only      print only the matched sequence\n"
"    -n --no-printline    do not print the matched sequence\n"
"    -l --lines           shows the line number of the match\n"
"    -p --positions       shows the position of the match\n"
"    -k --print-dist      shows the Levenshtein distance of the match\n"
"    -f --compact         prints output in compact format (line:pos:dist)\n"
"    -e --end             print only the end of the line, starting after the match\n"
"    -r --prefix          print only the prefix, ending before the match\n"
"\n   OTHER OPTIONS:\n"
"    -v --version         print version\n"
"    -y --memory          set DFA memory limit (in MB)\n"
"    -z --verbose         verbose using stderr\n";


void say_usage(void)
{
    fprintf(stderr, "%s\n", USAGE);
}
void say_help(void)
{
    fprintf(stderr, "use '-h' for help.\n");
}
