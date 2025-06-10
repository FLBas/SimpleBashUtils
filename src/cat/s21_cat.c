#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Flags flag = {0};

  parcer(argc, argv, &flag);

  if (flag.mistake)
    printf("cat: invalid option -- %s", argv[1]);
  else
    reader(argv, flag);

  return 0;
}

void parcer(int argc, char *argv[], Flags *flag) {
  struct option longFlags[] = {{"number-nonblank", 0, 0, 'b'},
                               {"number", 0, 0, 'n'},
                               {"squeeze-blank", 0, 0, 's'},
                               {0, 0, 0, 0}};

  int flags;

  while ((flags = getopt_long(argc, argv, "benstvET", longFlags, NULL)) != -1) {
    switch (flags) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->E = 1;
        flag->v = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->T = 1;
        flag->v = 1;
        break;
      case 'E':
        flag->E = 1;
        break;
      case 'T':
        flag->T = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default:
        flag->mistake = 1;
        exit(1);
        break;
    }
  }
  if (flag->b) flag->n = 0;
}

void reader(char *argv[], Flags flag) {
  int i = 1;

  int cur;
  int str_cnt = 0;
  int counter = 0;
  int flag_s = 0;
  int cnt_s = 0;

  while (argv[i] != NULL) {
    if ((*argv[i]) == '-') {
      i++;
      continue;
    } else {
      FILE *f = fopen(argv[i], "r");

      if (f) {
        while ((cur = fgetc(f)) != EOF) {
          if (flag.s) {
            if (cat_flag_s(cur, &cnt_s, &flag_s)) {
              continue;
            }
          }
          if (flag.b) {
            cat_flag_b(cur, &str_cnt, &counter);
          }
          if (flag.n) {
            cat_flag_n(cur, &str_cnt, &counter);
          }
          if (flag.T) {
            cat_flag_T(cur);
            if (cur == '\t') {
              continue;
            }
          }
          if (flag.E) {
            cat_flag_E(cur);
          }
          if (flag.v) {
            cat_flag_v(cur);
            continue;
          }

          printf("%c", cur);
        }
        fclose(f);
      } else {
        printf("cat: %s: No such file or directory\n", argv[i]);
      }
    }
    i++;
  }
}

void cat_flag_b(int cur, int *str_cnt, int *counter) {
  if (cur != '\n' && (*counter) == 0) {
    printf("%6d\t", ++(*str_cnt));
    (*counter) = 1;
  } else if (cur == '\n') {
    (*counter) = 0;
  }
}

int cat_flag_s(int cur, int *cnt_s, int *flag_s) {
  int flag = 0;

  if (cur != '\n' && *cnt_s == 0) {
    (*cnt_s) = 1;
    (*flag_s) = 0;
  } else if (cur == '\n' && *cnt_s == 1)
    (*cnt_s) = 0;
  else if (cur == '\n' && *cnt_s == 0 && *flag_s == 0)
    (*flag_s) = 1;
  else if (cur == '\n' && *flag_s == 1)
    flag = 1;

  return flag;
}

void cat_flag_n(int cur, int *str_cnt, int *counter) {
  if (cur != '\n' && (*counter == 0)) {
    printf("%6d\t", ++(*str_cnt));
    (*counter) = 1;
  }
  if (cur == '\n' && (*counter) == 1) {
    (*counter) = 0;
  } else if (cur == '\n' && (*counter) == 0)
    printf("%6d\t", ++(*str_cnt));
}

void cat_flag_E(int cur) {
  if (cur == '\n') {
    printf("$");
  }
}

void cat_flag_T(int cur) {
  if (cur == '\t') {
    printf("^%c", cur + 64);
  }
}

void cat_flag_v(int cur) {
  if ((cur < 32 && cur != '\t' && cur != '\n')) {
    printf("^%c", cur + 64);
  } else if (cur == 127) {
    printf("^?");
  } else if (cur > 127 && cur <= 159) {
    printf("M-^%c", cur - 64);
  } else if (cur >= 160 && cur <= 254) {
    printf("M-%c", cur - 128);
  } else if (cur == 255) {
    printf("M-^?");
  } else {
    printf("%c", cur);
  }
}