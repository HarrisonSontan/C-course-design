// Ԥ����ָ����ڽ���ĳЩ�����İ�ȫ�Ծ���
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// �洢�й�ͼ�����Ϣ�Ľṹ��
struct bookInfo
{
    char name[20];   // ����
    float price;     // ��۸�
    int num;         // �������
};

// ����ڵ�ṹ��
struct Node
{
    struct bookInfo data;  // �����򣬰����鼮��Ϣ
    struct Node* next;     // ָ����ָ�������е���һ���ڵ�
};

// ȫ������
struct Node* list = NULL;

// ��������ͷ
struct Node* createHead()
{
    // ��̬�����ڴ��ͷ���
    struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
    // ��ʼ��
    headNode->next = NULL;
    // ����ͷ���
    return headNode;
}

// �����ڵ㣬׼������
// ���û�������ת��Ϊ�ṹ�����
struct Node* createNode(struct bookInfo data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// ͷ�巨����������
void insertNodeLeft(struct Node* headNode, struct bookInfo data)
{
    struct Node* newNode = createNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}

// ��ָ��λ��ɾ���ڵ�
void deleteNodeByName(struct Node* headNode, char* bookname)
{
    struct Node* posLeftNode = headNode;
    struct Node* posNode = headNode->next;

    // �鼮�����ַ�����ʹ���ַ����ȽϺ���
    while (posNode != NULL && strcmp(posNode->data.name, bookname))
    {
        posNode = posNode->next;
        posLeftNode = posLeftNode->next;
    }

    if (posNode == NULL)
    {
        printf("δ�ҵ�Ҫɾ�����鼮��\n");
        return;
    }
    else
    {
        printf("ɾ���ɹ���\n");
        posLeftNode->next = posNode->next;
        free(posNode);
        posNode = NULL;
    }
}

struct Node* searchByName(struct Node* headNode, char* bookName)
{
    struct Node* posNode = headNode->next;

    while (posNode != NULL && strcmp((posNode->data.name), bookName))
    {
        posNode = posNode->next;
    }

    return posNode;
}

// ��ӡ����
void printList(struct Node* headNode)
{
    struct Node* pMove = headNode->next;
    printf("����\t\t\t�۸�\t����\n");

    while (pMove != NULL)
    {
        // ʹ���Ʊ�����ֶο�������ֶ���
        printf("%-20s\t%.1f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
        pMove = pMove->next;
    }
}

// �˵�
void Menu()
{
    printf("----------------------------------------------\n");
    printf("          ����ͼ�����ϵͳ\n");
    printf("----------------------------------------------\n");
    printf("\t0. �˳�ϵͳ\n");
    printf("\t1. ����鼮\n");
    printf("\t2. ����鼮\n");
    printf("\t3. �����鼮\n");
    printf("\t4. �黹�鼮\n");
    printf("\t5. �鼮����\n");
    printf("\t6. ɾ���鼮\n");
    printf("\t7. �����鼮\n");
    printf("----------------------------------------------\n");
    printf("����������Ҫ�Ĺ��ܣ�");
}

// �ļ�����
// �ļ�д���������ڴ��е�����д�����txt��
void saveInfoToFile(const char* fileName, struct Node* headNode)
{
    FILE* fp = fopen(fileName, "w");
    struct Node* pMove = headNode->next;

    while (pMove != NULL)
    {
        fprintf(fp, "%s\t%f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
        pMove = pMove->next;
    }

    fclose(fp);
}

// �ļ��������������txt�е����ݶ����ڴ棩
void readInfoFromFile(const char* fileName, struct Node* headNode)
{
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        // ����ļ������ڣ�������
        fp = fopen(fileName, "w+");
    }

    struct bookInfo tempData;

    // ���ļ��ж�ȡ���ݲ�����ڵ㵽������
    while (fscanf(fp, "%s\t%f\t%d\n", tempData.name, &tempData.price, &tempData.num) != EOF)
    {
        insertNodeLeft(list, tempData);
    }

    fclose(fp);
}

// ð������
void bubbleSortList(struct Node* headNode)
{
    for (struct Node* p = headNode->next; p != NULL; p = p->next)
    {
        for (struct Node* q = headNode->next; q->next != NULL; q = q->next)
        {
            if (q->data.price > q->next->data.price)
            {
                // ����ֵ
                struct bookInfo tempData = q->data;
                q->data = q->next->data;
                q->next->data = tempData;
            }
        }
    }

    // ��ӡ����������
    printList(headNode);
}

// ����
void Key()
{
    int userKey = 0;
    struct bookInfo tempBook;  // ��ʱ�����洢�鼮��Ϣ
    struct Node* result = NULL;

    // ��ȡ�û�����
    scanf("%d", &userKey);

    switch (userKey)
    {
    case 0:
        printf("���ɹ��˳���\n");
        system("pause");
        exit(0);
        break;
    case 1:
        printf("������鼮��\n");
        printf("�����鼮����Ϣ����ʽ���£�\nname price num:");
        scanf("%s%f%d", tempBook.name, &tempBook.price, &tempBook.num);
        insertNodeLeft(list, tempBook);
        // д�ļ������ڴ��е�����д�����txt��
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 2:
        printf("������鼮��\n");
        printList(list);
        break;
    case 3:
        printf("�������鼮��\n");
        printf("������Ҫ���ĵ�������");
        scanf("%s", tempBook.name);
        result = searchByName(list, tempBook.name);
        if (result == NULL)
        {
            printf("û������鼮�޷����ģ�\n");
        }
        else
        {
            if (result->data.num > 0)
            {
                result->data.num--;
                printf("���ĳɹ���\n");
            }
            else
            {
                printf("��ǰ�鼮�޿�棬����ʧ�ܣ�\n");
            }
        }
        // д�ļ������ڴ��е�����д�����txt��
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 4:
        printf("���黹�鼮��\n");
        printf("������Ҫ�黹��������");
        scanf("%s", tempBook.name);
        result = searchByName(list, tempBook.name);
        if (result == NULL)
        {
            printf("������Դ�Ƿ���\n");
        }
        else
        {
            result->data.num++;
            printf("�鼮�黹�ɹ���\n");
        }
        // д�ļ������ڴ��е�����д�����txt��
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 5:
        printf("���鼮����\n");
        bubbleSortList(list);
        // д�ļ������ڴ��е�����д�����txt��
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 6:
        printf("��ɾ���鼮��\n");
        printf("������Ҫɾ���鼮�����֣�");
        scanf("%s", tempBook.name);
        deleteNodeByName(list, tempBook.name);
        // д�ļ������ڴ��е�����д�����txt��
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 7:
        printf("�������鼮��\n");
        printf("������Ҫ���ҵ�������");
        scanf("%s", tempBook.name);
        // ������ұ���
        result = searchByName(list, tempBook.name);
        if (result == NULL)
        {
            printf("δ�ҵ������Ϣ!");
        }
        else
        {
            printf("����\t�۸�\t����\n");
            printf("%s\t%f\t%d\n", result->data.name, result->data.price, result->data.num);
        }
        break;
    default:
        printf("����������������룡\n");
        break;
    }
}

// ������
int main()
{
    list = createHead();
    // �ڴ��뿪ʼʱ���ļ�����
    readInfoFromFile("booklinfo.txt", list);

    while (1)
    {
        Menu();
        Key();
        system("pause");
        system("cls");
    }
    return 0;
}
