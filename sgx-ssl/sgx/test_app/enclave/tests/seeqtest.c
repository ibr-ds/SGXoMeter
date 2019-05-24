//
// Created by moe on 24.05.19.
//

#include "../seeq/seeq.h"
#include "../TestMacros.h"
#include "../TestEnclave.h"

int seeq_test() {

    struct seeqarg_t args;

    args.showdist  = SHOW_DIST_FLAG * MASK_INV;
    args.showpos   = SHOW_POS_FLAG * MASK_INV;
    args.showline  = SHOW_LINE_FLAG * MASK_COUNT;
    args.printline = PRINT_LINE_FLAG * MASK_INV;
    args.matchonly = MATCH_ONLY_FLAG * MASK_INV;
    args.count     = COUNT_FLAG;
    args.compact   = COMPACT_FLAG * MASK_INV;
    args.dist      = DIST_FLAG;
    args.verbose   = VERBOSE_FLAG;
    args.endline   = END_LINE_FLAG * MASK_INV;
    args.prefix    = PREFIX_FLAG * MASK_INV;
    args.invert    = INVERT_FLAG * MASK_INV;
    args.best      = BEST_FLAG * MASK_INV;
    args.non_dna   = NON_DNA_FLAG;
    args.all       = ALL_FLAG;
    args.memory    = MEMORY_ARG;

    return seeq(expr, input, args);

}