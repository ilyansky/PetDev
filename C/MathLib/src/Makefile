FL = -Werror -Wextra -Wall
LFL = -lcheck -lsubunit -lpthread -lm
GCOV = -fprofile-arcs -ftest-coverage

all: clean

s21_math.a: s21_math.c
	gcc -c $(FLAGS) s21_math.c -o s21_math.o
	ar rc s21_math.a s21_math.o
	ranlib s21_math.a
	
test: test.c s21_math.c
	gcc test.c s21_math.c s21_math.a -o test $(FL) $(LFL)

gcov_report: test.c s21_math.c 
	gcc $(FL) test.c s21_math.c -o test $(LFL) $(GCOV)
	./test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info -o coverage_html

clean:
	rm -rf *.o *.gcno *.gcda *.c.gcov *.a *.info math test main a.out coverage_html

clang: 
	clang-format -i *.c *.h

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

push: 
	git add .
	git commit -m 'in developing'
	git push



