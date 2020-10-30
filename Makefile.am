ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libeasm.la
include_HEADERS = \
	src/log.h \
	src/lex.h
libeasm_la_SOURCES = \
	src/log.c \
	src/lex.c

bin_PROGRAMS = easm
easm_SOURCES = src/easm.c
easm_LDADD = libeasm.la

TESTS = tests/check_lex
check_PROGRAMS = tests/check_lex

tests_check_lex_SOURCES = \
	tests/check_lex.c
tests_check_lex_CFLAGS = @CHECK_CFLAGS@
tests_check_lex_LDADD = libeasm.la @CHECK_LIBS@

