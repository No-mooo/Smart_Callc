#include <check.h>
#include "smart_callc.h"
#define correct 0
#define inCorrect 1
const double esp = 1e-7;

START_TEST(test_1) {
    char *test = "(6/(5-2)*2)=";
    double resul = (6/(5-2)*2);
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_2) {
    char *test = "2*(7+3)^2=";
    double resul = 2*pow(7 + 3, 2);
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_3) {
    char *test = "(6/cos(5-2)*2)=";
    double resul = (6/cos(5-2)*2);
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_4) {
    char *test = "2*5/(-(4+2))=";
    double resul = 2.0*5.0/(-(4.0+2.0));
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_5) {
    char *test = "2+(4)*3=";
    double resul = 2.0+(4.0)*3.0;
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_6) {
    char *test = "5*(-(4+2))=";
    double resul = 5.0*(-(4.0+2.0));
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_7) {
    char *test = "5*(-4)=";
    double resul = 5.0*(-4.0);
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_8) {
    char *test = "+6-4*(+(-4))=";
    double resul = +6.0-4.0*(+(-4.0));
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_9) {
    char *test = "2+(+(-4))=";
    double resul = 2.0+(+(-4.0));
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_10) {
    char *test = "4+(+(-23*2)/33+(-2)*3^(1+2))=";
    double resul = 4.0+(+(-23.0*2.0)/33.0+(-2.0)*powf(3.0, 1.0 + 2.0));
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_11) {
    char *test = "-4+(-4)=";
    double resul = -4.0+(-4.0);
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_12) {
    char *test = "4mod2=";
    double resul = fmod(4, 2);
    ck_assert_double_eq(calculator(test, 4), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_13) {
    double x = 13.0;
    char *test = "x+2=";
    double resul = x + 2;
    ck_assert_double_eq(calculator(test, x), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_14) {
    double x = 6.0;
    char *test = "6modx=";
    double resul = fmod(6, x);
    ck_assert_double_eq(calculator(test, x), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_15) {
    double x = 6.0;
    char *test = "xmodx+tan(0.522)=";
    double resul = fmod(x, x)+tan(0.522);
    ck_assert_double_eq(calculator(test, x), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_16) {
    double x = 2.33;
    char *test = "2+2*atan(33)+3.43*2=";
    double resul = 2.0+2.0*atan(33.0)+3.43*2.0;
    ck_assert_double_eq_tol(calculator(test, x), resul, esp);
    ck_assert_int_eq(check_input_user(test), 0);
}

START_TEST(test_17) {
    double x = 2.33;
    char *test = "(-39*(-20))-asin(0.2)+3.22=";
    double resul = (-39.0*(-20.0))-asin(0.2)+3.22;
    ck_assert_double_eq(calculator(test, x), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_18) {
    double x = 2.33;
    char *test = "22/sqrt(2.33)=";
    double resul = 22.0/sqrt(2.33);
    ck_assert_double_eq(calculator(test, x), resul);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_19) {
    double x = 2.33;
    char *test = "1+2/acos(0.4)+sin(0.43)=";
    double resul = 1.0+2.0/acos(0.4)+sin(0.43);
    ck_assert_double_eq_tol(calculator(test, x), resul, esp);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_20) {
    double x = 2.33;
    char *test = "(4+4)/log(0.3)/2-(-2)*(cos(0.33))=";
    double resul = (4+4)/log10(0.3)/2.0-(-2.0)*(cos(0.33));
    ck_assert_double_eq_tol(calculator(test, x), resul, esp);
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_21) {
    double x = 2.33;
    char *test = "3*ln(0.3)*0.44/2*(-4.2)=";
    double resul = 3*log(0.3)*0.44/2*(-4.2);
    ck_assert_double_eq_tol(calculator(test, x), resul, esp);
    ck_assert_double_eq(check_input_user(test), correct);
}

// test correct value
START_TEST(test_correct_1) {
    char *test = "(4)*()=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_2) {
    char *test = "(5*(()+3))=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_3) {
    char *test = "(5*(()+3))=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_4) {
    char *test = "(/)=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_5) {
    char *test = "(5/)=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_6) {
    char *test = "(5/)=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_7) {
    char *test = "(/(5+5))=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_8) {
    char *test = "x(54+5)=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_9) {
    char *test = "(33*2)x+2=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_10) {
    char *test = "5+(x)-2=";
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_correct_11) {
    char *test = "==4+4";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_12) {
    char *test = "44.3.5+53=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_13) {
    char *test = ".5+5=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_14) {
    char *test = "55+5.5.-=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_15) {
    char *test = "ln(cos(5))=";
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_correct_16) {
    char *test = "2mod3+3+cos(2)=";
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_correct_17) {
    char *test = "-(2)";
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_correct_18) {
    char *test = "3+mod4=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_19) {
    char *test = "(5+5)mod(6+5)=";
    ck_assert_double_eq(check_input_user(test), correct);
}

START_TEST(test_correct_20) {
    char *test = "4mod2(5+5)=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

START_TEST(test_correct_21) {
    char *test = "(4)+x+(6)+=";
    ck_assert_double_eq(check_input_user(test), inCorrect);
}

int main() {
    Suite *s1 = suite_create("Suite");
    SRunner *sr = srunner_create(s1);
    int nf;

    TCase *tc1_1 = tcase_create("tests");
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, test_1);
    tcase_add_test(tc1_1, test_2);
    tcase_add_test(tc1_1, test_3);
    tcase_add_test(tc1_1, test_4);
    tcase_add_test(tc1_1, test_5);
    tcase_add_test(tc1_1, test_6);
    tcase_add_test(tc1_1, test_7);
    tcase_add_test(tc1_1, test_8);
    tcase_add_test(tc1_1, test_9);
    tcase_add_test(tc1_1, test_10);
    tcase_add_test(tc1_1, test_11);
    tcase_add_test(tc1_1, test_12);
    tcase_add_test(tc1_1, test_13);
    tcase_add_test(tc1_1, test_14);
    tcase_add_test(tc1_1, test_15);
    tcase_add_test(tc1_1, test_16);
    tcase_add_test(tc1_1, test_17);
    tcase_add_test(tc1_1, test_18);
    tcase_add_test(tc1_1, test_19);
    tcase_add_test(tc1_1, test_20);
    tcase_add_test(tc1_1, test_21);

    // test correct value
    tcase_add_test(tc1_1, test_correct_1);
    tcase_add_test(tc1_1, test_correct_2);
    tcase_add_test(tc1_1, test_correct_3);
    tcase_add_test(tc1_1, test_correct_4);
    tcase_add_test(tc1_1, test_correct_5);
    tcase_add_test(tc1_1, test_correct_6);
    tcase_add_test(tc1_1, test_correct_7);
    tcase_add_test(tc1_1, test_correct_8);
    tcase_add_test(tc1_1, test_correct_9);
    tcase_add_test(tc1_1, test_correct_10);
    tcase_add_test(tc1_1, test_correct_11);
    tcase_add_test(tc1_1, test_correct_12);
    tcase_add_test(tc1_1, test_correct_13);
    tcase_add_test(tc1_1, test_correct_14);
    tcase_add_test(tc1_1, test_correct_15);
    tcase_add_test(tc1_1, test_correct_16);
    tcase_add_test(tc1_1, test_correct_17);
    tcase_add_test(tc1_1, test_correct_18);
    tcase_add_test(tc1_1, test_correct_19);
    tcase_add_test(tc1_1, test_correct_20);
    tcase_add_test(tc1_1, test_correct_21);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
