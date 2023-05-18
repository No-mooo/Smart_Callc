#ifndef SRC_SMART_CALLC_SMART_CALLC_H_
#define SRC_SMART_CALLC_SMART_CALLC_H_

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double calculator(char *text, double x);

typedef struct stack_number {
    double value;

    struct stack_number *next;
    struct stack_number *before;
} stack_number;

typedef struct stack_operand {
    char value[20];
    int priority;

    struct stack_operand *next;
    struct stack_operand *before;
} stack_operand;

typedef struct input_user {
    char *text;
    int i;
    int check_next_element;
    int check_before_element;
    char *list_operand;
} input_user;

void operand_func(stack_number **end_stack_number, stack_operand **end_stack_operand, char *text, int *i);
void push_number(stack_number **end, double i);
int get_priority(char *text);
void push_operand(stack_operand **end, char *text);
void counting_operand(stack_number **end_stack_number, stack_operand **end_stack_operand);
void del_struct_operand(stack_operand **end);
void del_struct_number(stack_number **end);
void check_unar_minus(stack_number **end_stack_number, stack_operand **end_stack_operand, const char *text,
const int *i);
void check_x(stack_number **end_stack_number, char *text, int *i, double x);
void check_unar_plus(const char *text, int *i);
int check_input_user(char *text);
int check_input_1(input_user save_struct, int *open_bracket);
int check_input_2(input_user save_struct);
int check_input_3(input_user save_struct);
int check_input_4(input_user save_struct);
int check_input_5(input_user save_struct);
int check_input_6(input_user save_struct);
int check_input_7(char *text);
int check_input_8(char *text);
#endif  // SRC_SMART_CALLC_SMART_CALLC_H_
