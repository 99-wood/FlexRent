#include "voidlist.h"
#include <stdlib.h>
#include <stdio.h>

// ������ʼ��
void initVoidList(struct VoidList* list) {
    list->head = NULL;
    list->cnt = 0;
}

// ���Ԫ�ظ���������
int getVoidListCnt(struct VoidList* list) {
    return list->cnt;
}


// ��ѯ�Ƿ����ĳ��ֵ
bool findVoidListValue(struct VoidList* list, void* w) {
    struct VoidListNode* current = list->head;
    while (current != NULL) {
        // �Ƚ�ָ��ָ���ֵ
        if (*(int*)current->value == *(int*)w) {
            return true;
        }
        current = current->nxt;
    }
    return false;
}
// ������תΪ void* ���飬���������׵�ַ
void** VoidListToVoidArray(struct VoidList* list) {
    if (list->head == NULL) {
        printf("List is empty. No elements to convert.\n");
        return NULL;
    }

    // ����ռ�洢�����е�Ԫ��
    void** array = (void**)malloc(list->cnt * sizeof(void*));
    if (array == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // �������е�Ԫ�ظ��Ƶ�������
    struct VoidListNode* current = list->head;
    for (int i = 0; i < list->cnt; i++) {
        array[i] = current->value;
        current = current->nxt;
    }

    return array;
}

// �� int* ����תΪ��������������
struct VoidList* VoidArrayToVoidList(void* array[], int len) {
    // ��ʼ������
    struct VoidList* list = (struct VoidList*)malloc(sizeof(struct VoidList));
    if (list == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    initVoidList(list);

    // �������е�Ԫ�����β�������β��
    for (int i = 0; i < len; i++) {
        addVoidListTail(list, array[i]);
    }

    return list;
}

// ����ͷ������ڵ�
void addVoidListHead(struct VoidList* list, void* w) {
    struct VoidListNode* newNode = (struct VoidListNode*)malloc(sizeof(struct VoidListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->value = w;
    newNode->nxt = list->head;
    list->head = newNode;
    list->cnt++;
}

// ����β������ڵ�
void addVoidListTail(struct VoidList* list, void* w) {
    // �����½ڵ�
    struct VoidListNode* newNode = (struct VoidListNode*)malloc(sizeof(struct VoidListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->value = w;
    newNode->nxt = NULL;

    // �������Ϊ�գ����½ڵ�����Ϊ�׽ڵ�
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        // �����ҵ�����β���ڵ㣬�����½ڵ���뵽β���ڵ����
        struct VoidListNode* current = list->head;
        while (current->nxt != NULL) {
            current = current->nxt;
        }
        current->nxt = newNode;
    }
    list->cnt++;
}
// ���ض��ڵ�����ڵ�
void addVoidListNode(struct VoidList* list, struct VoidListNode* node, void* w) {
    // �����½ڵ�
    struct VoidListNode* newNode = (struct VoidListNode*)malloc(sizeof(struct VoidListNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->value = w;
    newNode->nxt = node->nxt;
    node->nxt = newNode;
    list->cnt++;
}
// ɾ������ͷ���ڵ�
void delVoidListHead(struct VoidList* list) {
    if (list->head == NULL) {
        printf("List is empty. No node to delete.\n");
        return;
    }
    struct VoidListNode* temp = list->head;
    list->head = list->head->nxt;
    free(temp);
    list->cnt--;
}

// ɾ������β���ڵ�
void delVoidListTail(struct VoidList* list) {
    if (list->head == NULL) {
        printf("List is empty. No node to delete.\n");
        return;
    }
    if (list->head->nxt == NULL) {
        // ����ֻ��һ���ڵ�����
        free(list->head);
        list->head = NULL;
    } else {
        struct VoidListNode* current = list->head;
        while (current->nxt->nxt != NULL) {
            current = current->nxt;
        }
        free(current->nxt);
        current->nxt = NULL;
    }
    list->cnt--;
}

// ɾ���ض��ڵ�
void delVoidListNode(struct VoidList* list, struct VoidListNode* node) {
    if (list->head == NULL) {
        printf("List is empty. No node to delete.\n");
        return;
    }
    if (node == list->head) {
        // ���Ҫɾ���Ľڵ���ͷ�ڵ�
        list->head = node->nxt;
        free(node);
    } else {
        // �����ҵ�Ҫɾ���ڵ��ǰһ���ڵ�
        struct VoidListNode* current = list->head;
        while (current != NULL && current->nxt != node) {
            current = current->nxt;
        }
        if (current == NULL) {
            printf("Node not found in the list.\n");
            return;
        }
        // ��ǰһ���ڵ��ָ��ָ��Ҫɾ���ڵ����һ���ڵ�
        current->nxt = node->nxt;
        // �ͷ�Ҫɾ���Ľڵ���ڴ�
        free(node);
    }
    list->cnt--;
}

// ɸѡ���������Ľڵ�
struct VoidList* filterVoidList(struct VoidList* list, bool (*check)(void*)) {
    // ��ʼ��������
    struct VoidList* filteredList = (struct VoidList*)malloc(sizeof(struct VoidList));
    if (filteredList == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    initVoidList(filteredList);

    // ����ԭ������ɸѡ���������Ľڵ㲢����������
    struct VoidListNode* current = list->head;
    while (current != NULL) {
        if (check(current->value)) {
            // �ڵ������������������������β��
            addVoidListTail(filteredList, current->value);
        }
        current = current->nxt;
    }

    return filteredList;
}


void clearVoidList(struct VoidList* list){
    for(struct VoidListNode * p = list -> head; p != NULL;){
        struct VoidListNode * nxt = p -> nxt;
        free(p);
        p = nxt;
    }
    list -> head = NULL;
    list -> cnt = 0;
    return;
}