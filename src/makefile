TEST = all_tests
HEADER = s21_matrix.h

OBJ = $(patsubst %.c, %.o, $(SRC) $(SRC))
OBJ_TEST = $(patsubst %.c, %.o, $(SRC_TEST))
COVER_GCNO = $(patsubst %.o, %.gcno, $(OBJ) $(OBJ_TEST))
COVER_GCDA = $(patsubst %.o, %.gcda, $(OBJ) $(OBJ_TEST))
CC = gcc
SRC = s21_matrix.c	
SRC_TEST = s21_matrix_tests.c
CFLAGS := -Wall -Werror -Wextra -std=c11
LINUX_FLAGS = -lsubunit -lrt -lpthread -lm
LIB_FLAGS = -lcheck

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIB_FLAGS += $(LINUX_FLAGS)
endif

.PHONY: all, clean, test, s21_matrix.a, gcov_report

all: clean s21_matrix.a test

s21_matrix.a: $(OBJ)
	ar rcs s21_matrix.a $?
	ranlib s21_matrix.a

%.o: %.c $(HEADER)
	$(CC) $(СFLAGS) -c $< -o $@ $(LIB_FLAGS)

test:
	$(CC) $(CFLAGS) -g $(SRC) $(SPRINTF_SRC) $(SRC_TEST) -o all_tests $(LIB_FLAGS) --coverage
	@echo "---------------------------TESTS--------------------------------------"
	@./$(TEST)
	@echo "----------------------------------------------------------------------"

gcov_report: test 
	lcov -t "$(TEST)" -o $(TEST).info -c -d .	
	genhtml -o report $(TEST).info 

check:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@echo "=====================CPPCHECK====================="
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@echo "=======================STYLE======================="
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	@echo "=======================LEAKS======================="
	CK_FORK=no leaks -atExit -- ./all_tests


clean:
	@rm -rf $(OBJ) $(COVER_GCNO) $(OBJ_TEST) $(COVER_GCDA) s21_matrix.a *.info *.cfg
	@rm -rf $(TEST) report
