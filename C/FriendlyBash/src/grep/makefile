################
### Building ###
################

FLAGS = -Werror -Wextra -Wall

all : s21_grep test

s21_grep : s21_grep.o grep.o
	gcc $(FLAGS) s21_grep.o grep.o -o s21_grep

s21_grep.o : s21_grep.c
	gcc -c $(FLAGS) s21_grep.c -o s21_grep.o

grep.o : grep.c
	gcc -c $(FLAGS) grep.c -o grep.o
 
test : test.o
	gcc $(FLAGS) test.o -o test

test.o : test.c 
	gcc -c $(FLAGS) test.c -o test.o  
 
###############
### Support ###
###############

clean :
	rm *.o
	rm s21_grep
	rm test
	rm custom_output.txt
	rm expected_output.txt


clang : 
	clang-format -i *.c *.h

leaks :
	leaks -atExit -- ./s21_grep -i fLaG test_grep.txt

cpp :
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

push : 
	git add .
	git commit -m 'in developing'
	git push
