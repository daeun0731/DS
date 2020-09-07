#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int ID;
    char *Name;
} Student;

typedef Student *DATATYPE;

typedef struct Node {
    DATATYPE data;
    struct Node *next;
} Node;

typedef struct {
    Node *Head;
    Node *Cur;
    Node *Tail;
    int NumofData;
    int (*Comp)(DATATYPE data1, DATATYPE data2);
} LinkedList;

void InitList(LinkedList *list);
int ComparePrecede(DATATYPE data1, DATATYPE data2);
void SetSortRule(LinkedList *list, int (*Comp)(DATATYPE data1, DATATYPE data2));

void SetStudentValue(Student *stu, int id, char *name);
void Insert(LinkedList *list, DATATYPE data);
void HeadInsert(LinkedList *list, DATATYPE data);
void SortInsert(LinkedList *list, DATATYPE data);

int RetCount(LinkedList *list);

int PosHead(LinkedList *list, DATATYPE *data);
int PosNext(LinkedList *list, DATATYPE *data);

void PrintStudent(Student *stu);

int CompareStudent(Student *stu, int id);

DATATYPE Remove(LinkedList *list);

void InitList(LinkedList *list) {
    list->Head=(Node*)malloc(sizeof(Node));
    list->Head->next=NULL;
    list->Comp=NULL;
    list->NumofData=0;
}

int ComparePrecede(DATATYPE data1, DATATYPE data2) {
    if (data1->ID < data2->ID) {
        return 0;
    }
    else {
        return 1;
    }
}

void SetSortRule(LinkedList *list, int (*Comp)(DATATYPE data1, DATATYPE data2)) {
        list->Comp=Comp;
}

void SetStudentValue(Student *stu, int id, char *name) {
    stu->ID=id;
    stu->Name=name;
}

void Insert(LinkedList *list, DATATYPE data) {
    if (list->Comp==NULL) {
        HeadInsert(list, data);
    }
    else {
        SortInsert(list, data);
    }
}

void HeadInsert(LinkedList *list, DATATYPE data) {
    Node *temp=(Node*)malloc(sizeof(Node));
    temp->data=data;

    temp->next=list->Head->next;
    list->Head->next=temp;

    list->NumofData++;
}

void SortInsert(LinkedList *list, DATATYPE data) {
    Node *new=(Node*)malloc(sizeof(Node));
    Node *pred=list->Head;
    new->data=data;

    while ((pred->next!=NULL)&&(list->Comp(data, pred->next->data)!=0)) {
        pred=pred->next;
    }

    new->next=pred->next;
    pred->next=new;

    list->NumofData++;
}

int RetCount(LinkedList *list) {
    return list->NumofData;
}

int PosHead(LinkedList *list, DATATYPE *data) {
    if (list->Head->next==NULL) {
        return FALSE;
    }

    list->Tail=list->Head;
    list->Cur=list->Head->next;

    *data=list->Cur->data;
    return TRUE;
}

int PosNext(LinkedList *list, DATATYPE *data) {
    if (list->Cur->next==NULL) {
        return FALSE;
    }

    list->Tail=list->Cur;
    list->Cur=list->Cur->next;

    *data=list->Cur->data;
    return TRUE;
}

void PrintStudent(Student *stu) {
    printf("ID : %d, Name : %s\n", stu->ID, stu->Name);
}

int CompareStudent(Student *stu, int id) {
    if (stu->ID==id) {
        return 1;
    }
    else {
        return 0;
    }
}

DATATYPE Remove(LinkedList *list) {
    Node *temp=list->Cur;
    DATATYPE tdata=temp->data;

    list->Tail->next=list->Cur->next;
    list->Cur=list->Tail;

    free(temp);
    list->NumofData--;
    return tdata;
}

int main(int argc, char *argv[]) {
    LinkedList list;
    Student *stu;
    int compID;

    InitList(&list);
    SetSortRule(&list, ComparePrecede); 

    stu=(Student*)malloc(sizeof(Student));
    SetStudentValue(stu, 2020200001, "test person1");
    Insert(&list, stu);

    stu=(Student*)malloc(sizeof(Student));
    SetStudentValue(stu, 2020200765, "test person2");
    Insert(&list, stu);

    stu=(Student*)malloc(sizeof(Student));
    SetStudentValue(stu, 2020300004, "test person3");
    Insert(&list, stu);

    stu=(Student*)malloc(sizeof(Student));
    SetStudentValue(stu, 2020200628, "test person4");
    Insert(&list, stu);

    stu=(Student*)malloc(sizeof(Student));
    SetStudentValue(stu, 2020200218, "test person5");
    Insert(&list, stu);

    printf("Num of datas %d\n", RetCount(&list));

    if (PosHead(&list, &stu)) {
        PrintStudent(stu);

        while (PosNext(&list, &stu)) {
            PrintStudent(stu);
        }
    }
    printf("\n");
    printf("\n");

    compID=2020200628;
    printf("Delete student node ID = %d\n", compID);
    printf("\n");

    if (PosHead(&list, &stu)) {
        if (CompareStudent(stu, compID)==1) {
            Remove(&list);
        }
        
        while (PosNext(&list, &stu)) {
            if (CompareStudent(stu, compID)==1) {
                Remove(&list);
            }
        }
    }

    printf("Num of datas %d\n", RetCount(&list));

    if (PosHead(&list, &stu)) {
        PrintStudent(stu);

        while (PosNext(&list, &stu)) {
            PrintStudent(stu);
        }
    }
    printf("\n");

    return 0;
}

