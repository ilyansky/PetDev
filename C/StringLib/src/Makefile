CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
SRCS= sprintf/s21_sprintf.c special_functions/special_functions.c standard_functions/s21_string.c sscanf/s21_sscanf.c sscanf/s21_func_for_sscanf.c
TEST_SRC= standard_functions/s21_test.c sprintf/s21_test.c sscanf/s21_sscanf_test.c
TEST_FLAGS_LINUX= -lcheck -lm -lsubunit -lpthread
TEST_FLAGS= -lcheck -lm -lpthread
GCOV_FLAGS = -ftest-coverage -fprofile-arcs

all: s21_string.a

s21_string.a:
	$(CC) -c ${SRCS}
	ar rc s21_string.a *.o
	ranlib s21_string.a
	rm *.o

test: rebuild
#	$(CC) ${CFLAGS} -c 
	$(CC) ${CFLAGS} ${TEST_SRC} s21_string.a ${TEST_FLAGS} -o test
	./test
	rm -rf *.o *.a test

test_linux: rebuild
	$(CC) -c ${TEST_SRC}	
	$(CC) *.o s21_string.a ${TEST_FLAGS_LINUX} -o test_linux

gcov_report:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage $(TEST_SRC) $(SRCS) -pthread -lcheck -pthread -lm -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

gcov_report_linux:
	$(CC) ${GCOV_FLAGS} -c ${TEST_SRC}
	$(CC) $(GCOV_FLAGS) *.o $(TEST_FLAGS_LINUX) -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o *.a test test_linux *.gcno *.gcda *.info report

rebuild : clean all