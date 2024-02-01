FLAG = -Werror -Wextra -Wall
 
all : stepik

stepik : spiral_matrix_fill.o 
	gcc $(FLAG) build/spiral_matrix_fill.o -o build/spiral_matrix_fill

spiral_matrix_fill.o : spiral_matrix_fill.c
	gcc $(FLAG) -c spiral_matrix_fill.c -o build/spiral_matrix_fill.o


clean : 
	rm -rf build/*.o 
	rm -rf build/spiral_matrix_fill
	rm -rf a.out

rebuild :
	make clean
	make all

leaks :
	leaks -atExit -- build/spiral_matrix_fill

clang: 
	clang-format -i *.c

cpp :
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
