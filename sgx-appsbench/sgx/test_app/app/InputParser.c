#include "GlobalVariables.h" // ToDo delete this later after full cmake support
#include "InputParser.h"

#ifdef RUNTIME_PARSER

/*  ToDo: here are the shared global variables to define */
/*#ifdef WRITE_LOG_FILE
char *DATA_FILE_NAME = PLOTDATA_FILE_NAME;
#endif

int NUM_OF_ITERATION = NUMBER_OF_ITERATIONS; //WILL BE USED
uint64_t ARR_SIZE = ARRAY_SIZE;
uint64_t RATE = CYCLES_RATE;
*/
/*  ToDo: Here is the definition of the globalConfig with default values   */
globalConfig_t GLOBAL_CONFIG = {
#ifdef WRITE_LOG_FILE
        .DATA_FILE_NAME = PLOTDATA_FILE_NAME,
#endif
        .NUM_OF_ITERATION = NUMBER_OF_ITERATIONS,
        .RUNTIME = RUNTIME_PHASE,
        .WARMUP_TIME = WARMUP_PHASE

#ifdef DNA_PATTERN_MATCHING
        ,
        .DNA_INPUT = INPUT_DNA,
        .PATTERN_INPUT = PATTERN,
        .SHOW_DIST = DIST_FLAG,
        .SHOW_POS = SHOW_POS_FLAG,
        .SHOW_LINE = SHOW_LINE_FLAG,
        .PRINT_LINE = PRINT_LINE_FLAG,
        .MATCH_ONLY = MATCH_ONLY_FLAG,
        .COUNT = COUNT_FLAG,
        .COMPACT = COMPACT_FLAG,
        .DIST = DIST_FLAG,
        .VERBOSE = VERBOSE_FLAG,
        .END_LINE = END_LINE_FLAG,
        .PREFIX = PREFIX_FLAG,
        .INVERT = INVERT_FLAG,
        .BEST = BEST_FLAG,
        .NON_DNA = NON_DNA_FLAG,
        .ALL = ALL_FLAG,
        .MEMORY = (size_t)MEMORY_ARG 

#endif
};


/* ToDo: the end of the global variables definition      */



static const char *TOOL_USAGE = "Tool Usage:"
                           "  TestApp [options]\n"
                           "\n   CONFIG OPTIONS:\n"
#ifdef WRITE_LOG_FILE
                           "    -o --data-output [file name]     sets the name of the generated data file [default plotdata.txt]\n"
#endif
                           "    -R --runtime-phase  [#]          sets the runtime phase for each benchmark test [default 60 seconds]\n"
                           "    -I --iteration [#]               sets the number of iterations [default 0 (unlimited)]\n"
                           "    -w --warmup-phase [#]            sets the warmup phase time for each benchmark test [default 10 seconds)]\n";

#ifdef DNA_PATTERN_MATCHING

static const char *SEEQ_USAGE = "DNA MATCHER Usage:\n"
                                "\n   INPUT OPTION:\n"
                                "    -P --pattern [sought pattern]    sets the pattern to seek in the DNA [default predefined pattern]\n"
                                "    -D --DNA [search DNA]            sets the DNA for the pattern search process [default predefined DNA]\n"
                                "\n   MATCHING OPTIONS:\n"
                                "    -d --distance [#]                maximum Levenshtein distance [default 0]\n"
                                "    -i --invert                      return only the non-matching lines\n"
                                "    -b --best                        scan the whole line to find the best match [default: first match only]\n"
                                "    -a --all                         returns all the matches (implies -m) [default: first match only]\n"
                                "    -x --nondna [0,1,2]              non-DNA characters: 0-skip line, 1-convert to 'N', 2-ignore. [default 0]\n"
                                "\n   FORMAT OPTIONS:\n"
                                "    -c --count                       returns the count of matching lines\n"
                                "    -m --match-only                  print only the matched sequence\n"
                                "    -n --no-printline                do not print the matched sequence\n"
                                "    -l --lines                       shows the line number of the match\n"
                                "    -p --positions                   shows the position of the match\n"
                                "    -k --print-dist                  shows the Levenshtein distance of the match\n"
                                "    -f --compact                     prints output in compact format (line:pos:dist)\n"
                                "    -e --end                         print only the end of the line, starting after the match\n"
                                "    -r --prefix                      print only the prefix, ending before the match\n"
                                "\n   OTHER OPTIONS:\n"
                                "    -v --version                     print version\n"
                                "    -y --memory                      set DFA memory limit (in MB)\n"
                                "    -z --verbose                     verbose using stderr\n";

