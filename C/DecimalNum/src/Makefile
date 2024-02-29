FL = -Werror -Wextra -Wall -std=c11
LFL = -lcheck -lsubunit -lpthread -lm
GCOV = -fprofile-arcs -ftest-coverage

SRC_FILES = $(wildcard *.c) 
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(SRC_FILES:.c=.o)

all: s21_decimal.a

s21_decimal.a: $(OBJ_FILES) 
	ar rc $@ $^
	ranlib s21_decimal.a

%.o: %.c
	gcc $(FL) -c -o $@ $<

gcov_report: 
	make test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info -o coverage_html

test: clean
	make s21_decimal.a
	gcc $(SRC_FILES) test/test.c s21_decimal.a -o testfile $(FL) $(LFL) $(GCOV)
	./testfile

clean:
	rm -rf *.o *.gcno *.gcda *.c.gcov *.a *.info math main a.out testfile coverage_html

main: 
	gcc $(SRC_FILES)
	./a.out

clang: 
	clang-format -i $(SRC_FILES) $(HEADER_FILES)
	clang-format -i test/test.c

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_FILES)

push: 
	git add -A
	git commit -m 'wannabepurple'
	git push