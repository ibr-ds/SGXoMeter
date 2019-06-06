//
// Created by moe on 05.06.19.
//

#ifndef TEST_APP_INPUTPARSER_H
#define TEST_APP_INPUTPARSER_H


#include <getopt.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>


#if defined(__cplusplus)
extern "C" {
#endif

void say_usage(void);
void say_help(void);
void parseSeeqInput(int argc, char **argv);

#if defined(__cplusplus)
}
#endif




#endif //TEST_APP_INPUTPARSER_H
