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
    list n1, n2, n3;

    while(1) {
        printf(">>>");
        n1 = n2 = n3 = NULL;
        i = 0; n = 0 ;
        init_os(&os, 10);
        init_ps(&ps, 10);
        gets(str);
        if(!strcmp(str, "exit")) {
            break;
        }
        while(str[i] != '\0') {
            if(isdigit(str[i])) {
                init(&n1);
                do{ 
                    n = str[i] - '0';
                    insert_dig(&n1, n);
                    i++;
                }while(isdigit(str[i]));
                push_op(&ps, n1);
                i++;
            }
            else if(str[i] == '/') {
                push_os(&os, str[i]);
                i++;
                i++;
            }
            else {
                break;
            }
        }
        init(&n2);
        init(&n1);
        init(&n3);
        n2 = pop_op(&ps);
        n1 = pop_op(&ps);
        n3 = division(n2, n1);
        push_op(&ps, n3);
        display(&ps);
        
    }
    return 0;
}