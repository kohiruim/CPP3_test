CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
TEST_LIBS = -lgtest
TEST_SRC = tests.cc
OBJECTS = test

all: install

install:
	mkdir release;
	cp calcView/* release
	cd release; qmake calcView.pro
	make -C release
	cd release; rm -rf *.h *.cpp *.ui *.o *.pro *.pro.user Makefile

uninstall:
	rm -rf release

dvi:
	open dox/dox.pdf

dist:
	mkdir archive; mkdir archive/src;
	cp -r calcView Makefile dox archive/src
	[ -d release ] && cp -r release archive/src || true
	cp *.c *.h archive/src
	tar czf s21_calc.tgz archive/
	rm -rf archive

test: $(TESTS)
	$(CC) $(CFLAGS) $(TEST_SRC) $(TEST_LIBS) -o $(OBJECTS) -L. --coverage
	./test

gcov_report: test
	$(CC) --coverage $(TEST_SRC) $(TEST_LIBS) -o gсov_report.o
	./gсov_report.o
	lcov --ignore-errors mismatch -t $(OBJECTS) -o s21_calc_tests.info --no-external -c -d .
	genhtml -o report s21_calc_tests.info
	open ./report/index.html

check:
	cp ../materials/linters/.clang-format .
	clang-format -n calcView/*.h calcView/*.cpp
	rm -rf .clang-format

clean: 
	rm -rf test *.gcda  *.gcno *.o *.info report

rebuild: clean all