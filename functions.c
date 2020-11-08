#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include "bc.h"



int precedence(char c){
    if(c == '+')
        return 10;  
    else if(c == '-')
        return 10;
    else if(c == '*')
        return 20;
    else if(c == '/')
        return 20;
    else if(c == '%')
        return 20;
    else if(c == '^')
        return 30;
    else if(c == '(')
        return 5;
    else if(c == '#')
        return 0;
    return 0;
}

node* add(list n2, list n1) {
    node *p1, *p2, *n = NULL;
    p1 = n1;
    p2 = n2;
    int c1 = 0, c2 = 0, c = 0;
    node *a1 = n1, *a2 = n2;
    while(a1 -> next != NULL) {
        a1 = a1 -> next;
        c1++;
    }
    while(a2 -> next != NULL) {
        a2 = a2 ->next;
        c2++;
    }

    int d1= 0, d2 = 0, d;
    while(a1 && a2) {
        d1 = (a1 -> dig) + (a2 -> dig) + c;
        d2 = d1 % 10;
        c = d1 / 10;
        insert_beg(&n, d2);
        a1 = a1 -> prev;
        a2 = a2 -> prev;
    }

    while(a1) {
        d1 = (a1 -> dig) + c;
        d2 = d1 % 10;
        c = d1 / 10;
        insert_beg(&n, d2);
        a1 = a1 -> prev;
    }

    while(a2) {
        d1 = (a2 -> dig) + c;
        d2 = d1 % 10;
        c = d1 / 10;
        insert_beg(&n, d2);
        a2 = a2 -> prev;
    }
    if(c > 0) {
        insert_beg(&n, c);
    }
    //distory_list(&p1);distory_list(&p2);distory_list(&a1);distory_list(&a2);
    return n;
}
void insert_beg(list *p, int d) {
    node *n = *p, *new = NULL, *a = NULL;

    new = (node*)malloc(sizeof(node));
    if(new) {
        new -> dig = d;
        new -> prev = NULL;
        new -> next = NULL;
    }
    else return;
    if((*p) == NULL) {
        (*p) = new;
        return;
    }
    else {
        a = (*p);
        new -> next = a;
        a -> prev = new;
        (*p) = new;
        return; 
    }

}

void display(pstack *ps) {

    node *p = NULL, *q = NULL;
    init(&q);
    init(&p);
    p = pop_op(ps);
    
    while(p) {
        printf("%d", p -> dig);
        q = p;
        p = p -> next;
        free(q);
    }
    printf("\n");
    return;
}

void print(node *p) {
    node *n;
    init(&n);
    n = p;
    while(n) {
        printf("%d", n ->dig);
        n = n ->next;
    }
    return;
}

node* larger(list n1, list n2) {
    list a = n1, b = n2;
    int c1 = 0, c2 = 0;
   while(a){
        if(a -> dig == 0 && a -> next != NULL) {
            a = a -> next;
            a -> prev = NULL;
        } 
        else {
            break;
        }
    } 
   while(b){
        if(b -> dig == 0 && b -> next != NULL) {
            b = b -> next;
            b -> prev = NULL;
        } 
        else {
            break;
        }
    } 
    while(a) {
        a = a->next;
        c1++;
    } 
    while(b) {
        b = b->next;
        c2++;
    }
    if(c1 > c2) 
        return n1;
    else if(c2 > c1)
        return n2;
    else {
        node *p = n1, *q = n2;
        while(p && q) {
            if(p -> dig > q ->dig) 
                return n1;
            else if(p->dig < q->dig)
                return n2;
            else {
                p = p->next;
                q = q->next;
            }
        }
        return n1;

    }
}

