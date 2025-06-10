#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int mistake;
} Flags;

void chek_flag(int argc, char *argv[], Flags *flag);
void get_buffer(char ***optarg_value, char *optarg, int *cnt_arr);
void reader(int argc, char *argv[], int optind, char **optarg_value, Flags flag,
            int cnt_arr);
void grepFile(char *argv[], FILE *file, Flags flag, char **optarg_value,
              int cnt_arr, int index_filename, int cnt_files);
int get_result(char **optarg_value, Flags flag, int cnt_arr, char *line,
               int *cnt_match);