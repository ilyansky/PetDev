INC = -I inc 
FL = -std=c11 -Wall -Wextra -Werror
NCURS = -lncurses

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    CHECKH = $(shell pkg-config --cflags --libs check)
else
    CHECKH = -lcheck -lm -pthread -lrt -lsubunit
endif

GCOV = -fprofile-arcs -ftest-coverage
SRC = brick_game/tetris/logic.c gui/cli/interface.c gui/cli/main.c
TEST_SRC = brick_game/tetris/logic.c gui/cli/interface.c testdir/test.c
DIR = installDir

.PHONY: install uninstall dist dvi test gcov_report

all: clean tetris

install: all
	mkdir -p $(DIR)
	cp tetris $(DIR)

uninstall: 
	rm -rf installDir/
	
tetris: clean
	gcc $(INC) $(SRC) -o tetris $(FL) $(NCURS)
	./tetris

clean: 
	rm -rf project.tar.gz tetris testdir/tests *.gcda *.gcno testdir/*.gcda testdir/*.gcno documentation.md coverage_html/ coverage.info dvi/ dist/ installDir/

test: clean
	gcc $(INC) $(TEST_SRC) -o testdir/tests $(FL) $(NCURS) $(GCOV) $(CHECKH)
	testdir/./tests

gcov_report: 
	make test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info -o coverage_html
	open coverage_html/index.html

# Documentation
dvi:
	mkdir -p dvi/
	touch dvi/documentation.md
	echo "# Documentation" > dvi/documentation.md
	echo "Tetris documentation" >> dvi/documentation.md
	pandoc dvi/documentation.md -o dvi/documentation.pdf --pdf-engine=xelatex

# Make archive
dist: 
	mkdir -p dist
	cp -r brick_game gui inc testdir makefile dist/
	tar -czvf project.tar.gz dist/
	rm -rf dist

clang:
	find . -type f \( -name '*.c' -o -name '*.h' \) | xargs clang-format -i

push:
	make clean
	make clang
	git add -A
	@echo "Enter commit message: " && read msg; \
	git commit -m "$$msg"
	git push

cleanbrew:
	brew autoremove
	brew cleanup