node* sub(list n2, list n1) {


    list a1 = n1, a2 = n2, p1 = n1, p2 = n2, temp = NULL, n3 = NULL, temp2 = NULL;
    list temp1 = n3, q = NULL, x = NULL, y = NULL;
    init(&n3);
    // while(a1) {

    // }

    while(a1 -> dig ==0) {
        if(a1 -> next == NULL)
            break;
        q = a1;
        //print(a1);
        //printf("\t");
        a1 = a1 -> next;     
        a1 ->prev = NULL;
        //print(a1);
    }

    while(a2 -> dig ==0) {
        if(a2 -> next == NULL)
            break;
        q = a2;
        //print(a2);
        //printf("\t");
        a2 = a2 -> next;
        a2 ->prev = NULL;
        //print(a2);
    }
    // print(a1);
    // printf("\t");
    // print(a2);

    q = NULL;
    int c1 = 0, c2 = 0, b = 0, d1 = 0, d = 0;
    if(is_same(a1, a2)) {
        insert_dig(&temp1, 0);
        return temp1;
    }
    while(a1->next != NULL) {
        insert_dig(&x, a1 ->dig);
        a1 = a1 -> next;
        c1++; 
    }
    insert_dig(&x, a1 ->dig);
    c1++;
    while(a2 -> next != NULL) {
        insert_dig(&y, a2 -> dig);
        a2 = a2 ->next;
        c2++;
    }
    insert_dig(&y, a2 ->dig);
    c2++;

    temp = larger(x, y);
    if(is_same(x,temp)) {
        while(a1 && a2) {
            if((a1 -> dig) >= (a2->dig + b)) {
                d1 = (a1 -> dig - (a2 -> dig + b));
                b = 0;
            }
            else {
                d1 = 10 + (a1 ->dig) - (a2->dig + b);
                b = 1;
            }
            insert_beg(&n3, d1);
            a1 = a1 -> prev;
            a2 = a2 -> prev;
        }
        while(a1) {
            if(a1->dig >= b){
                d = a1->dig - b;
                d1 = d % 10;
                // b = d / 10;
                insert_beg(&n3, d1);
                a1 = a1 -> prev;
                b = 0;
            }
            else {
                d = 10 + a1->dig - b;
                b = 1;
                d1 = d % 10;
                // b = d / 10;
                insert_beg(&n3, d1);
                a1 = a1 -> prev; 
            }
        }
        temp1 = n3;

        while(temp1 -> dig == 0) {
            if(temp1 -> next == NULL)
                return temp1;
            q = temp1;
            temp1 = temp1 -> next;
            q -> next = NULL;
            temp1 -> prev = NULL;
            free(q);
        }
    }
    else {
        while(a1 && a2) {
            if((a2 -> dig) >= (a1->dig + b)) {
                d1 = (a2 -> dig - (a1 -> dig + b));
                b = 0;
            }
            else {
                d1 = 10 + (a2 ->dig) - (a1->dig + b);
                b = 1;
            }
            insert_beg(&n3, d1);
            a1 = a1 -> prev;
            a2 = a2 -> prev;
        }
        while(a2) {
            if(a2->dig >= b) {
                d1= a2 -> dig - b;
                b = 0;
            }
            else {
                d1 = 10 + (a2 ->dig) - b;
                b = 1;
            }
            a2 = a2 -> prev;
            insert_beg(&n3, d1);
        }
        temp1 = n3; q = NULL;
        while(temp1 -> dig ==0) {
            if(temp1 -> next == NULL)
                return temp1;
            q = temp1;
            temp1 = temp1 -> next;
            temp1 ->prev = NULL;
            free(q);
        }
        temp1 -> dig = -(temp1->dig);
       // printf("-");
    }
    return temp1;
}


node* multi(list n2, list n1) {

    list a1 = n1, a2 = n2, n3 = NULL, mult = NULL, q = NULL, temp, temp1;
    init(&n3);
    init(&mult);
    init(&temp1);init(&temp);
    mult = (node*)malloc(sizeof(node));
    if(mult) {
        mult ->dig = 0;
        mult -> next = NULL;
        mult -> prev = NULL;
    }
   while(a2){
        if(a2 -> dig == 0 && a2 -> next != NULL) {
            a2 = a2 -> next;
            a2 -> prev = NULL;
        } 
        else {
            break;
        }
    } 
   while(a1){
        if(a1 -> dig == 0 && a2 -> next != NULL) {
            a1 = a1 -> next;
            a2 -> prev = NULL;
        } 
        else {
            break;
        }
    } 

    if(a2 -> dig == 1 && a2 -> next == NULL)
        return a1;

    while(a2 -> next != NULL) {
        a2 = a2 -> next;
    }
    while(a1 -> next != NULL) {
        a1 = a1 -> next;
    }
    temp = a1, temp1= NULL;
    int c = 0, d = 0, t = 0;
    while(a2) {
        a1 = temp;
        c = 0;
        init(&n3);
        while(a1) {
            d = (a1->dig) * (a2->dig) + c;
            insert_beg(&n3, d%10);
            c = d / 10;
            a1 = a1 -> prev;
        }
        if(c > 0) {
            insert_beg(&n3, c);
        }
        int i = 0;
        while(i < t) {
            insert_dig(&n3, 0);
            i++;
        }
        mult = add(n3, mult);
        a2 = a2 -> prev;
        t++;
    }
    // distroy(&n3);
    // distroy(&a2);
    // distroy(&a1);
    temp1 = mult;
    while(temp1 -> dig ==0 && temp1 ->next != NULL) {
        q = temp1;
        temp1 = temp1 -> next;
        temp1 -> prev = NULL;
        free(q);
    }
    return mult;

}


