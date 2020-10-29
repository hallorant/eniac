#include <check.h>

#include "../src/lex.h"

START_TEST(test_match_keyword) {
  int index = 0;
  ck_assert_int_eq(match_keyword("foo", "foobar", &index), true);
  ck_assert_int_eq(index, 3);
}
END_TEST

Suite *money_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("ENIAC Assembler");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_match_keyword);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = money_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : CK_FAILURE;
}