#endif


void say_usage()
{
    fprintf(stderr, "%s\n", TOOL_USAGE);
#ifdef DNA_PATTERN_MATCHING
    fprintf(stderr, "%s\n", SEEQ_USAGE);
#endif
}
void say_help(void)
{
    fprintf(stderr, "use '-h' for help.\n");
}



#define FLAG_IS_SET 1
#define FLAG_NOT_SET -1

void parseInput(int argc, char **argv)
{

#ifdef WRITE_LOG_FILE
    int o_flag = FLAG_NOT_SET; 
#endif

    int r_flag = FLAG_NOT_SET, t_flag = FLAG_NOT_SET, w_flag = FLAG_NOT_SET;
#ifdef DNA_PATTERN_MATCHING
    int pattern_flag   = FLAG_NOT_SET;
    int dna_flag       = FLAG_NOT_SET;
    int showdist_flag  = FLAG_NOT_SET;
    int showpos_flag   = FLAG_NOT_SET;
    int printline_flag = FLAG_NOT_SET;
    int matchonly_flag = FLAG_NOT_SET;
    int showline_flag  = FLAG_NOT_SET;
    int count_flag     = FLAG_NOT_SET;
    int invert_flag    = FLAG_NOT_SET;
    int compact_flag   = FLAG_NOT_SET;
    int dist_flag      = FLAG_NOT_SET;
    int verbose_flag   = FLAG_NOT_SET;
    int endline_flag   = FLAG_NOT_SET;
    int prefix_flag    = FLAG_NOT_SET;
    int best_flag      = FLAG_NOT_SET;
    int nondna_flag    = FLAG_NOT_SET;
    int memory_flag    = FLAG_NOT_SET;
    int all_flag       = FLAG_NOT_SET;
#endif

    int c;
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
                {"runtime-phase"    ,  required_argument, 0, 'R'},
                {"iteration"        ,  required_argument, 0, 'I'},
                {"warmup-phase"     ,  required_argument, 0, 'w'},
#ifdef WRITE_LOG_FILE
                {"data-output"      ,  required_argument, 0, 'o'},
#endif
                {"help"             ,  required_argument, 0, 'h'},

#ifdef DNA_PATTERN_MATCHING
                {"pattern"          ,  required_argument, 0, 'P'},
                {"DNA-input"        ,  required_argument, 0, 'D'},
                {"positions"        ,    no_argument    , 0, 'p'},
                {"match-only"       ,    no_argument    , 0, 'm'},
                {"no-printline"     ,    no_argument    , 0, 'n'},
                {"print-dist"       ,    no_argument    , 0, 'k'},
                {"nondna"           ,  required_argument, 0, 'x'},
                {"lines"            ,    no_argument    , 0, 'l'},
                {"count"            ,    no_argument    , 0, 'c'},
                {"invert"           ,    no_argument    , 0, 'i'},
                {"format-compact"   ,    no_argument    , 0, 'f'},
                {"verbose"          ,    no_argument    , 0, 'z'},
                {"version"          ,    no_argument    , 0, 'v'},
                {"help"             ,    no_argument    , 0, 'h'},
                {"end"              ,    no_argument    , 0, 'e'},
                {"prefix"           ,    no_argument    , 0, 'r'},
                {"best"             ,    no_argument    , 0, 'b'},
                {"all"              ,    no_argument    , 0, 'a'},
                {"memory"           ,  required_argument, 0, 'y'},
                {"distance"         ,  required_argument, 0, 'd'},

#endif
                {0                  ,         0         , 0,  0 }
        };

        const char * allowedOptions = "hw:R:S:I:"
#ifdef WRITE_LOG_FILE
				      "o:"
#endif

#ifdef DNA_PATTERN_MATCHING
                                      "apmnilczfvkherby:d:x:P:D:"