// node* multii(list n2, list n1) {
//     list a1 = n1, a2 = n2, new = NULL, mult = NULL, subt = NULL;
//     new = (node*)malloc(sizeof(node));
//     if(new) {
//         new -> dig = 1;
//         new ->next = NULL;
//         new -> prev = NULL;
//     }
//     mult = (node*)malloc(sizeof(node));
//     if(mult) {
//         mult ->dig = 0;
//         mult -> prev = NULL;
//         mult -> next = NULL;
//     }
//     // while(a2 != NULL){
//     //     if(a2 -> next == NULL && a2 ->dig == 0) {
//     //         return mult;
//     //     }
//     //     a2 = sub(new,a2);
//     //     print(a2);
//     //     printf("\t");
//     // }
//     // print(sub(new,a2));
//     a2 = add(a2,new);
//     while(a2 != NULL) {
//         mult = add(mult, a1);
//         a2 = sub(new,a2);
//         print(a2);
//     }
//     return mult;
// }


void distroy(list *n1) {
    list n = *n1, q = *n1;
    while(n != NULL) {
        q = n;
        n = n -> next;
        n -> prev = NULL;
        q -> next = NULL;
        free(q);
    }
    return;
}

int is_same(list n1, list n2) {
    list a1 = n1, a2 = n2;
    while(a1 && a2) {
        if(a1 -> dig == a2 -> dig){ 
            a1 = a1 -> next;
            a2 = a2 -> next;
            continue;
        }
        else{
            return 0;
        }
    }
    while(a1) {
        return 0;
    }
    while(a2) {
        return 0;
    }
    return 1;
}


node* division(list n2 , list n1) {


    list a1 = n1, a2 = n2, n3 = NULL, temp = NULL, q = NULL;
    int count=0, d=0;
    init(&temp);

    while(a1 -> dig ==0) {
        if(a1 -> next == NULL)
            break;
        q = a1;
        a1 = a1 -> next;     
        a1 ->prev = NULL;
    }
   
    while(a2 -> dig ==0) {
        if(a2 -> next == NULL)
            break;
        q = a2;
        a2 = a2 -> next;
        a2 ->prev = NULL;
    }

    if(a2 -> dig == 0 && a2 -> next == NULL) {
        printf("Invalid input... please enter the valid input combination");
        return n3;
    }

    if(is_same(a1,a2)) {
        insert_dig(&n3, 1);
        return n3;
    }
    if(is_same(a2,larger(a1,a2))) {
        insert_dig(&n3, 0);
        
        return n3;
    }

    if(is_same(a1,a2)) {
        insert_dig(&n3, 1);
        return n3;
    }
    while(a1) {
        insert_dig(&temp, a1 ->dig);
        a1 = a1 -> next;
    }
  
    while(is_same(temp,larger(temp,a2))) {
        
        temp = sub(a2, temp);
        count++;

    }
   
    if(is_same(temp,a2)) {
        count++;
    }

    while(count > 0) {
        d = count % 10;
        count = count / 10;
        insert_beg(&n3, d);
    }
    return n3;
}



// node* multi(list n2, list n1) {
//     list a1 = n1, a2 = n2, n3 = NULL, mult = NULL, q = NULL, temp, temp1;
//     init(&n3);
//     init(&mult);
//     init(&temp1);init(&temp);
//     mult = (node*)malloc(sizeof(node));
//     if(mult) {
//         mult ->dig = 0;
//         mult -> next = NULL;
//         mult -> prev = NULL;
//     }

