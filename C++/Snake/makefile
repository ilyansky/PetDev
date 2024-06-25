all: snake

# --------------------------------------------
# COMMON 

INC = -I inc
FL = -std=c++17
CFL = -std=c11
COMMON = $(INC) $(FL)
CPP = g++

# END COMMON
# --------------------------------------------






# --------------------------------------------
# DESKTOP SNAKE 

DESK_SNAKE_SRC = desktopSnake/deskSnakeMain.cpp \
desktopSnake/deskSnakeController.cpp \
desktopSnake/deskSnakeModel.cpp \
desktopSnake/deskSnakeView.cpp
QT_DIR = /opt/homebrew/Cellar/qt/6.7.0_1
QT_INC = -I/$(shell find $(QT_DIR) -type d -name Headers -exec echo -I{} \;)
QT_LIB = -F$(QT_DIR)/lib -framework QtWidgets -framework QtGui -framework QtCore
QT = $(QT_LIB) $(QT_INC)
DESK_SNAKE = $(QT) $(DESK_SNAKE_SRC) $(COMMON)

snake: clean
	$(CPP) $(DESK_SNAKE) -o snake 
	./snake

# END DESKTOP SNAKE
# --------------------------------------------





# --------------------------------------------
# TERMINAL SNAKE 

TERM_SNAKE_SRC = terminalSnake/termSnakeMain.cpp \
terminalSnake/termSnakeLogic.cpp \
terminalSnake/termSnakeView.cpp
NCURS_FL = -lncurses
TERM_SNAKE = $(TERM_SNAKE_SRC) $(NCURS_FL)  $(COMMON)

tsnake: clean
	$(CPP) $(TERM_SNAKE) -o tsnake
	./tsnake

# END TERMINAL SNAKE
# --------------------------------------------





# --------------------------------------------
# ANOTHER AIMS

install: all
	mkdir -p installDir/
	cp snake installDir/
	rm snake

uninstall:
	make clean

dvi: clean
	mkdir -p dvi/
	touch dvi/documentation.md
	echo "# Documentation" > dvi/documentation.md
	echo "Snake documentation" >> dvi/documentation.md
	pandoc dvi/documentation.md -o dvi/documentation.pdf --pdf-engine=xelatex

dist: clean
	mkdir -p dist
	cp -r brick_game gui inc testdir makefile dist/
	tar -czvf project.tar.gz dist/
	rm -rf dist

push:
	make clean
	make clang
	git add -A
	@echo "Enter commit message: " && read msg; \
	git commit -m "$$msg"
	git push

clang:
	find . -type f \( -name '*.c' -o -name '*.h' \) | xargs clang-format -i

clean: 
	rm -rf snake tsnake installDir/ project.tar.gz dist/ dvi/

cleanbrew:
	brew autoremove
	brew cleanup

.PHONY: install uninstall dist dvi

# END ANOTHER AIMS
# --------------------------------------------
