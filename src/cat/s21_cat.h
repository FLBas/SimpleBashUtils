#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int b;
  int E;
  int n;
  int s;
  int T;
  int v;
  int mistake;
} Flags;

void parcer(int argc, char *argv[], Flags *flag);
void reader(char *argv[], Flags flag);
void cat_flag_b(int cur, int *str_cnt, int *counter);
void cat_flag_E(int cur);
void cat_flag_v(int cur);
int cat_flag_s(int cur, int *cnt_s, int *flag_s);
void cat_flag_n(int cur, int *str_cnt, int *counter);
void cat_flag_T(int cur);