//     while(a2 -> next != NULL) {
//         a2 = a2 -> next;
//     }
//     while(a1 -> next != NULL) {
//         a1 = a1 -> next;
//     }
//     temp = a1, temp1= NULL;
//     int c = 0, d = 0, t = 0;
//     while(a2) {
//         a1 = temp;
//         c = 0;
//         init(&n3);
//         while(a1) {
//             d = (a1->dig) * (a2->dig) + c;
//             insert_beg(&n3, d%10);
//             c = d / 10;
//             a1 = a1 -> prev;
//         }
//         if(c > 0) {
//             insert_beg(&n3, c);
//         }
//         int i = 0;
//         while(i < t) {
//             insert_dig(&n3, 0);
//             i++;
//         }
//         mult = add(n3, mult);
//         a2 = a2 -> prev;
//         t++;
//     }
//     // distroy(&n3);
//     // distroy(&a2);
//     // distroy(&a1);
//     temp1 = mult;
//     while(temp1 -> dig ==0) {
//         q = temp1;
//         temp1 = temp1 -> next;
//         temp1 -> prev = NULL;
//         free(q);
//     }
//     return mult;

// }



void display_stack(pstack *p) {
    int i = p->top;
    pstack *s = p;
    while(s ->top !=-1) {
        print(s->arr[s->top]);
        printf("\t");
        s ->top--;
    }
    printf("\n");
    s->top = i;
    return;
}


// int is_comparison(char *p) {
//     int i = 0;
//     while(p[i] != '\0') {
//         do{ 
//             n = p[i] - '0';
//             insert_dig(&n1, n);
//             i++;
//         }while(isdigit(p[i]));
//         push_op(&ps, n1);
//         i++;
//         if(p[i] == '<' || (p[i] == '>') || (p[i] == '=' && p[i+1] == '=') || (p[i] == '!' && p[i+1] == '=' )) {
//             c = str[i];
//             i++;
//             i++;
//         }
//         if(isdigit(str[i])) {
//             do{ 
//                 n = str[i] - '0';
//                 insert_dig(&n1, n);
//                 i++;
//             }while(isdigit(str[i]));
//             push_op(&ps, n1);  
//         }
//         if(str[i] == '\0'){
//             is_comparison(&ps, c);
//         }

//     }
// }


// void is_comparison(pstack *p, char c) {
//     list a1, a2, n3, q;
//     a2 = pop_op(p);
//     a1 = pop_op(p);

//     while(a1 -> dig ==0) {
//         if(a1 -> next == NULL)
//             break;
//         q = a1;
//         a1 = a1 -> next;     
//         a1 ->prev = NULL;
//     }

//     while(a2 -> dig ==0) {
//         if(a2 -> next == NULL)
//             break;
//         q = a2;
//         a2 = a2 -> next;
//         a2 ->prev = NULL;
//     }
//     if(c == '=') {
//         if(is_same(a1,a2)) {
//             printf("True");
//         }
//         else {
//             printf("False");
//         }
//     }
//     if(c == '!') {
//         if(!is_same(a1, a2)) {
//             printf("True");
//         }
//         else {
//             printf("False");
//         }
//     }
//     n3 = larger(a1, a2);
//     if(c == '>') {
//         if(a1==n3) {
//             printf("True");
//         }
//         else {
//             printf("False");
//         }
//     }
//     else if(c == '<') {
//         if(n3 == a2) {
//             printf("True");
//         }
//         else {
//             printf("False");
//         }
//     }
//     return;
// }

int is_trigo(char *p) {
    char *s = p;
    int r;
    int i = 0;
    if(s[i] == 's' && s[i+1] == 'i' && s[i+2] == 'n' && s[i+3] == '(' && isdigit(s[i+4])) {
        r = 1;
        return r;
    }
    else if(s[i] == 'c' && s[i+1] == 'o' && s[i+2] == 's' && s[i+3] == '(' && isdigit(s[i+4])) {
        r = 2;
        return r;
    }
    else if(s[i] == 't' && s[i+1] == 'a' && s[i+2] == 'n' && s[i+3] == '(' && isdigit(s[i+4])) {
        r = 3;
        return r;
    }
    else if(s[i] == 'l' && s[i+1] == 'o' && s[i+2] == 'g' && s[i+3] == '(' && isdigit(s[i+4])) {
        r = 4;
        return r;
    }
    else if(s[i] == 'e' && s[i+1] == 'x' && s[i+2] == 'p' && s[i+3] == 'o' && s[i+4] == '(' && isdigit(s[i+5])) {
        r = 5;
        return r;
    }
    else if(s[i] == 'p' && s[i+1] == 'o' && s[i+2] == 'w' && s[i+4] == '(' && isdigit(s[i+5])) {
        r = 6;
        return r;
    }
    else {
        return 0;
    }
}

