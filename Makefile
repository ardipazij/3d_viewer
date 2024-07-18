CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
LDFLAGS = -lcheck -lpthread -lm -I /usr/local/include -L/usr/local/lib


CHECK =	$(shell pkg-config --cflags --libs check)
FS = -fsanitize=address -g

SRC	= $(wildcard ./backend/*.c) $(wildcard ./backend/matrix/s21_*.c) 
OBJ	= $(patsubst ./backend/%.c,./backend/%.o, ${SRC})
TARGET = test
LIB = s21_3DViewer_v1.0.a
FILE_TEST =	$(wildcard ./backend/ui_test/s21_*.c)
VG_FLAGS =	--vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

all: dvi dist install

install: uninstall
	@echo "-----------------INSTALLING-------------------"
	@mkdir ./3DViewer
	@cd ./frontend/viewir && qmake && make && make clean && rm Makefile && mv viewir.app ./../../3DViewer/

uninstall:
	@echo "-----------------UNSTALLING-------------------"
	@rm -rf 3DViewer

rebuild: clean uninstall install

dist: install
	@echo "-----------------ARCHIVING-------------------"
	@mkdir -p ../dist
	@cp -R 3DViewer/viewir.app ../dist
	@cp readme/readme.html ../dist 
	@cd ../dist && tar cvzf 3DViewer.tgz *
	@cd ../dist && rm -rf viewir.app readme.html 
	@mv ../dist/3DViewer.tgz .
	@rm -rf ../dist 

dvi:
	@echo "--------------OPEN-README-FILE-----------------"
	@open ./readme/readme.html

open:
	@cd ./3DViewer && open viewir.app

clean:
	@echo "-----------------REMOVING-------------------"
	@rm -f ./backend/*.o ./backend/matrix/*.o
	@rm -f ./*.a ./*.gcda ./*.gcno ./*.info ./*.out ./test
	@rm -rf coverage test.dSYM
	@rm -rf ./3DViewer
	@rm -rf ./3DViewer.tgz

s21_3DViewer_v1.0.a:
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRC)  
	@mv ./s21_matrix.o ./backend/matrix
	@mv ./*.o ./backend
	@ar -rcs $@ $(OBJ)

test: clean s21_3DViewer_v1.0.a
	@echo "-----------------CREATE-TEST------------------"
	@$(CC) $(CFLAGS) -fsanitize=address $(LDFLAGS) --coverage $(FILE_TEST) $(LIB) -o $@ $(CHECK)
	@./$(TARGET)

gcov_report: test
	@echo "--------------CREATE-GCOV-REPORT------------------"
	@$(CC) --coverage $(CFLAGS) $(LDFLAGS) $(FILE_TEST) $(LIB) $(SRC) -o test $(CHECK)
	@./test
	@lcov -t "test" -o tests.info -c -d .
	@genhtml -o coverage tests.info
	@open coverage/index.html

check:
	@clang-format -style=Google -n backend/*.c backend/*.h
	@clang-format -style=Google -n backend/*/*.c 
