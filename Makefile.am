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
easm_LDFLAGS = -static

TESTS = tests/suite
check_PROGRAMS = tests/suite

tests_suite_SOURCES = \
	tests/check_lex.c \
	tests/check_lex.h \
	tests/suite.c
tests_suite_LDFLAGS = -static
tests_suite_CFLAGS = @CHECK_CFLAGS@
tests_suite_LDADD = libeasm.la @CHECK_LIBS@
