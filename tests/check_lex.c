#include <check.h>

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

Suite *money_suite() {
  Suite *s = suite_create("ENIAC Assembler");
  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_try_to_match_whitespace);
  tcase_add_test(tc_core, test_try_to_match_digit);
  tcase_add_test(tc_core, test_try_to_match_keyword);
  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  int number_failed;
  Suite *s = money_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : CK_FAILURE;
}
