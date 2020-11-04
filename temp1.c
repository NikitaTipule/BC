#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "bc.h"

int main() {
    char str[500];
    pstack ps;
    ostack os;
    init_os(&os, 10);
    init_ps(&ps, 10);
    int i = 0, n = 0;
    char c;
    list n1, n2, n3, result;



    while(1) {
        printf(">>>");
        n1 = n2 = n3 = result = NULL;
        i = 0; n = 0 ;
        init_os(&os, 10);
        init_ps(&ps, 10);
        gets(str);
        if(!strcmp(str,"exit"))
            break;
        else if(isdigit(str[i]) || str[i] == '(') {
            if(str[i]=='#') {
                printf("Invalid input .");
                continue;
            }
            else {
                push_os(&os, '#');
                while(str[i] != '\0') {
                    if(str[i] == '(') {
                        push_os(&os, '(');
                        i++;
                        i++;
                    }
                    else if(isdigit(str[i])) {
                        init(&n1);
                        do{ 
                            n = str[i] - '0';
                            insert_dig(&n1, n);
                            i++;
                        }while(isdigit(str[i]));
                        push_op(&ps, n1);
                        i++;
                    }
                    else if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^') {
                        c = pop_os(&os);
                        if(precedence(str[i]) > precedence(c)) {
                            push_os(&os, c);
                            push_os(&os, str[i]);
                            //display_stack(&ps);
                            i++;
                            i++;
                        }
                        else {
                            while(precedence(str[i]) <= precedence(c)) {
                                //display_stack(&ps);
                                n2 = pop_op(&ps);
                                n1 = pop_op(&ps);
                                switch(c) {
                                    case '+' : result = add(n2, n1);
                                                //display(&ps);
                                            //    print(n2);printf("\n");
                                            //    print(n1);printf("\n");
                                               push_op(&ps, result);
                                               //print(result);printf("\n");
                                               break;
                                    case '-' : result = sub(n2, n1);
                                               push_op(&ps, result);
                                               break;
                                    case '*' : result = multi(n2, n1);
                                               push_op(&ps, result);
                                               //print(result);
                                               break;
                                    case '/' : result = division(n2, n1);
                                               push_op(&ps, result);
                                               //print(result);
                                               break;
                                    // case '^' : result = expo(n2, n1);
                                    //            push_op(&ps, result);
                                    //            break;
                                }
                                //push_op(&ps, result); 
                                c = pop_os(&os);
                            }
                            push_os(&os, c);
                            push_os(&os, str[i]);
                            i++;
                            i++;
                        }
                    }
                    else if(str[i] == ')') {
                        c = pop_os(&os);
                        while(c != '(' && c != '#') {
                            n2 = pop_op(&ps);
                            n1 = pop_op(&ps);
                            switch(c) {
                                case '+' : result = add(n2, n1);
                                            push_op(&ps, result);
                                            break;
                                case '-' : result = sub(n2, n1);
                                            push_op(&ps, result);
                                            break;
                                case '*' : result = multi(n2, n1);
                                            push_op(&ps, result);
                                            break;
                                case '/' : result = division(n2, n1);
                                            push_op(&ps, result);
                                            break;
                            }
                            c = pop_os(&os);
                        }
                        if(c == '#') {
                            push_os(&os, '#');
                        }
                        i++;
                        if(str[i] == '\0')
                            break;
                        i++;
                    }

                }
                c = pop_os(&os);
                while(c != '#'){
                    n2 = pop_op(&ps);
                    n1 = pop_op(&ps);
                    switch(c) {
                        case '+' : result = add(n2, n1);
                                    push_op(&ps, result);
                                    break;
                        case '-' : result = sub(n2, n1);
                                    push_op(&ps, result);
                                    break;
                        case '*' : result = multi(n2, n1);
                                    push_op(&ps, result);
                                    break;
                        case '/' : result = division(n2, n1);
                                    push_op(&ps, result);
                                    //printf("\n");
                                    //print(result);
                                    //printf("\n");
                                    break;
                        default :   push_op(&ps,n1);
                                    push_op(&ps,n2);
                                    break;
                    }
                    c = pop_os(&os);
                }

            }
        }
        display(&ps);
    }
}
