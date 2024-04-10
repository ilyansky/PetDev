FL = -Werror -Wextra -Wall -std=c++17
LIBFL = -pthread
TFL = -lgtest -lgtest_main

LIB = s21_matrix_oop.a
SRC_FILES = $(wildcard *.cpp)
HEADER_FILES = $(wildcard *.h)
OBJ_FILES = $(SRC_FILES:.cpp=.o)

all: $(LIB)

$(LIB): $(OBJ_FILES)
	ar rcs $@ $^

%.o: %.cpp
	g++ $(FL) $(LIBFL) -c -o $@ $<

test:
	g++ $(FL) $(TFL) $(SRC_FILES) -o testfile
	./testfile

clang:
	clang-format -i *.cpp
	clang-format -i *.h

clean:
	rm -f *.a a.out *.o testfile

leak:
	make test
	leaks -atExit -- ./testfile

push:
	make clean
	make clang
	git add -A
	git commit -m "ilyansky"
	git push

mainclang:
	clang $(SRC_FILES)
	./a.out

