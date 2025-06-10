#include "s21_grep.h"

int main(int argc, char *argv[]) {
  Flags flag = {0};

  chek_flag(argc, argv, &flag);

  return 0;
}

void chek_flag(int argc, char *argv[], Flags *flag) {
  int opt = 0;
  int cnt_arr = 0;
  char **optarg_value = NULL;

  while ((opt = getopt(argc, argv, "e:ivclnhs")) != -1) {
    switch (opt) {
      case 'e':
        flag->e = 1;
        get_buffer(&optarg_value, optarg, &cnt_arr);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      default:
        flag->mistake = 1;
        exit(1);
        break;
    }
  }

  if (!flag->e && argc >= 3) {
    get_buffer(&optarg_value, argv[optind], &cnt_arr);
  }

  if (argc > 2)
    reader(argc, argv, optind, optarg_value, *flag, cnt_arr);
  else
    printf("Usage: grep [OPTION]... PATTERNS [FILE]\n");

  for (int j = 0; j < cnt_arr; j++) {
    free(optarg_value[j]);
  }
  free(optarg_value);
}

void get_buffer(char ***optarg_value, char *optarg, int *cnt_arr) {
  (*cnt_arr)++;
  if (*cnt_arr > 1) {
    *optarg_value = (char **)realloc(*optarg_value, *cnt_arr * sizeof(char *));
    (*optarg_value)[*cnt_arr - 1] =
        (char *)malloc((strlen(optarg) + 1) * sizeof(char));
    strcpy((*optarg_value)[*cnt_arr - 1], optarg);
  } else {
    *optarg_value = (char **)malloc(1 * sizeof(char *));
    (*optarg_value)[*cnt_arr - 1] =
        (char *)malloc((strlen(optarg) + 1) * sizeof(char));
    strcpy((*optarg_value)[*cnt_arr - 1], optarg);
  }
}

void reader(int argc, char *argv[], int optind, char **optarg_value, Flags flag,
            int cnt_arr) {
  FILE *file;
  int index_filename = 0;
  int cnt_files = 0;
  for (int i = flag.e ? optind : 1; i < argc; i++) {
    if (argv[i][0] == '-' || strcmp(argv[i], optarg_value[0]) == 0) {
      continue;
    }
    file = fopen(argv[i], "r");
    if (file) {
      if ((argc - optind - 1) > 1) cnt_files = 1;
      index_filename = i;
      grepFile(argv, file, flag, optarg_value, cnt_arr, index_filename,
               cnt_files);
      fclose(file);
    } else {
      if (flag.s)
        continue;
      else
        printf("grep: %s: No such file or directory\n", argv[i]);
    }
  }
}

void grepFile(char *argv[], FILE *file, Flags flag, char **optarg_value,
              int cnt_arr, int index_filename, int cnt_files) {
  char *line = NULL;
  size_t len = 0;
  char lastLine = '\n';
  int cnt_match = 0;
  int cnt_line = 0;

  while (getline(&line, &len, file) != EOF) {
    cnt_line++;
    if (!flag.v && !get_result(optarg_value, flag, cnt_arr, line, &cnt_match))
      continue;
    else if (flag.v &&
             get_result(optarg_value, flag, cnt_arr, line, &cnt_match))
      continue;

    if (!flag.c && !flag.l && !flag.n && !cnt_files) printf("%s", line);
    if (flag.n && !flag.c && !flag.l) printf("%d:%s", cnt_line, line);
    if (flag.h && cnt_files) printf("%s", line);
    if (!flag.h && cnt_files) printf("%s:%s", argv[index_filename], line);

    lastLine = line[strlen(line) - 1];
  }

  if (flag.c && !flag.l) printf("%d\n", cnt_match);
  if (flag.l) printf("%s\n", argv[index_filename]);
  if (lastLine != '\n' && !flag.c) printf("\n");

  free(line);
}

int get_result(char **optarg_value, Flags flag, int cnt_arr, char *line,
               int *cnt_match) {
  regex_t preg;
  int cflag = flag.i ? REG_ICASE : 0;
  int res = 0;

  for (int i = 0; i < cnt_arr; i++) {
    if (regcomp(&preg, optarg_value[i], cflag)) {
      printf("failed regex expression\n");
      regfree(&preg);
      exit(1);
    } else {
      if (!regexec(&preg, line, 0, NULL, 0)) {
        (*cnt_match)++;
        res = 1;
        regfree(&preg);
      } else {
        regfree(&preg);
      }
    }
  }
  return res;
}