#endif
        ;

        c = getopt_long(argc, argv, allowedOptions, long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1)  break;
        switch (c) {
#ifdef WRITE_LOG_FILE
            case 'o':
                if (o_flag  == FLAG_NOT_SET) {

                    if (strlen(optarg) == 0) {
                        fprintf(stderr, "error: Invalid file name!.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    o_flag = FLAG_IS_SET;
                    GLOBAL_CONFIG.DATA_FILE_NAME = optarg;
                }
                else {
                    fprintf(stderr, "error: Output file name option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;
#endif

            case 'w':
                if (w_flag  == FLAG_NOT_SET) {
                    uint64_t wTime = atol(optarg);
                    if (wTime < 0) {
                        fprintf(stderr, "error: Invalid warmup time value!.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    w_flag = FLAG_IS_SET;
                    GLOBAL_CONFIG.WARMUP_TIME = wTime;
                }
                else {
                    fprintf(stderr, "error: Warmup time value is set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'R':
                if (r_flag  == FLAG_NOT_SET) {
                    uint64_t runtime = atol(optarg);  //ToDo you can replace this with strtoul but then you need an extra char pointer for the rest of the input and extra checks and free
                    if (runtime < 0) {
                        fprintf(stderr, "error: Runtime value should be positive!\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    r_flag = FLAG_IS_SET;
                    GLOBAL_CONFIG.RUNTIME = runtime;
                }
                else {
                    fprintf(stderr, "error: Runtime value is set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;


            case 'I':
                if (t_flag == FLAG_NOT_SET) {
                    int iterations = atoi(optarg);
                    if (iterations < 0) {
                        fprintf(stderr, "error: Number of iterations must be 0(unlimited) or a positive integer.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    t_flag = FLAG_IS_SET;
                    GLOBAL_CONFIG.NUM_OF_ITERATION = iterations;
                }
                else {
                    fprintf(stderr, "error: Number of iterations option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

#ifdef DNA_PATTERN_MATCHING
            case 'P':
                if (pattern_flag  == FLAG_NOT_SET) {

                    if (strlen(optarg) == 0) {
                        fprintf(stderr, "error: Invalid pattern format!.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    pattern_flag = FLAG_IS_SET;
                    GLOBAL_CONFIG.PATTERN_INPUT = optarg;
                }
                else {
                    fprintf(stderr, "error: Pattern option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

            case 'D':
                if (dna_flag  == FLAG_NOT_SET) {

                    if (strlen(optarg) == 0) {
                        fprintf(stderr, "error: Invalid DNA input format!.\n");
                        say_help();
                        exit(EXIT_FAILURE);
                    }
                    dna_flag = FLAG_IS_SET;
                    GLOBAL_CONFIG.DNA_INPUT = optarg;
                }
                else {
                    fprintf(stderr, "error: DNA input option set more than once.\n");
                    say_help();
                    exit(EXIT_FAILURE);
                }
                break;

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
#endif
            case 'h':
                say_usage();
                exit(EXIT_SUCCESS);

            default:
                break;
        }
    }
#ifdef DNA_PATTERN_MATCHING
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

    int maskcnt = !count_flag;
    int maskinv = !invert_flag * maskcnt;

    GLOBAL_CONFIG.SHOW_DIST     = showdist_flag * maskinv;
    GLOBAL_CONFIG.SHOW_POS      = showpos_flag * maskinv;
    GLOBAL_CONFIG.SHOW_LINE     = showline_flag * maskcnt;
    GLOBAL_CONFIG.PRINT_LINE    = printline_flag * maskinv;
    GLOBAL_CONFIG.MATCH_ONLY    = matchonly_flag * maskinv;
    GLOBAL_CONFIG.COUNT         = count_flag;
    GLOBAL_CONFIG.COMPACT       = compact_flag * maskinv;
    GLOBAL_CONFIG.DIST          = dist_flag;
    GLOBAL_CONFIG.VERBOSE       = verbose_flag;
    GLOBAL_CONFIG.END_LINE      = endline_flag * maskinv;
    GLOBAL_CONFIG.PREFIX        = prefix_flag * maskinv;
    GLOBAL_CONFIG.INVERT        = invert_flag * maskcnt;
    GLOBAL_CONFIG.BEST          = best_flag * maskinv;
    GLOBAL_CONFIG.NON_DNA       = nondna_flag;
    GLOBAL_CONFIG.ALL           = all_flag;
    GLOBAL_CONFIG.MEMORY        = (size_t)memory_flag * 1024*1024;
#endif
}

#endif