double sin_t(pstack *p) {
    list n = NULL, new = NULL;
    n = pop_op(p);
    int count = 0;
    list a = n, c = n;
    //print(n);
    while(a -> dig == 0) {
        if(a->next == NULL) 
            break;
        a = a->next;
        a -> prev = NULL;
    }
    //print(a);
    //chaking the number is greater than 360 or not
    init(&new);
    insert_beg(&new,0);
    insert_beg(&new, 6);
    insert_beg(&new, 3);

    while(is_same(a,larger(a,new))) {
        //print(a);printf("\t");
        a = sub(new, a);
    }
    c = a;
    //print(a);printf("\n");
    while(c -> next != NULL) {
        count++;
        c = c->next;
    }
    float b = 0; int i = 0;

    while(c) {
        //printf("%d\t", c->dig);
        b = b + (c->dig) * pow(10,i);
        //printf("%d\n", b);
        i++;
        c = c -> prev; 
    }

    int t = b;float r, sum;
    b = b * 3.14159 / 180;
    r = b;
    sum = b;
     
    for(i = 1; i <= 100; i++)
    {
        r = (r*(-1)*b*b) / (2*i*(2*i+1));
        sum = sum + r;
    }


    //printf("%d\n", b);
    // float t = b * 3.142/180;
    //return sin(t);
    return sum;

}

double cos_t(pstack *p) {


    list n = NULL, new = NULL;
    n = pop_op(p);
    int count = 0;
    list a = n, c = n;
    //print(n);
    while(a -> dig == 0) {
        if(a->next == NULL) 
            break;
        a = a->next;
        a -> prev = NULL;
    }
    //print(a);
    //chaking the number is greater than 360 or not
    init(&new);
    insert_beg(&new,0);
    insert_beg(&new, 6);
    insert_beg(&new, 3);

    while(is_same(a,larger(a,new))) {
        //print(a);printf("\t");
        a = sub(new, a);
    }
    c = a;
    //print(a);printf("\n");
    while(c -> next != NULL) {
        count++;
        c = c->next;
    }
    float b = 0;int i = 0;

    while(c) {
        //printf("%d\t", c->dig);
        b = b + (c->dig) * pow(10,i);
        //printf("%d\n", b);
        i++;
        c = c -> prev; 
    }


    float t = b * 3.141592653589793238/180;
    return cos(t);
    //return sum;

}


double tan_t(pstack *p) {


    list n = NULL, new = NULL;
    n = pop_op(p);
    int count = 0;
    list a = n, c = n;
    //print(n);
    while(a -> dig == 0) {
        if(a->next == NULL) 
            break;
        a = a->next;
        a -> prev = NULL;
    }
    //print(a);
    //chaking the number is greater than 360 or not
    init(&new);
    insert_beg(&new,0);
    insert_beg(&new, 6);
    insert_beg(&new, 3);

    while(is_same(a,larger(a,new))) {
        //print(a);printf("\t");
        a = sub(new, a);
    }
    c = a;
    //print(a);printf("\n");
    while(c -> next != NULL) {
        count++;
        c = c->next;
    }
    int b = 0, i = 0;

    while(c) {
        //printf("%d\t", c->dig);
        b = b + (c->dig) * pow(10,i);
        //printf("%d\n", b);
        i++;
        c = c -> prev; 
    }
    float x=0;
    if(b == 90) {
        printf("value is out of range");
        return x; 
    }
    //printf("%d\n", b);
    float t = b * 3.141592653589793238/180;
    return tan(t);

}

