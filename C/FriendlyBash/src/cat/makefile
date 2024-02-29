################
### Building ###
################

FLAGS = -Werror -Wextra -Wall
 
all : s21_cat test

s21_cat: s21_cat.o cat.o
	gcc $(FLAGS) s21_cat.o cat.o -o s21_cat

s21_cat.o: s21_cat.c
	gcc -c $(FLAGS) s21_cat.c -o s21_cat.o

cat.o : cat.c
	gcc -c $(FLAGS) cat.c -o cat.o

test : test_cat.o
	gcc $(FLAGS) test_cat.o -o test

test_cat.o : test_cat.c 
	gcc -c $(FLAGS) test_cat.c -o test_cat.o 

###############
### Support ###
###############

clean :
	rm *.o
	rm s21_cat
	rm test
	rm custom_output.txt
	rm expected_output.txt

clang : 
	clang-format -i *.c *.h 
	
leaks :
	leaks -atExit -- ./s21_cat -be -nst test_cat.c

cpp :
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

push : 
	git add .
	git commit -m 'in developing'
	git push
