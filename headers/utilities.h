#ifndef UTILITIES_H
#define UTILITIES_H

#define SD_ARG_ROWS         "-r"
#define SD_ARG_COLUMNS      "-c"
#define SD_ARG_THREADS      "-t"

#define DD_ARG_ROWS         "--rows"
#define DD_ARG_COLUMNS      "--columns"
#define DD_ARG_THREADS      "--threads"
#define DD_ARG_HELP         "--help"

#define SCC_ARGS            200
#define SCC_HELP            201

#define ERR_ARGC            400
#define ERR_NO_ROWS         401
#define ERR_NO_COLUMNS      402
#define ERR_NO_THREADS      403
#define ERR_INVLD_ROWS      404
#define ERR_INVLD_COLUMNS   405
#define ERR_INVLD_THREADS   406
#define ERR_MEMORY          407
#define ERR_NOT_MANAGED     408

void help(char* program_name);
int get_params_code(int argc, char** argv);
int check_params(int argc, char** argv);

#endif