double expo(pstack *p) {


    list n = NULL, new = NULL;
    n = pop_op(p);
    int count = 0;
    list a = n, c = n;
    //print(n);
    while(a -> dig == 0) {
        if(a->next == NULL) 
            break;
        a = a->next;
        a -> prev = NULL;
    }

    while(c -> next != NULL) {
        count++;
        c = c->next;
    }
    long long int b = 0;int i = 0;

    while(c) {
        b = b + (c->dig) * pow(10,i);
        i++;
        c = c -> prev; 
    }   


}

node* mod(list n1, list n2) {

    list a1 = n1, a2 = n2, n3 = NULL, temp = NULL, q = NULL;
    int count=0, d=0;
    init(&temp);
    while(a1 -> dig ==0) {
        if(a1 -> next == NULL)
            break;
        q = a1;
        a1 = a1 -> next;     
        a1 ->prev = NULL;
    }

    while(a2 -> dig ==0) {
        if(a2 -> next == NULL)
            break;
        q = a2;
        a2 = a2 -> next;
        a2 ->prev = NULL;
    }

    if(a2 -> dig == 0 && a2 -> next == NULL) {
        printf("Invalid input... please enter the valid input combination");
        return n3;
    }

    if(is_same(a1,a2)) {
        insert_dig(&n3, 0);
        return n3;
    }
    if(is_same(a2,larger(a1,a2))) {
        //insert_dig(&n3, 0);
        
        return a1;
    }

    if(is_same(a1,a2)) {
        insert_dig(&n3, 0);
        return n3;
    }
    while(a1) {
        insert_dig(&temp, a1 ->dig);
        a1 = a1 -> next;
    }
    while(is_same(temp,larger(temp,a2))) {
        //print(larger(temp,a2));printf("\t");
        temp = sub(a2, temp);
        count++;
        // print(temp);
        // printf("\t");
        // printf("%d\n", count);
    }
    //print(larger(temp,a2));printf("\t");
    if(is_same(temp,a2)) {
        insert_beg(&n3, 0);
        return n3;
    }

    list temp2=NULL;
    while(temp->dig == 0) {
        if(temp->next == NULL) {
            break;
        }
        temp2 = temp;
        temp = temp -> next;
        temp-> prev = NULL;
        temp2 -> next = NULL;
        free(temp2);
    }
    
    return temp;  
}



void distroy_stack(pstack *p) {
    pstack *s = p;
    list n =NULL;
    while((s->top) != -1) {
        n = pop_op(p);
        distory_list(&n);
    }
    s->top = s->size - 1;
    while(s->top != -1) {
        s->arr[s->top] = NULL;
        s->top--;
    }
    free(s->arr);
    return;
}

void distory_list(list *n) {
    list l = (*n), m = NULL;
    //print(l);
    while(l -> next != NULL) {
        m = l;
        l = l->next;
        l -> prev = NULL;
        m -> next = NULL;
        free(m);
    }
    l ->next = NULL;
    l ->prev = NULL;
    free(l);
    return;
}


void distroy_stack_o(ostack *p) {
    free(p->a);
    return;
}



node* power(list n2, list n1) {

    list a1 = n1, a2 = n2, n3 = NULL, new = NULL, new1= NULL;
    new = (node*)malloc(sizeof(node));
    if(new) {
        new -> dig = 0;
        new -> next = NULL;
        new -> prev = NULL;
    }
    else return n3;
    new1 = (node*)malloc(sizeof(node));
    if(new1) {
        new1 -> dig = 1;
        new1 -> next = NULL;
        new1 -> prev = NULL;       
    }
    
    n3 = (node*)malloc(sizeof(node));
    if(n3) {
        n3 -> dig = 1;
        n3 -> next = NULL;
        n3 -> prev = NULL;
    }

    while(!is_same(new, n2)) {
        n3 = multi(n3, n1);
        n2 = sub(new1, n2);
    }

    return n3;
}


double log_n(pstack *p) {

    list n = NULL, new = NULL;
    n = pop_op(p);

    list a = n, c = n;
    //print(n);
    while(a -> dig == 0) {
        if(a->next == NULL) 
            break;
        a = a->next;
        a -> prev = NULL;
    }
    int i = 0;
    float b = 0;

    while(c) {
        //printf("%d\t", c->dig);
        b = b + (c->dig) * pow(10,i);
        //printf("%d\n", b);
        i++;
        c = c -> prev; 
    }

    return log(b);


}

