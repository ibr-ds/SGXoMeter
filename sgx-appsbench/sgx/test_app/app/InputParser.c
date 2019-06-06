#include "InputParser.h"

static const char *TOOL_USAGE = "Usage:"
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


static const char *SEEQ_USAGE = "Usage:"
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
    fprintf(stderr, "%s\n", SEEQ_USAGE);
}
void say_help(void)
{
    fprintf(stderr, "use '-h' for help.\n");
}

void parseSeeqInput(int argc, char **argv)
{
    char *expr, *input;

    // Unset flags (value -1).
    int showdist_flag  = -1;
    int showpos_flag   = -1;
    int printline_flag = -1;
    int matchonly_flag = -1;
    int showline_flag  = -1;
    int count_flag     = -1;
    int invert_flag    = -1;
    int compact_flag   = -1;
    int dist_flag      = -1;
    int verbose_flag   = -1;
    int endline_flag   = -1;
    int prefix_flag    = -1;
    int best_flag      = -1;
    int nondna_flag    = -1;
    int memory_flag    = -1;
    int all_flag       = -1;

    // Unset options (value 'UNSET').
    input = NULL;

    if (argc == 1) {
        say_usage();
        exit(EXIT_SUCCESS);
    }

    int c;
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
                {"positions",     no_argument, 0, 'p'},
                {"match-only",    no_argument, 0, 'm'},
                {"no-printline",  no_argument, 0, 'n'},
                {"print-dist",    no_argument, 0, 'k'},
                {"nondna",  required_argument, 0, 'x'},
                {"lines",         no_argument, 0, 'l'},
                {"count",         no_argument, 0, 'c'},
                {"invert",        no_argument, 0, 'i'},
                {"format-compact",no_argument, 0, 'f'},
                {"verbose",       no_argument, 0, 'z'},
                {"version",       no_argument, 0, 'v'},
                {"help",          no_argument, 0, 'h'},
                {"end",           no_argument, 0, 'e'},
                {"prefix",        no_argument, 0, 'r'},
                {"best",          no_argument, 0, 'b'},
                {"all",           no_argument, 0, 'a'},
                {"memory",  required_argument, 0, 'y'},
                {"distance",required_argument, 0, 'd'},
                {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "apmnilczfvkherby:d:x:",
                        long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1) break;

        switch (c) {
            case 'd':
                if (dist_flag < 0) {
                    int dist = atoi(optarg);
                    if (dist < 0) {
                        fprintf(stderr, "error: distance must be a positive integer.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    dist_flag = atoi(optarg);
                }
                else {
                    fprintf(stderr, "error: distance option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'y':
                if (memory_flag < 0) {
                    int memory = atoi(optarg);
                    if (memory < 0) {
                        fprintf(stderr, "error: memory limit must be a positive integer.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    memory_flag = atoi(optarg);
                }
                else {
                    fprintf(stderr, "error: memory option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'v':
                exit(EXIT_SUCCESS);

            case 'z':
                if (verbose_flag < 0) {
                    verbose_flag = 1;
                }
                else {
                    fprintf(stderr, "error: verbose option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'r':
                if (prefix_flag < 0) {
                    prefix_flag = 1;
                }
                else {
                    fprintf(stderr, "error: 'prefix' option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'a':
                if (all_flag < 0) {
                    all_flag = 1;
                }
                else {
                    fprintf(stderr, "error: 'all' option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'x':
                if (nondna_flag < 0) {
                    int nondna = atoi(optarg);
                    if (nondna < 0 || nondna > 2) {
                        fprintf(stderr, "error: nondna value must be either 0, 1 or 2.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    nondna_flag = nondna;
                }
                else {
                    fprintf(stderr, "error: 'nondna' option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;


            case 'b':
                if (best_flag < 0) {
                    best_flag = 1;
                }
                else {
                    fprintf(stderr, "error: 'best' option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;


            case 'e':
                if (endline_flag < 0) {
                    endline_flag = 1;
                }
                else {
                    fprintf(stderr, "error: line-end option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'p':
                if (showpos_flag < 0) {
                    showpos_flag = 1;
                }
                else {
                    fprintf(stderr, "error: show-position option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'm':
                if (matchonly_flag < 0) {
                    matchonly_flag = 1;
                }
                else {
                    fprintf(stderr, "error: match-only option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'n':
                if (printline_flag < 0) {
                    printline_flag = 0;
                }
                else {
                    fprintf(stderr, "error: no-printline option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'k':
                if (showdist_flag < 0) {
                    showdist_flag = 1;
                }
                else {
                    fprintf(stderr, "error: show-distance option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'l':
                if (showline_flag < 0) {
                    showline_flag = 1;
                }
                else {
                    fprintf(stderr, "error: show-line option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'c':
                if (count_flag < 0) {
                    count_flag = 1;
                }
                else {
                    fprintf(stderr, "error: count option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'i':
                if (invert_flag < 0) {
                    invert_flag = 1;
                }
                else {
                    fprintf(stderr, "error: invert option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'f':
                if (compact_flag < 0) {
                    compact_flag = 1;
                }
                else {
                    fprintf(stderr, "error: format-compact option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'h':
                say_usage();
                exit(0);

            default:
                break;
        }
    }

    if (optind == argc) {
        fprintf(stderr, "error: not enough arguments.\n");
        say_help();
        exit(EXIT_FAILURE);
    }
    expr = argv[optind++];

    if (optind < argc) {
        if ((optind == argc - 1) && (input == NULL)) {
            input = argv[optind];
        }
        else {
            fprintf(stderr, "error: too many options.\n");
            say_help();
            exit(EXIT_FAILURE);
        }
    }
    if (count_flag == -1) count_flag = 0;
    if (showdist_flag == -1) showdist_flag = 0;
    if (showpos_flag  == -1) showpos_flag = 0;
    if (matchonly_flag == -1) matchonly_flag = 0;
    if (showline_flag == -1) showline_flag = 0;
    if (invert_flag == -1) invert_flag = 0;
    if (compact_flag == -1) compact_flag = 0;
    if (dist_flag == -1) dist_flag = 0;
    if (verbose_flag == -1) verbose_flag = 0;
    if (endline_flag == -1) endline_flag = 0;
    if (prefix_flag == -1) prefix_flag = 0;
    if (best_flag == -1) best_flag = 0;
    if (nondna_flag == -1) nondna_flag = 0;
    if (memory_flag == -1) memory_flag = 0;
    if (all_flag == -1) all_flag = 0;
    if (printline_flag == -1) printline_flag = (!matchonly_flag && !endline_flag && !prefix_flag);

    if (!showdist_flag && !showpos_flag && !printline_flag && !matchonly_flag && !showline_flag && !count_flag && !compact_flag && !prefix_flag && !endline_flag) {
        fprintf(stderr, "Invalid options: No output will be generated.\n");
        say_help();
        exit(EXIT_FAILURE);
    }

    /*int maskcnt = !count_flag;
    int maskinv = !invert_flag * maskcnt;

    struct seeqarg_t args;

    args.showdist  = showdist_flag * maskinv;
    args.showpos   = showpos_flag * maskinv;
    args.showline  = showline_flag * maskcnt;
    args.printline = printline_flag * maskinv;
    args.matchonly = matchonly_flag * maskinv;
    args.count     = count_flag;
    args.compact   = compact_flag * maskinv;
    args.dist      = dist_flag;
    args.verbose   = verbose_flag;
    args.endline   = endline_flag * maskinv;
    args.prefix    = prefix_flag * maskinv;
    args.invert    = invert_flag * maskcnt;
    args.best      = best_flag * maskinv;
    args.non_dna    = nondna_flag;
    args.all       = all_flag;
    args.memory    = (size_t)memory_flag * 1024*1024;
*/ //ToDO under construction
}
