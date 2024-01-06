// 预处理指令，用于禁用某些函数的安全性警告
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 存储有关图书的信息的结构体
struct bookInfo
{
    char name[20];   // 书名
    float price;     // 书价格
    int num;         // 书的数量
};

// 链表节点结构体
struct Node
{
    struct bookInfo data;  // 数据域，包含书籍信息
    struct Node* next;     // 指针域，指向链表中的下一个节点
};

// 全局链表
struct Node* list = NULL;

// 创建链表头
struct Node* createHead()
{
    // 动态分配内存给头结点
    struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
    // 初始化
    headNode->next = NULL;
    // 返回头结点
    return headNode;
}

// 创建节点，准备插入
// 将用户的数据转换为结构体变量
struct Node* createNode(struct bookInfo data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 头插法创建单链表
void insertNodeLeft(struct Node* headNode, struct bookInfo data)
{
    struct Node* newNode = createNode(data);
    newNode->next = headNode->next;
    headNode->next = newNode;
}

// 按指定位置删除节点
void deleteNodeByName(struct Node* headNode, char* bookname)
{
    struct Node* posLeftNode = headNode;
    struct Node* posNode = headNode->next;

    // 书籍名是字符串，使用字符串比较函数
    while (posNode != NULL && strcmp(posNode->data.name, bookname))
    {
        posNode = posNode->next;
        posLeftNode = posLeftNode->next;
    }

    if (posNode == NULL)
    {
        printf("未找到要删除的书籍。\n");
        return;
    }
    else
    {
        printf("删除成功！\n");
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

// 打印链表
void printList(struct Node* headNode)
{
    struct Node* pMove = headNode->next;
    printf("书名\t\t\t价格\t数量\n");

    while (pMove != NULL)
    {
        // 使用制表符和字段宽度来保持对齐
        printf("%-20s\t%.1f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
        pMove = pMove->next;
    }
}

// 菜单
void Menu()
{
    printf("----------------------------------------------\n");
    printf("          简易图书管理系统\n");
    printf("----------------------------------------------\n");
    printf("\t0. 退出系统\n");
    printf("\t1. 添加书籍\n");
    printf("\t2. 浏览书籍\n");
    printf("\t3. 借阅书籍\n");
    printf("\t4. 归还书籍\n");
    printf("\t5. 书籍排序\n");
    printf("\t6. 删除书籍\n");
    printf("\t7. 查找书籍\n");
    printf("----------------------------------------------\n");
    printf("请输入您需要的功能：");
}

// 文件操作
// 文件写操作（将内存中的数据写入外存txt）
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

// 文件读操作（将外存txt中的数据读入内存）
void readInfoFromFile(const char* fileName, struct Node* headNode)
{
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL)
    {
        // 如果文件不存在，创建它
        fp = fopen(fileName, "w+");
    }

    struct bookInfo tempData;

    // 从文件中读取数据并插入节点到链表中
    while (fscanf(fp, "%s\t%f\t%d\n", tempData.name, &tempData.price, &tempData.num) != EOF)
    {
        insertNodeLeft(list, tempData);
    }

    fclose(fp);
}

// 冒泡排序
void bubbleSortList(struct Node* headNode)
{
    for (struct Node* p = headNode->next; p != NULL; p = p->next)
    {
        for (struct Node* q = headNode->next; q->next != NULL; q = q->next)
        {
            if (q->data.price > q->next->data.price)
            {
                // 交换值
                struct bookInfo tempData = q->data;
                q->data = q->next->data;
                q->next->data = tempData;
            }
        }
    }

    // 打印排序后的链表
    printList(headNode);
}

// 交互
void Key()
{
    int userKey = 0;
    struct bookInfo tempBook;  // 临时变量存储书籍信息
    struct Node* result = NULL;

    // 读取用户输入
    scanf("%d", &userKey);

    switch (userKey)
    {
    case 0:
        printf("【成功退出】\n");
        system("pause");
        exit(0);
        break;
    case 1:
        printf("【添加书籍】\n");
        printf("输入书籍的信息（格式如下）\nname price num:");
        scanf("%s%f%d", tempBook.name, &tempBook.price, &tempBook.num);
        insertNodeLeft(list, tempBook);
        // 写文件（将内存中的数据写入外存txt）
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 2:
        printf("【浏览书籍】\n");
        printList(list);
        break;
    case 3:
        printf("【借阅书籍】\n");
        printf("请输入要借阅的书名：");
        scanf("%s", tempBook.name);
        result = searchByName(list, tempBook.name);
        if (result == NULL)
        {
            printf("没有相关书籍无法借阅！\n");
        }
        else
        {
            if (result->data.num > 0)
            {
                result->data.num--;
                printf("借阅成功！\n");
            }
            else
            {
                printf("当前书籍无库存，借阅失败！\n");
            }
        }
        // 写文件（将内存中的数据写入外存txt）
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 4:
        printf("【归还书籍】\n");
        printf("请输入要归还的书名：");
        scanf("%s", tempBook.name);
        result = searchByName(list, tempBook.name);
        if (result == NULL)
        {
            printf("该书来源非法！\n");
        }
        else
        {
            result->data.num++;
            printf("书籍归还成功！\n");
        }
        // 写文件（将内存中的数据写入外存txt）
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 5:
        printf("【书籍排序】\n");
        bubbleSortList(list);
        // 写文件（将内存中的数据写入外存txt）
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 6:
        printf("【删除书籍】\n");
        printf("请输入要删除书籍的名字：");
        scanf("%s", tempBook.name);
        deleteNodeByName(list, tempBook.name);
        // 写文件（将内存中的数据写入外存txt）
        saveInfoToFile("booklinfo.txt", list);
        break;
    case 7:
        printf("【查找书籍】\n");
        printf("请输入要查找的书名：");
        scanf("%s", tempBook.name);
        // 链表查找遍历
        result = searchByName(list, tempBook.name);
        if (result == NULL)
        {
            printf("未找到相关信息!");
        }
        else
        {
            printf("书名\t价格\t数量\n");
            printf("%s\t%f\t%d\n", result->data.name, result->data.price, result->data.num);
        }
        break;
    default:
        printf("输入错误，请重新输入！\n");
        break;
    }
}

// 主函数
int main()
{
    list = createHead();
    // 在代码开始时将文件导入
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
