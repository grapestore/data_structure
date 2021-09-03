#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct Info{
    int count;
    struct Node *head;
    struct Node *tail;
}Info;

void rearadd1(Info *data, int value);
void rearadd2(Node *head , int value);
void finding(Node *head, int target);
void delete(Node *head, int target);
void insert(Node *head, int index, int value);
void add_first(Node *head, int value);


int main(){

    Node *head = malloc(sizeof(Node));
    //Info *data = malloc(sizeof(Info));
    
    head->next = NULL;
    // data->head = head;
    // data->tail = NULL;
    rearadd2(head, 10);
    rearadd2(head, 20);
    rearadd2(head, 30);
    
    finding(head, 20);
    delete(head,20);
    finding(head, 20);

    insert(head, 2, 20);
    finding(head, 20);

    add_first(head, 100);
    
    Node *curr = head->next;
    while(curr != NULL){
        printf("%d\n", curr->data);
        curr = curr->next;
    }

    Node *erase = head->next;
    while(erase != NULL){
        free(erase);
        erase = erase->next;
    }

    //system("leaks a.out");
    
}

// head 앞에 노드 삽입
void add_first(Node *head, int value){
    Node *newnode = malloc(sizeof(Node));
    newnode->data = value;
    newnode->next = head->next;
    head->next = newnode;
}

// 마지막 tail data를 저장하여 삽입하는 방법 시간복잡도 빠름
void rearadd1(Info *data, int value){

    Node *newnode = malloc(sizeof(Node));
    newnode->data = value;
    newnode->next = NULL;
    if(data->tail == NULL){
        data->head->next = newnode;
    }
    else{
        data->tail->next = newnode;
    }
    data->tail = newnode;
}

// head부터 탐색하여 마지막 노드에 삽입하는 방법
void rearadd2(Node *head , int value){
    Node *newnode = malloc(sizeof(Node));
    newnode->data = value;
    newnode->next = NULL;
    while(head->next!=NULL){
        head = head->next;
    }
    head->next = newnode;
}

// 원하는 value찾는 방법 탐색
void finding(Node *head, int target){
    Node *current = head->next;
    int count = 0;
    while(current->data != target){
        current = current->next;
        if(current==NULL){
            printf("no value\n");
            return;
        }
        count++;
    }
    printf("index: %d value: %d\n", count, current->data);
}

// 원하는 value 삭제하고 리스트 연결
void delete(Node *head, int target){
    Node *current = head->next;
    Node *pre_current = current;

    while(current->data != target){
        pre_current = current;
        current = current->next;
        if(current==NULL){
            printf("no target\n");
            return;
        }
    }
    pre_current->next = current->next;
    free(current);
}

void insert(Node *head, int index, int value){
    Node *newnode = malloc(sizeof(Node));
    newnode->data = value;
    Node *curr = head->next;
    Node *pre_curr = curr;
    int count = 0;
    while(count != index){
        pre_curr = curr;
        curr = curr->next;
        count++;
    }
    newnode->next = curr;
    pre_curr->next = newnode;
}
