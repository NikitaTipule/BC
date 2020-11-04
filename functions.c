#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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

        // while(temp1 -> dig == 0) {
        //     if(temp1 -> next == NULL)
        //         return temp1;
        //     q = temp1;
        //     temp1 = temp1 -> next;
        //     temp1 -> prev = NULL;
        //     free(q);
        // }
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
        //print(larger(temp,a2));printf("\t");
        temp = sub(a2, temp);
        count++;
        print(temp);
        printf("\t");
        printf("%d\n", count);
    }
    print(larger(temp,a2));printf("\t");
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
    while(p ->top !=-1) {
        print(p->arr[p->top]);
        printf("\t");
        p ->top--;
    }
    printf("\n");
    p->top = i;
    return;
}