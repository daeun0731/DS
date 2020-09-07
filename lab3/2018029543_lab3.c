#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define TRUE 1
#define FALSE 0
#define EMPTY -1

typedef char DATATYPE;

typedef struct NODE {
    DATATYPE data;
    struct NODE *next;
} NODE;

typedef struct {
    NODE *head;
} ListStack;

void InitStack(ListStack *stack);
int IsEmpty(ListStack *stack);

void Push(ListStack *stack, DATATYPE data);
DATATYPE Pop(ListStack *stack);
DATATYPE Peek(ListStack *stack);

void ConvertExp(char exp[]);
int GetOperatorPriority(char op);
int CompareOperatorPriority(char op1, char op2);
int EvalExp(char exp[]);

void InitStack(ListStack *stack) {
    stack->head=NULL;
}

int IsEmpty(ListStack *stack) {
    if (stack->head == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void Push(ListStack *stack, DATATYPE data) {
    NODE *temp = (NODE*)malloc(sizeof(NODE));

    temp->data=data;
    temp->next=stack->head;
 
    stack->head=temp;
}

DATATYPE Pop(ListStack *stack) {
    DATATYPE tempData;
    NODE *temp;

    if (IsEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }

    tempData=stack->head->data;
    temp=stack->head;

    stack->head=stack->head->next;
    free(temp);

    return tempData;
}

DATATYPE Peek(ListStack *stack) {
    if (IsEmpty(stack)) {
        printf("Stack is empty\n");
        exit(1);
    }
    
    return stack->head->data;
}

void ConvertExp(char exp[]) {
    int len=strlen(exp);
    char *ans=(char*)malloc(len+1);

    ListStack stack;
    InitStack(&stack);

    int count=0;
    for (int i=0;i<len;i++) {
        if (isdigit(exp[i])!=FALSE) {
            ans[count]=exp[i];
            count++;
        }
        else if (exp[i]=='(' || IsEmpty(&stack) || CompareOperatorPriority(exp[i], Peek(&stack)!=-1)) {
            Push(&stack, exp[i]);
        }
        else if (exp[i]==')') {
            while (Peek(&stack)!='(') {
                ans[count]=Pop(&stack);
                count++;
            }
            Pop(&stack);
        }
        else {
            ans[count]=exp[i];
            count++;
        }
    }

    while (IsEmpty(&stack)!=1) {
        ans[count]=Pop(&stack);
        count++;
    }
    
    strcpy(exp,ans);
    free(ans);
}


int GetOperatorPriority(char op) {
    if (op=='*'||op=='/') {
        return 5;
    }
    else if (op=='+'||op=='-') {
        return 3;
    }
    else if (op=='(') {
        return 1;
    }
    else {
        return -1;
    }
}

int CompareOperatorPriority(char op1, char op2) {
    if (GetOperatorPriority(op1) > GetOperatorPriority(op2)) {
        return 1;
    }
    else if (GetOperatorPriority(op1) < GetOperatorPriority(op2)) {
        return -1;
    }
    else {
        return 0;
    }
}

int EvalExp(char exp[]){
    ListStack stack;
    InitStack(&stack);
    
    int len=strlen(exp);
    int a;
    int b;
    int temp;

    for (int i=0;i<len;i++) {
        if (isdigit(exp[i])!=FALSE) {
            Push(&stack, exp[i]);
        }
        else {
            b=Pop(&stack)-'0';
            a=Pop(&stack)-'0';

            if (exp[i]=='+') {
                temp=a+b+'0';
                Push(&stack, temp);
            }

            else if (exp[i]=='-') {
                temp=a-b+'0';
                Push(&stack, temp);
            }

            else if (exp[i]=='*') {
                temp=a*b+'0';
                Push(&stack, temp);
            }
            else {
                temp=a/b+'0';
                Push(&stack, temp);
            }
        }
    }
    return Peek(&stack)-'0';
}

int main(int argc, char *argv[]) {
    char ex1[]="1+2*3";
    char ex2[]="(1+2)*3";
    char ex3[]="((1-2)+3)*(5-2)";

    ConvertExp(ex1);
    ConvertExp(ex2);
    ConvertExp(ex3);

    int ans1=EvalExp(ex1);
    int ans2=EvalExp(ex2);
    int ans3=EvalExp(ex3);

    printf("%s = %d\n", ex1, ans1);
    printf("%s = %d\n", ex2, ans2);
    printf("%s = %d\n", ex3, ans3);

    return 0;
}
