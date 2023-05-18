#include "smart_callc.h"
// удалить makefile

// int main() {
//     // char *test = "1+2/acos(0.4)=";
//     // double resul = 1.0+2.0/acos(0.4);

//     //     printf("or == %f // my %f", resul, calculator(test, 10));

//     // if (check_input_user(test3) == 1) {
//     //     printf("\n%s\n", "error");

//     // } else {
//     //     printf("\n%s\n", "good");
//     // }



//     return 0;
// }

double calculator(char *text, double x) {
    double resul;
    stack_number stack_number_start = {0, NULL, NULL};
    stack_number *end_stack_number = &stack_number_start;
    stack_operand stack_operand_start = {" ", 0, NULL, NULL};
    stack_operand *end_stack_operand = &stack_operand_start;
    end_stack_operand->next = end_stack_operand;
    end_stack_number->next = end_stack_number;

    int i = 0;
    while (i < (int)strlen(text)) {
        if (text[i] >= 48 && text[i] <= 57) {
            char *push_value = (char*) malloc(1 * sizeof(char));
            int size_value = 1;
            // для цифр и точек
            while (i < (int)strlen(text) && ((text[i] >= 48 && text[i] <= 57) || text[i] == '.')) {
                push_value[size_value - 1] = text[i];
                i++;
                size_value++;
                char *new_str = (char*) realloc(push_value, size_value * sizeof(char));
                while (!new_str) new_str = (char*) realloc(push_value, size_value * sizeof(char));
                push_value = new_str;
                push_value[size_value - 1] = '\0';  // странная херрня
            }

            push_number(&end_stack_number, atof(push_value));
            free(push_value);
        }

        check_x(&end_stack_number, text, &i, x);
        check_unar_plus(text, &i);

        if (text[i] < 48 || text[i] > 57) {
            operand_func(&end_stack_number, &end_stack_operand, text, &i);
        }
    }

    resul = end_stack_number->value;
    return resul;
}

void operand_func(stack_number **end_stack_number, stack_operand **end_stack_operand, char *text, int *i) {
    char *push_value = (char*) malloc(1 * sizeof(char));
    int size_value = 1;
    // для текста и операндов
    do {
        if (text[*i] == 'x') break;
        push_value[size_value - 1] = text[*i];
        *i = *i + 1;
        size_value++;
        char *new_str = (char*) realloc(push_value, size_value * sizeof(char));
        while (!new_str) new_str = (char*) realloc(push_value, size_value * sizeof(char));
        push_value = new_str;
        push_value[size_value - 1] = '\0';
    } while (*i < (int)strlen(text) && (text[*i] >= 97 && text[*i] <= 122) && (text[*i - 1] >= 97 && text[*i
    - 1] <= 122));

    push_operand(end_stack_operand, push_value);
    check_unar_minus(end_stack_number, end_stack_operand, text, i);

    if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
    (*end_stack_operand)->priority) {
        if (!strstr((*end_stack_operand)->value, "(")) {
            counting_operand(end_stack_number, end_stack_operand);
        }

        if (strstr((*end_stack_operand)->value, "=")) {
            while ((*end_stack_operand)->before != NULL) {
                snprintf((*end_stack_operand)->value, strlen("END") + 1, "%s", "END");
                counting_operand(end_stack_number, end_stack_operand);
            }
        }
    }

    free(push_value);
}

