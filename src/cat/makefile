CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: clean

all: s21_cat

s21_cat: s21_cat.o
	$(CC) s21_cat.o -o s21_cat

s21_cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c -o s21_cat.o

test:
	@echo  "\033[0;48;5;175;30mStart of tests\033[0m"
	@(./s21_cat -b test.txt > res_s21.txt) && (cat -b test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "-b:SUCCESS") || echo "-b:WRONG"
	@(./s21_cat -e test.txt > res_s21.txt) && (cat -e test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "-e:SUCCESS") || echo "-e:WRONG"
	@(./s21_cat -n test.txt > res_s21.txt) && (cat -n test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "-n:SUCCESS") || echo "-n:WRONG"
	@(./s21_cat -s test.txt > res_s21.txt) && (cat -s test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "-s:SUCCESS") || echo "-s:WRONG"
	@(./s21_cat -t test.txt > res_s21.txt) && (cat -t test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "-t:SUCCESS") || echo "-t:WRONG"
	@(./s21_cat --number-nonblank test.txt > res_s21.txt) && (cat --number-nonblank test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "--number-nonblank:SUCCESS") || echo "--number-nonblank:WRONG"
	@(./s21_cat --number test.txt > res_s21.txt) && (cat --number test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "--number:SUCCESS") || echo "--number:WRONG"
	@(./s21_cat --squeeze-blank test.txt > res_s21.txt) && (cat --squeeze-blank test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "--squeeze-blank:SUCCESS") || echo "--squeeze-blank:WRONG"
	@(./s21_cat -benstvET test.txt > res_s21.txt) && (cat -benstvET test.txt > res_cat.txt) && (diff res_s21.txt res_cat.txt && echo "-benstvET:SUCCESS") || echo "-benstvET:WRONG"
	@echo "\033[0;48;5;175;30mEnd of tests\033[0m"

rebuild: clean all

clean:
	rm -f s21_cat s21_cat.o res_cat.txt res_s21.txt