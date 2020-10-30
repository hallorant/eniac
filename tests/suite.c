#include <check.h>

#include "check_lex.h"

int main() {
  int number_failed;
  Suite *s = suite_create("ENIAC Assembler Test Suite");
  suite_add_tcase(s, lex_tcase());
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : CK_FAILURE;
}