void counting_operand(stack_number **end_stack_number, stack_operand **end_stack_operand) {
    if (strstr((*end_stack_operand)->before->value, "+")) {
        (*end_stack_number)->before->value += (*end_stack_number)->value;
        del_struct_number(end_stack_number);
        del_struct_operand(end_stack_operand);

    } else if (strstr((*end_stack_operand)->before->value, "-")) {
        (*end_stack_number)->before->value -= (*end_stack_number)->value;
        del_struct_number(end_stack_number);
        del_struct_operand(end_stack_operand);

    } else if (strstr((*end_stack_operand)->before->value, "*")) {
        // для - * -
        if ((*end_stack_operand)->before->before != NULL) {
            if (strstr((*end_stack_operand)->before->before->value, "-")) {
                (*end_stack_number)->before->value *= -1;
                snprintf((*end_stack_operand)->before->before->value, strlen("+") + 1, "%s", "+");
            }
        }

        (*end_stack_number)->before->value *= (*end_stack_number)->value;
        del_struct_number(end_stack_number);
        del_struct_operand(end_stack_operand);

    } else if (strstr((*end_stack_operand)->before->value, "/")) {
        (*end_stack_number)->before->value /= (*end_stack_number)->value;
        del_struct_number(end_stack_number);
        del_struct_operand(end_stack_operand);

    } else if (strstr((*end_stack_operand)->before->value, ")")) {
        del_struct_operand(end_stack_operand);

        while (!strstr((*end_stack_operand)->before->value, "(")) {
            counting_operand(end_stack_number, end_stack_operand);
        }

        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "ln")) {
        (*end_stack_number)->value = log((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "acos")) {
        (*end_stack_number)->value = acos((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "sqrt")) {
        (*end_stack_number)->value = sqrt((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "atan")) {
        (*end_stack_number)->value = atan((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "log")) {
        (*end_stack_number)->value = log10((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "asin")) {
        (*end_stack_number)->value = asin((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "mod")) {
        double before_num = (*end_stack_number)->before->value;
        double end_num = (*end_stack_number)->value;
        (*end_stack_number)->before->value = fmod(before_num, end_num);
        del_struct_number(end_stack_number);
        del_struct_operand(end_stack_operand);

    } else if (strstr((*end_stack_operand)->before->value, "sin")) {
        (*end_stack_number)->value = sin((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "tan")) {
        (*end_stack_number)->value = tan((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "cos")) {
        (*end_stack_number)->value = cos((*end_stack_number)->value);
        del_struct_operand(end_stack_operand);

        if ((*end_stack_operand)->before != NULL && (*end_stack_operand)->before->priority >=
        (*end_stack_operand)->priority) {
            counting_operand(end_stack_number, end_stack_operand);
        }

    } else if (strstr((*end_stack_operand)->before->value, "^")) {
        (*end_stack_number)->before->value = pow((*end_stack_number)->before->value,
        (*end_stack_number)->value);
        del_struct_number(end_stack_number);
        del_struct_operand(end_stack_operand);
    }
}

void check_x(stack_number **end_stack_number, char *text, int *i, double x) {
    if (text[*i] == 'x') {
        int check = 0;

        if (*i == 0 || (*i - 1 >= 0 && (text[*i - 1] < 97 || text[*i - 1] > 122))) check++;
        if (*i + 1 < (int)strlen(text) && (text[*i + 1] < 97 || text[*i + 1] > 122)) check++;

        if (check) {
            push_number(end_stack_number, x);
            *i = *i + 1;
        }
    }
}

void check_unar_plus(const char *text, int *i) {
    if (text[*i] == '+') {
        if ((*i - 1 >= 0 && text[*i - 1] == '(') || *i == 0) *i = *i + 1;
    }
}

void check_unar_minus(stack_number **end_stack_number, stack_operand **end_stack_operand, const char *text,
const int *i) {
    if (strstr((*end_stack_operand)->value, "-")) {
        int check = 0;
        if ((*end_stack_number)->next != NULL) check++;
        if (*i - 2 >= 0 && text[*i - 2] == '(') check++;

        if (check) {
            push_number(end_stack_number, atof("-1"));
            snprintf((*end_stack_operand)->value, strlen("*") + 1, "%s", "*");
        }
    }
}

void del_struct_number(stack_number **end) {
    if ((*end)->before != NULL) {
        stack_number *save_end_number = *end;
        (*end) = (*end)->before;
        (*end)->next = NULL;
        save_end_number->next = NULL;
        save_end_number->before = NULL;

        free(save_end_number);
    }
}

void del_struct_operand(stack_operand **end) {
    if ((*end)->before != NULL) {
        stack_operand *save_end_operand = *end;

        (*end) = (*end)->before;
        (*end)->next = NULL;
        // strcpy((*end)->value, (*save_end_operand).value); // треш с присвоениями
        snprintf((*end)->value, strlen((*save_end_operand).value) + 1, "%s", (*save_end_operand).value);
        (*end)->priority = save_end_operand->priority;

        save_end_operand->next = NULL;
        save_end_operand->before = NULL;
        free(save_end_operand);
    }
}

void push_number(stack_number **end, double i) {
    if ((*end)->next != NULL) {
        (*end)->value = i;
        (*end)->next = NULL;

    } else {
        stack_number *new = (stack_number*) malloc(sizeof(stack_number));
        new->next = NULL;
        new->value = i;
        (*new).before = (*end);
        (*end)->next = new;
        (*end) = new;
    }
}

void push_operand(stack_operand **end, char *text) {
    if ((*end)->next != NULL) {
        snprintf((*end)->value, strlen(text) + 1, "%s", text);
        (*end)->next = NULL;
        (*end)->priority = get_priority(text);

    } else {
        stack_operand *new = (stack_operand*) malloc(sizeof(stack_operand));
        new->next = NULL;
        snprintf(new->value, strlen(text) + 1, "%s", text);
        (*new).before = (*end);
        (*end)->next = new;
        (*end) = new;
        (*end)->priority = get_priority((*end)->value);
    }
}

int get_priority(char *text) {
    char list_priority[5][100] = {"(=", "-+", "*/", "^", "cos sin tan acos asin atan sqrt ln log mod )"};
    int resul = 0;

    for (int i = 0; i < 5; i++) {
        if (strstr(list_priority[i], text)) resul = i + 1;
    }

    return resul;
}

int check_input_user(char *text) {
    int error = 0;
    input_user input_user;
    int open_bracket = 0;
    input_user.text = text;
    input_user.list_operand = "=-+*/^";

    for (int i = 0; i < (int)strlen(text) && !error; i++) {
        input_user.i = i;
        input_user.check_next_element = 0;
        input_user.check_before_element = 0;
        if (i + 1 < (int)strlen(text)) input_user.check_next_element = 1;
        if (i - 1 >= 0) input_user.check_before_element = 1;

        if (!error && check_input_1(input_user, &open_bracket)) error = 1;  // check ()
        if (!error && check_input_2(input_user)) error = 1;  // check / * ^
        if (!error && check_input_3(input_user)) error = 1;  // chek + -
        if (!error && check_input_4(input_user)) error = 1;  // chek X
        if (!error && check_input_5(input_user)) error = 1;  // chek =
        if (!error && check_input_6(input_user)) error = 1;  // chek .
    }

    if (!error && check_input_7(text)) error = 1;  // chek num 1234567890
    if (!error && check_input_8(text)) error = 1;  // cos tan mod ...

    return error;
}

int check_input_1(input_user save_struct, int *open_bracket) {
    int error = 0;
    char *text = save_struct.text;
    int i = save_struct.i;
    int check_next_element = save_struct.check_next_element;

    if (text[i] == ')') {
        if (!*open_bracket) {
            error = 1;

        } else {
            (*open_bracket)--;
        }

        if (check_next_element && text[i + 1] == '(') error = 1;
    }

    if (text[i] == '(') {
        (*open_bracket)++;
        if (check_next_element && text[i + 1] == ')') error = 1;
    }

    if (*open_bracket && i + 1 >= (int)strlen(text)) error = 1;

    return error;
}

int check_input_2(input_user save_struct) {
    int error = 0;
    char *text = save_struct.text;
    int i = save_struct.i;
    int check_next_element = save_struct.check_next_element;
    int check_before_element = save_struct.check_before_element;
    char *list_operand = save_struct.list_operand;
    char *list_check = "/*^";

    if (i == 0 && strchr(list_check, text[i])) error = 1;
    if (strchr(list_check, text[i])) {
        if (check_next_element && strchr(list_operand, text[i + 1])) error = 1;
        if (check_before_element && strchr(list_operand, text[i - 1])) error = 1;
        if (check_before_element && text[i - 1] == '(') error = 1;
        if (check_next_element && text[i + 1] == ')') error = 1;
    }

    return error;
}

int check_input_3(input_user save_struct) {
    int error = 0;
    char *text = save_struct.text;
    int i = save_struct.i;
    int check_next_element = save_struct.check_next_element;
    int check_before_element = save_struct.check_before_element;
    char *list_operand = save_struct.list_operand;

    if (text[i] == '+' || text[i] == '-') {
        if (check_next_element && text[i + 1] == ')') {
            error = 1;

        } else if (check_next_element && strchr(list_operand, text[i + 1])) {
            error = 1;

        } else if (check_before_element && strchr(list_operand, text[i - 1])) {
            error = 1;
        }
    }

    return error;
}

int check_input_4(input_user save_struct) {
    int error = 0;
    int i = save_struct.i;
    int check_next_element = save_struct.check_next_element;
    int check_before_element = save_struct.check_before_element;
    char *text = save_struct.text;

    if (text[i] == 'x') {
        if (check_next_element && !strchr(")+-*/^=", text[i + 1])) error = 1;
        if (!error && check_before_element && !strchr("(+-*/^", text[i - 1])) error = 2;

        if (i - 3 >= 0 && error == 2) {  // check before mod
            int check = 0;
            if (text[i - 1] == 'd') check++;
            if (text[i - 2] == 'o') check++;
            if (text[i - 3] == 'm') check++;
            if (check == 3) error = 0;
        }

        if (i + 3 <= (int)strlen(text) && error == 1) {  // check after mod
            int check = 0;
            if (text[i + 1] == 'm') check++;
            if (text[i + 2] == 'o') check++;
            if (text[i + 3] == 'd') check++;
            if (check == 3) error = 0;
        }
    }

    return error;
}

int check_input_5(input_user save_struct) {
    int error = 0;
    int i = save_struct.i;
    char *text = save_struct.text;

    if (text[i] == '=') {
        if (i != (int)strlen(text) - 1) error = 1;
        // if (!error && i == 0 && text[i] == '=') error = 1;  // для случаев когда просто = стоит
    }

    return error;
}

int check_input_6(input_user save_struct) {
    int error = 0;
    int i = save_struct.i;
    int check_next_element = save_struct.check_next_element;
    int check_before_element = save_struct.check_before_element;
    char *text = save_struct.text;

    if (text[i] == '.') {
        if (i == 0) error = 1;
        if (!error && check_before_element && text[i - 1] < 48) error = 1;
        if (!error && check_next_element && text[i + 1] > 57) error = 1;
    }

    return error;
}

int check_input_7(char *text) {
    int error = 0;
    int i = 0;

    while (!error && i < (int)strlen(text)) {
        if (i < (int)strlen(text) && ((text[i] >= 48 && text[i] <= 57) || text[i] == '.')) {
            int start = i;
            int sum_point = 0;

            while (i < (int)strlen(text) && ((text[i] >= 48 && text[i] <= 57) || text[i] == '.')) {
                if (text[i] == '.') sum_point++;
                i++;
            }

            if (i < (int)strlen(text) && !strchr(")+-*/^=", text[i])) error = 1;  // next check
            if (!error && start - 1 >= 0 && !strchr("(+-*/^", text[start - 1])) error = 2;  // before check
            if (!error && sum_point > 1) error = 1;

            if (start - 3 >= 0 && error == 2) {  // check before mod
                int check = 0;
                if (text[start - 1] == 'd') check++;
                if (text[start - 2] == 'o') check++;
                if (text[start - 3] == 'm') check++;
                if (check == 3) error = 0;
            }

            if (i + 3 <= (int)strlen(text) && error == 1) {  // check after mod
                int check = 0;
                if (text[i] == 'm') check++;
                if (text[i + 1] == 'o') check++;
                if (text[i + 2] == 'd') check++;
                if (check == 3) error = 0;
            }

        } else {
            i++;
        }
    }

    return error;
}

int check_input_8(char *text) {
    int error = 0;
    int i = 0;

    while (!error && i < (int)strlen(text)) {
        if (i < (int)strlen(text) && (text[i] >= 97 && text[i] <= 122) && text[i] != 'x') {
            int start = i;
            int check_mod = 0;

            while (i < (int)strlen(text) && (text[i] >= 97 && text[i] <= 122) && text[i] != 'x') {
                i++;
            }

            if (start + 3 <= (int)strlen(text)) {  // check mod
                int check = 0;
                if (text[start] == 'm') check++;
                if (text[start + 1] == 'o') check++;
                if (text[start + 2] == 'd') check++;
                if (check == 3) check_mod = 1;
            }

            if (!check_mod && start > 0 && !strchr("(+-*/^", text[start - 1])) error = 1;
            if (check_mod) {
                if (start == 0) error = 1;
                if (!error && start > 0 && !strchr(")1234567890x", text[start - 1])) error = 1;
                if (!error && i <= (int)strlen(text) && !strchr("(1234567890x", text[i])) error = 1;
            }

        } else {
            i++;
        }
    }

    return error;
}

