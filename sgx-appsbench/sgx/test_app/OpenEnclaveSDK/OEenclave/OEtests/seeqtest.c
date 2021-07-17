//
// Created by moe on 24.05.19.
//

#ifdef DNA_PATTERN_MATCHING
#include <UtilsStructs.h>
#include "seeq.h"


struct seeqarg_t args;
static globalConfig_t *globConfPtr;


void pre_seeq_test(globalConfig_t *globalConfig)
{

    globConfPtr = globalConfig;

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


}


int seeq_test()
{
        return seeq(globConfPtr->PATTERN_INPUT, globConfPtr->DNA_INPUT, args);
}
#endif