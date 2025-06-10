CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: clean

all: s21_grep

s21_grep: s21_grep.o
	$(CC) s21_grep.o -o s21_grep

s21_grep.o: s21_grep.c
	$(CC) $(CFLAGS) -c s21_grep.c -o s21_grep.o

test:
	@echo  "\033[0;48;5;175;30mStart of tests\033[0m"
	@(./s21_grep -e test test.txt > res_s21.txt) && (grep -e test test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-e:SUCCESS") || echo "-e:WRONG"
	@(./s21_grep -i TEST test.txt > res_s21.txt) && (grep -i TEST test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-i:SUCCESS") || echo "-i:WRONG"
	@(./s21_grep -v test test.txt > res_s21.txt) && (grep -v test test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-v:SUCCESS") || echo "-v:WRONG"
	@(./s21_grep -c test test.txt > res_s21.txt) && (grep -c test test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-c:SUCCESS") || echo "-c:WRONG"
	@(./s21_grep -l test test.txt > res_s21.txt) && (grep -l test test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-l:SUCCESS") || echo "-l:WRONG"
	@(./s21_grep -n test test.txt > res_s21.txt) && (grep -n test test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-n:SUCCESS") || echo "-n:WRONG"
	@(./s21_grep -h test test.txt test.txt > res_s21.txt) && (grep -h test test.txt test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-h:SUCCESS") || echo "-h:WRONG"
	@(./s21_grep -s test test.txt > res_s21.txt) && (grep -s test test.txt > res_grep.txt) && (diff res_s21.txt res_grep.txt && echo "-s:SUCCESS") || echo "-s:WRONG"
	@echo "\033[0;48;5;175;30mEnd of tests\033[0m"


rebuild: clean all

clean:
	rm -f s21_grep s21_grep.o res_grep.txt res_s21.txt