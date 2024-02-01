FLAG = -Werror -Wextra -Wall
 
all : string_space_compression

string_space_compression : string_space_compression.o 
	gcc $(FLAG) build/string_space_compression.o -o build/string_space_compression

string_space_compression.o : string_space_compression.c
	gcc $(FLAG) -c string_space_compression.c -o build/string_space_compression.o


clean : 
	rm -rf build/*.o 
	rm -rf build/string_space_compression
	rm -rf a.out

rebuild :
	make clean
	make all

leaks :
	leaks -atExit -- build/string_space_compression

clang: 
	clang-format -i *.c

cpp :
	cppcheck --enable=all --suppress=missingIncludeSystem *.c
