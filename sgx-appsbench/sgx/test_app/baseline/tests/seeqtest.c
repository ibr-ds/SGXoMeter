//
// Created by moe on 24.05.19.
//
#include <UtilsStructs.h>
#include "seeq.h"

#ifdef DNA_PATTERN_MATCHING
int wrapper_seeq_test(globalConfig_t *globalConfig) {

    struct seeqarg_t args;

    args.showdist  = globalConfig->SHOW_DIST;
    args.showpos   = globalConfig->SHOW_POS;
    args.showline  = globalConfig->SHOW_LINE;
    args.printline = globalConfig->PRINT_LINE;
    args.matchonly = globalConfig->MATCH_ONLY;
    args.count     = globalConfig->COUNT;
    args.compact   = globalConfig->COMPACT;
    args.dist      = globalConfig->DIST;
    args.verbose   = globalConfig->VERBOSE;
    args.endline   = globalConfig->END_LINE;
    args.prefix    = globalConfig->PREFIX;
    args.invert    = globalConfig->INVERT;
    args.best      = globalConfig->BEST;
    args.non_dna   = globalConfig->NON_DNA;
    args.all       = globalConfig->ALL;
    args.memory    = globalConfig->MEMORY;

    return seeq(globalConfig->PATTERN_INPUT, globalConfig->DNA_INPUT, args);

}
#endif