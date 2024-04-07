FL = -Werror -Wextra -Wall -std=c11
LFL = -lcheck -lsubunit -lpthread -lm
GCOV = -fprofile-arcs -ftest-coverage

SRC_FILES = $(wildcard *.c) 
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(SRC_FILES:.c=.o)
LIB = s21_matrix.a

all: $(LIB)

$(LIB): $(OBJ_FILES) 
	ar rc $@ $^
	ranlib $(LIB)

%.o: %.c
	gcc $(FL) -c -o $@ $<

gcov_report: 
	make test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info -o coverage_html

test: clean
	make $(LIB)
	gcc $(SRC_FILES) test/test.c $(LIB) -o test/testfile $(FL) $(LFL) $(GCOV)
	test/./testfile

clean:
	rm -f *.o *.gcno *.gcda *.c.gcov *.a *.info math main a.out testfile coverage.info
	rm -f test/*.gcno test/*.gcda test/testfile 
	rm -rf coverage_html

main: 
	gcc $(SRC_FILES)
	./a.out

clang: 
	clang-format -i $(SRC_FILES) $(HEADER_FILES)
	clang-format -i test/test.c

push: 
	git add -A
	git commit -m 'ilyansky'
	git push

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_FILES)