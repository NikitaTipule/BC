#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "bc.h"

int main() {       
    char str[1000];
    pstack ps;
    ostack os;
    init_os(&os, 10);
    init_ps(&ps, 10);
    int i = 0, n = 0, m=0, invalid = 0;
    char c;
    list n1, n2, n3, result;



    while(1) {
        FILE *fp;
        fp = fopen("E:/DSA-1/BC/BC-calculator/history.txt", "a+");
        printf(">>>");
        n1 = n2 = n3 = result = NULL;
        init(&result);
        i = 0; n = 0 ; invalid = 0;
        init_os(&os, 10);
        init_ps(&ps, 2);
        gets(str);
        if(!strcmp(str,"exit"))
            break;

        //trigonometric functions
        else if(m = is_trigo(str)) {
            //m = is_trigo(str);
            init(&n1);
            init(&result);
            while(str[i] != '(') {
                i++;
            }
            i++;
            do{ 
                n = str[i] - '0';
                insert_dig(&n1, n);
                i++;
            }while(isdigit(str[i]));
            push_op(&ps, n1);
            if(str[i] == ',') {
                i++;
                init(&n1);
                while(str[i] != ')') {
                    n = str[i] - '0';
                    insert_dig(&n1, n);
                }
            }
            if(str[i] != ')'){
                printf("Invalid input\n");
                continue;
            }
            switch(m) {
                case 1: printf("%0.3lf\n",sin_t(&ps));
                        fputs("sin()\n", fp);
                        fclose(fp);
                        continue;
                        break;
                case 2: printf("%0.3lf\n",cos_t(&ps));
                        fputs("cos()\n", fp);
                        fclose(fp);
                        continue;
                        break;
                case 3: printf("%0.3lf\n",tan_t(&ps));
                        fputs("tan()\n", fp);
                        fclose(fp);
                        continue;
                        break;
                case 4: if(n1->dig == 0 && n1->next == NULL) {
                            printf("Invalid input\n");
                            continue;
                        }
                        printf("%0.3lf\n",log_n(&ps));
                        fputs("log()\n", fp);
                        fclose(fp);
                        continue;
                        break;
                // case 5: result = expo(&ps);
                //         push_op(&ps, result);

                default: break;
            }
        }


        else if(isdigit(str[i]) || str[i] == '(') {
            //init_ps(&ps, 20);
            //display_stack(&ps);
            if(str[i]=='#') {
                printf("Invalid input .");
                continue;
            }
            else {
                push_os(&os, '#');
                while(str[i] != '\0') {
                    if(str[i] == '(') {
                        push_os(&os, '(');
                        if(str[i+1] == ' ') {
                            i++;
                        }
                        else {
                            printf("Invalid input babli\n");
                            invalid = 1;
                            break;
                        }
                        if(isdigit(str[i+1])){ 
                            i++;
                        }
                        else {
                            printf("Invalid Input ara\n");
                            invalid = 1;
                            break;
                        }
                    }
                    else if(isdigit(str[i])) {
                        init(&n3);
                        do{ 
                            n = str[i] - '0';
                            insert_dig(&n3, n);
                            i++;
                        }while(isdigit(str[i]));
                        push_op(&ps, n3);
                        //distory_list(&n3);
                        if(str[i] == ' ')
                            i++;
                        if(str[i] == '(') {
                            printf("Invalid input\n");
                            invalid = 1;
                            break;
                        }
                    }
                    else if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^' || str[i] == '%') {
                        if(str[i+1] == ' ' && isdigit(str[i+2])){
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
                                                push_op(&ps, result);
                                                fputs("add()\n", fp);
                                                break;
                                        case '-' : result = sub(n2, n1);
                                                push_op(&ps, result);
                                                fputs("sub()\n", fp);
                                                break;
                                        case '*' : result = multi(n2, n1);
                                                push_op(&ps, result);
                                                fputs("multi()\n", fp);
                                                break;
                                        case '/' : result = division(n2, n1);
                                                fputs("div()\n", fp);
                                                push_op(&ps, result);
                                                break;
                                        case '%' : result = mod(n1, n2);
                                                fputs("mod()\n", fp);
                                                push_op(&ps, result);
                                                break;
                                        case '^' : result = power(n2, n1);
                                                fputs("power()\n", fp);
                                                push_op(&ps, result);
                                                break;
                                        default : break;
                                    }
        
                                    c = pop_os(&os);
                                }
                                push_os(&os, c);
                                push_os(&os, str[i]);
                                i++;
                                i++;
                            }
                        }
                        else {
                            printf("Invalid input\n");
                            invalid = 1;
                            break;
                        }
                    }
                    else if(str[i] == ')') {
                        if((str[i+1] == ' ' && (str[i + 2] == '+' || str[i+2] == '-' || str[i+2] == '/' || str[i+2] == '*' || str[i+2] == '^' || str[i+2] == '%') || str[i+1] == '\0')){
                            c = pop_os(&os);
                            while(c != '(' && c != '#') {
                                n2 = pop_op(&ps);
                                n1 = pop_op(&ps);
                                switch(c) {
                                    case '+' : result = add(n2, n1);
                                                push_op(&ps, result);
                                                fputs("add()\n", fp);
                                                break;
                                    case '-' : result = sub(n2, n1);
                                                push_op(&ps, result);
                                                fputs("sub()\n", fp);
                                                break;
                                    case '*' : result = multi(n2, n1);
                                                push_op(&ps, result);
                                                fputs("multi()\n", fp);
                                                break;
                                    case '/' : result = division(n2, n1);
                                                fputs("div()\n", fp);
                                                push_op(&ps, result);
                                                break;
                                    case '%' : result = mod(n1, n2);
                                                fputs("mod()\n", fp);
                                                push_op(&ps, result);
                                                break;
                                    case '^' :  result = power(n2, n1);
                                                push_op(&ps, result);
                                                fputs("power()\n", fp);
                                                break;
                                    default : break;
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
                        else {
                            printf("Invalid input nik\n");
                            invalid = 1;
                            break;
                        }
                    }

                }

                c = pop_os(&os);
                while(c != '#'){

                    n2 = pop_op(&ps);
                    n1 = pop_op(&ps);
                
                    switch(c) {
                        case '+' :  result = add(n2, n1);
                                    push_op(&ps, result);
                                    fputs("add()\n", fp);
                                    break;
                        case '-' :  result = sub(n2, n1);
                                    push_op(&ps, result);
                                    fputs("sub()\n", fp);
                                    break;
                        case '*' :  result = multi(n2, n1);
                                    push_op(&ps, result);
                                    fputs("multi()\n", fp);
                                    break;
                        case '/' :  result = division(n2, n1);
                                    push_op(&ps, result);
                                    fputs("div()\n", fp);
                                    break;
                        case '%' :  result = mod(n1, n2);
                                    push_op(&ps, result);
                                    fputs("mod()\n", fp);
                                    break;
                        case '^' :  result = power(n2, n1);
                                    push_op(&ps, result);
                                    fputs("power()\n", fp);
                                    break;
                        default :   break;
                    }
                    c = pop_os(&os);
                }

            }
        }
        if(invalid != 1) {
            display_stack(&ps);
        }
        distroy_stack(&ps);
        distroy_stack_o(&os);
        fclose(fp);
    }
}
