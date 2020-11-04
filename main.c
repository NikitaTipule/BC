#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "bc.h"

int main() {
    pstack ps;
    ostack os;
    char str[200];
    int i = 0;
    char c;
    node *n1 = NULL, *n2 = NULL, *result = NULL, *n = NULL;
    init_os(&os, 20);
    init_ps(&ps, 20);
    init(&n1);
    init(&n2);
    init(&n);
    init(&result);



    while(1) {
        printf(">>>");
        gets(str);
        if(!strcmp(str,"exit"))
            break;
        else if(isdigit(str[i]) || str[i] == '(') {
            if(str[i]=='#') {
                continue;
            }
            else {
                push_os(&os, '#');
                while(str[i] != '\0') {
                    if(str[i] == '(') {
                        push_os(&os, '(');
                        i++;
                    }
                    else if(isdigit(str[i])) {
                        init(&n);
                        while(isdigit(str[i])) {
                            insert_dig(&n, str[i] - '0');
                            i++;
                        }
                        push_op(&ps, n);
                        i++;
                    }
                    else if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^') {
                        c = pop_os(&os);
                        if(precedence(str[i]) > precedence(c)) {
                            push_os(&os, c);
                            push_os(&os, str[i]);
                            i++;
                            i++;
                        }
                        else {
                            while(precedence(str[i]) <= precedence(c)) {
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
                                    // case '^' : result = expo(n2, n1);
                                    //            push_op(&ps, result);
                                    //            break;
                                }
                                push_op(&ps, result); 
                                c = pop_os(&os);
                            }
                            push_os(&os, c);
                            push_os(&os, str[i]);
                            i++;
                            i++;
                        }
                    }
                    else if(str[i] == ')') {
                        n2 = pop_op(&ps);
                        n1 = pop_op(&ps);
                        c = pop_os(&os);
                    }

                }
            }
        }
        display(&ps);
    
    }
}