ACLOCAL_AMFLAGS = -I m4
bin_PROGRAMS = easm
easm_SOURCES = \
	src/easm.c \
	src/log.c \
	src/log.h

TESTS = tests/check_lex
check_PROGRAMS = tests/check_lex

tests_check_lex_SOURCES = \
	tests/check_lex.c \
	src/lex.c
tests_check_lex_CFLAGS = @CHECK_CFLAGS@
tests_check_lex_LDADD = @CHECK_LIBS@

