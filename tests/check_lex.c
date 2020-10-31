#include "check_lex.h"

#include "../src/lex.h"

START_TEST(test_try_to_match_whitespace) {
  int index;

  index = 0;
  ck_assert(try_to_match_whitespace(" ", &index));
  ck_assert_int_eq(index, 1);
  index = 0;
  ck_assert(try_to_match_whitespace("\t", &index));
  ck_assert_int_eq(index, 1);
  index = 0;
  ck_assert(!try_to_match_whitespace("", &index));
  ck_assert_int_eq(index, 0);
  index = 2;
  ck_assert(try_to_match_whitespace(" ; ", &index));
  ck_assert_int_eq(index, 3);
  index = 1;
  ck_assert(!try_to_match_whitespace(" ; ", &index));
  ck_assert_int_eq(index, 1);
  index = 2;
  ck_assert(try_to_match_whitespace("Rd\t\t\tPr", &index));
  ck_assert_int_eq(index, 5);
  index = 2;
  ck_assert(try_to_match_whitespace("Rd\t\t\t", &index));
  ck_assert_int_eq(index, 5);
  index = 2;
  ck_assert(!try_to_match_whitespace("RdPr", &index));
  ck_assert_int_eq(index, 2);
}
END_TEST

START_TEST(test_try_to_match_digit) {
  int index;
  int digit;

  index = 0;
  ck_assert(try_to_match_digit("5", &index, &digit));
  ck_assert_int_eq(index, 1);
  ck_assert_int_eq(digit, 5);
  index = 1;
  ck_assert(try_to_match_digit("50", &index, &digit));
  ck_assert_int_eq(index, 2);
  ck_assert_int_eq(digit, 0);
  index = 0;
  ck_assert(!try_to_match_digit("*", &index, &digit));
  ck_assert_int_eq(index, 0);
  index = 2;
  ck_assert(!try_to_match_digit("50*", &index, &digit));
  ck_assert_int_eq(index, 2);
  index = 0;
  ck_assert(!try_to_match_digit(" 5", &index, &digit));
  ck_assert_int_eq(index, 0);
}
END_TEST

START_TEST(test_try_to_match_keyword) {
  int index;

  index = 0;
  ck_assert(!try_to_match_keyword("", &index, "Rd"));
  ck_assert_int_eq(index, 0);
  index = 0;
  ck_assert(try_to_match_keyword("RdPr", &index, "Rd"));
  ck_assert_int_eq(index, 2);
  index = 0;
  ck_assert(try_to_match_keyword("rdpr", &index, "Rd"));
  ck_assert_int_eq(index, 2);
  index = 0;
  ck_assert(!try_to_match_keyword("RdPr", &index, "Pr"));
  ck_assert_int_eq(index, 0);
  index = 2;
  ck_assert(try_to_match_keyword("RdPr", &index, "Pr"));
  ck_assert_int_eq(index, 4);
  index = 2;
  ck_assert(try_to_match_keyword("RDPR", &index, "Pr"));
  ck_assert_int_eq(index, 4);
  index = 2;
  ck_assert(try_to_match_keyword("Rd;Pr", &index, ";"));
  ck_assert_int_eq(index, 3);
  index = 2;
  ck_assert(!try_to_match_keyword("Rd", &index, "Pr"));
  ck_assert_int_eq(index, 2);
}
END_TEST

START_TEST(test_try_to_match_label) {
  int index;
  char label[10];

  index = 0;
  ck_assert(try_to_match_label("label", &index, label, 10));
  ck_assert_int_eq(index, 5);
  ck_assert_str_eq(label, "label");
  index = 2;
  ck_assert(try_to_match_label("label", &index, label, 10));
  ck_assert_int_eq(index, 5);
  ck_assert_str_eq(label, "bel");
  index = 0;
  ck_assert(!try_to_match_label("label", &index, label, 1));
  ck_assert_int_eq(index, 0);
  index = 0;
  ck_assert(!try_to_match_label(" label", &index, label, 10));
  ck_assert_int_eq(index, 0);
  index = 2;
  ck_assert(try_to_match_label("  b12_c12(", &index, label, 10));
  ck_assert_int_eq(index, 9);
  ck_assert_str_eq(label, "b12_c12");
  index = 2;
  ck_assert(try_to_match_label("  _c12(", &index, label, 10));
  ck_assert_int_eq(index, 6);
  ck_assert_str_eq(label, "_c12");
  index = 0;
  ck_assert(!try_to_match_label("label", &index, label, 3));
  ck_assert_int_eq(index, 0);
  index = 0;
  ck_assert(!try_to_match_label("label", &index, label, 5));
  ck_assert_int_eq(index, 0);
}
END_TEST

START_TEST(test_try_to_match_label_decl) {
  int index;
  char label[10];

  index = 0;
  ck_assert(try_to_match_label_decl("label:", &index, label, 10));
  ck_assert_int_eq(index, 6);
  ck_assert_str_eq(label, "label");
  index = 0;
  ck_assert(!try_to_match_label_decl("label", &index, label, 10));
  ck_assert_int_eq(index, 0);
  index = 2;
  ck_assert(try_to_match_label_decl("label:", &index, label, 10));
  ck_assert_int_eq(index, 6);
  ck_assert_str_eq(label, "bel");
  index = 0;
  ck_assert(!try_to_match_label_decl("label", &index, label, 1));
  ck_assert_int_eq(index, 0);
  index = 0;
  ck_assert(!try_to_match_label_decl(" label", &index, label, 10));
  ck_assert_int_eq(index, 0);
  index = 2;
  ck_assert(try_to_match_label_decl("  b12_c12:(", &index, label, 10));
  ck_assert_int_eq(index, 10);
  ck_assert_str_eq(label, "b12_c12");
  index = 2;
  ck_assert(try_to_match_label_decl("  _c12:(", &index, label, 10));
  ck_assert_int_eq(index, 7);
  ck_assert_str_eq(label, "_c12");
  index = 0;
  ck_assert(!try_to_match_label_decl("label", &index, label, 3));
  ck_assert_int_eq(index, 0);
  index = 0;
  ck_assert(!try_to_match_label_decl("label", &index, label, 5));
  ck_assert_int_eq(index, 0);
}
END_TEST

START_TEST(test_try_to_match_eol) {
  int index;
  char label[10];

  index = 3;
  ck_assert(try_to_match_eol("\tRd", &index));
  ck_assert_int_eq(index, 3);
  index = 3;
  ck_assert(try_to_match_eol("\tRd ", &index));
  ck_assert_int_eq(index, 4);
  index = 0;
  ck_assert(try_to_match_eol("\t\t; a comment", &index));
  ck_assert_int_eq(index, 13);
  index = 0;
  ck_assert(try_to_match_eol("\t\t* a comment", &index));
  ck_assert_int_eq(index, 13);
  index = 0;
  ck_assert(try_to_match_eol("\t\t# a comment", &index));
  ck_assert_int_eq(index, 13);
  index = 2;
  ck_assert(try_to_match_eol("\t\t; a comment", &index));
  ck_assert_int_eq(index, 13);
  index = 2;
  ck_assert(try_to_match_eol("\t\t* a comment", &index));
  ck_assert_int_eq(index, 13);
  index = 2;
  ck_assert(try_to_match_eol("\t\t# a comment", &index));
  ck_assert_int_eq(index, 13);
  index = 0;
  ck_assert(!try_to_match_eol(" Rd\t; next punched card", &index));
  ck_assert_int_eq(index, 0);
}
END_TEST

TCase *lex_tcase() {
  TCase *tc = tcase_create("lex - lexical analysis");
  tcase_add_test(tc, test_try_to_match_whitespace);
  tcase_add_test(tc, test_try_to_match_digit);
  tcase_add_test(tc, test_try_to_match_keyword);
  tcase_add_test(tc, test_try_to_match_label);
  tcase_add_test(tc, test_try_to_match_label_decl);
  tcase_add_test(tc, test_try_to_match_eol);
  return tc;
}
