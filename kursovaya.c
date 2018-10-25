#define _CRT_SECURE_NO_WARNINGS
#define MAXLEN 100
#define COUNT_CATEGORIES 8
#define YES 1
#define NO 0
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
struct item
{
	int id;
	char type[50];
	char name[MAXLEN];
	int price;
	struct item *ptr; // ��������� �� ��������� �������
};
/* ���������� ������ ������*/
struct item* init(int a) // ����������� ������ ��� ������ ������
{
	struct item *lst;
	lst = (struct item*)malloc(sizeof(struct item));
	lst->id = a;
	lst->ptr = NULL; // ��� ��������� ���� ������
	return(lst);
}

struct item * deleteHead(struct item *head)
{
	struct item *temp;
	temp = head->ptr;
	free(head); // ������������ ������ �������� �����
	return(temp); // ����� ������ ������
}

void deleteItem(struct item *lst, struct item *head)
{
	struct item *temp;
	temp = head;
	while (temp->ptr != lst) // ������������� ������ ������� � �����
	{ // ���� �� ������ ����, �������������� lst
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr; // ������������ ���������
	free(lst); // ����������� ������ ���������� ����
}

void freeStruct(struct item ** head)
{
	struct item * current = *head;
	struct item * next = NULL;
	do
	{
		next = current->ptr;
		free(current);
		current = next;
	} while (current != NULL);
	free(current);
}

struct item* Appendlist(struct item** headRef)
{
	struct item* current = *headRef;
	struct item* lst;
	lst = (struct item*)malloc(sizeof(struct item));
	lst->ptr = NULL;
	// ���� ������ ����
	if (current == NULL) {
		*headRef = lst;
	}
	else {
		// �����
		while (current->ptr != NULL) {
			current = current->ptr;
		}
		current->ptr = lst;
	}
	return(lst);
}

int strcmp(char *str1, char *str2)
{
	int i = 0;
	while (*str1 && *str2)
	{
		if (!(*str1 == *str2))
		{
			i++;
			if (*str1 < *str2)
			{
				i = -i;
			}
			break;
		}
		str1++;
		str2++;
	}
	if (!i) 
	{
		if (*str1 || *str2) 
		{
			if (!*str2)
				i = 1;
		}
	}
	return i;
}

void strcpy(char *str1, char *str2)
{
	int recordEnd = NO;
	char buf;
	char *end;
	while (!recordEnd)
	{
		if (*str1 == '\0')
		{
			end = str2;
			while (*str2) 
			{
				*str1++ = *str2++;
			}
			*str1 = '\0';
			*end = '\0';
			recordEnd = YES;
		}
		else
		{
			if (*str2 == '\0')
			{
				end = str1;
				while (*str1)
				{
					*str2++ = *str1++;
				}
				*str2 = '\0';
				*end = '\0';
				recordEnd = YES;
			}
			else
			{
				buf = *str1;
				*str1 = *str2;
				*str2 = buf;
				str1++;
				str2++;
			}
		}
	}
}

void structFor(struct item** headRef, int structType, int count)
{
	struct item* current;
	struct item* next;
	int noSwap;
	int iBuf;
	switch (structType)
	{
	case 1:
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->ptr;
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->name, next->name) > 0)
				{
					iBuf = current->id;
					current->id = next->id;
					next->id = iBuf;
					strcpy(current->name, next->name);
					strcpy(current->type, next->type);
					iBuf = current->price;
					current->price = next->price;
					next->price = iBuf;
					noSwap = 0;
				}
				current = current->ptr;
				next = current->ptr;
			}
			if (noSwap == 1)
				break;
		}
		break;
	case 2:
		for (int i = count - 1; i >= 0; i--)
		{
			current = *headRef;
			next = current->ptr;
			noSwap = 1;
			for (int j = 0; j < i; j++)
			{
				if (strcmp(current->type, next->type) > 0)
				{
					iBuf = current->id;
					current->id = next->id;
					next->id = iBuf;
					strcpy(current->name, next->name);
					strcpy(current->type, next->type);
					iBuf = current->price;
					current->price = next->price;
					next->price = iBuf;
					noSwap = 0;
				}
				current = current->ptr;
				next = current->ptr;
			}
			if (noSwap == 1)
				break;
		}
		break;
	default:
		break;
	}
}

int inputData(struct item** headRef)
{
	FILE *fpin;
	int mass[2];
	int dataNum;
	int itemNum = 0;
	int inItem = NO;
	int countItems = 0;
	int i = 0;
	char line[MAXLEN];
	struct item* item_ptr = NULL;
	fpin = fopen("test.txt", "r"); // ������� ���� ��� ������
	if (fpin == NULL)
		return 0; // ������ ��� �������� �����
	fscanf(fpin, "%d\n", &countItems);
	while (!feof(fpin))// ���� �� ����� �������� �����
	{
		fscanf(fpin, "%s\n", line);
		if (line == NULL)
			break; // ���� ��������
		if (*line == '{')
		{
			inItem = YES;
			itemNum++;
			if (itemNum == 1)
			{
				item_ptr = *headRef;
			}
			else
			{
				item_ptr = Appendlist(&(*headRef));
			}
			dataNum = 0;
			continue;
		}
		if (*line == '}')
		{
			inItem = NO;
			continue;
		}
		if (inItem)
		{
			i = -1;
			++dataNum;
			switch (dataNum)
			{
			case 1:
				item_ptr->id = atoi(line);
				break;
			case 2:
				do
				{
					i++;
					item_ptr->type[i] = line[i];
				} while (line[i] != '\0');
				break;
			case 3:
				do
				{
					i++;
					item_ptr->name[i] = line[i];
				} while (line[i] != '\0');
				break;
			case 4:
				item_ptr->price = atoi(line);
				break;
			}
		}
	}
	fclose(fpin); // ������� ������� ����
	mass[0] = itemNum;
	mass[1] = countItems;
	return &mass;
}

void recordData(struct item** headRef, int itemNum) 
{
	FILE *fpin;
	struct item* current = *headRef;
	fpin = fopen("test.txt", "w"); // ������� ���� ��� ������
	fprintf(fpin, "%d\n", itemNum);
	while (current != NULL) 
	{
		fprintf(fpin, "{\n");
		fprintf(fpin, "%d\n", current->id);
		fprintf(fpin, "%s\n", current->type);
		fprintf(fpin, "%s\n", current->name);
		fprintf(fpin, "%d\n", current->price);
		fprintf(fpin, "}\n");
		current = current->ptr;
	}
	fclose(fpin); // ������� ������� ����
}

void main(void)
{
	struct item* head_ptr = init(0);
	/* ���������� ������ ������*/
	struct item* item_ptr = NULL;
	/* ���������� ��������� ����������*/
	char callback_name[MAXLEN];
	char categories[COUNT_CATEGORIES][50] = {"����","��������", "������", "�������", "�������", "��������", "�����", "������"};
	/* ���������� �������� ����������*/
	int itemNum;
	int countItems;
	int i=0;
	int callback_type;
	int callback_main;
	int callback_price;
	int callback_item;
	int callback_printType;
	int callback_basketTypes[COUNT_CATEGORIES+1];
	int *returnData;
	/* ���������� ���������� �������*/
	system("chcp 1251");
	system("cls");
	returnData = inputData(&head_ptr);
	countItems = *(returnData+1);
	itemNum = *returnData;
	do
	{
		system("cls");
		printf("[0] ����� �� ���������\n[1] �������� ����� �����\n[2] ������������� �����\n[3] ������� �����\n[4] ������� ������ � ���������� �������\n[5] ��������� ����������� ����� �������\n�������� ����� �� ������ : ");
		scanf("%d", &callback_main);
		switch (callback_main) {
		case 1: 
			system("cls");
			for (i = 0; i < COUNT_CATEGORIES; i++) 
			{
				printf("[%d] %s\n", i+1, &categories[i]);
			}
			printf("�������� ��� ������ : ");
			scanf("%d", &callback_type);
			system("cls");
			printf("������� �������� ������ : ");
			scanf("%s", &callback_name);
			system("cls");
			printf("������� ���� ������ : ");
			scanf("%d", &callback_price);
			countItems++;
			if (itemNum == 0)
			{
				item_ptr = head_ptr;
			}
			else
			{
				item_ptr = Appendlist(&head_ptr);
			}
			item_ptr->id = countItems;
			item_ptr->price = callback_price;
			i = -1;
			do
			{
				i++;
				item_ptr->name[i] = callback_name[i];
			} while (callback_name[i] != '\0');
			i = -1;
			do
			{
				i++;
				item_ptr->type[i] = categories[callback_type-1][i];
			} while (categories[callback_type - 1][i] != '\0');
			itemNum++;
			break;
		case 2:
			system("cls");
			if (!itemNum)
			{
				printf("��� �������\n");
				system("pause");
				break;
			}
			printf("�������� �����, ������� ������ �������� : \n");
			item_ptr = head_ptr;
			i = 1;
			while (item_ptr != NULL)
			{
				printf("[%d] %s\n", i, item_ptr->name);
				i++;
				item_ptr = item_ptr->ptr;
			}
			item_ptr = head_ptr;
			scanf("%d", &callback_item);
			for ( i = 0; i < callback_item - 1; i++)
			{
				item_ptr = item_ptr->ptr;
			}
			system("cls");
			printf("������ ��� ������ : %s\n--------------\n", item_ptr->type);
			for (i = 0; i < COUNT_CATEGORIES; i++)
			{
				printf("[%d] %s\n", i + 1, &categories[i]);
			}
			printf("������� ����� ��� ������ : ");
			scanf("%d", &callback_type);
			system("cls");
			printf("������ �������� ������ : %s\n������� ����� �������� ������ : ", item_ptr->name);
			scanf("%s", &callback_name);
			system("cls");
			printf("������ ����: %d\n������� ����� ���� ������ : ", item_ptr->price);
			scanf("%d", &callback_price);
			item_ptr->price = callback_price;
			i = -1;
			do
			{
				i++;
				item_ptr->name[i] = callback_name[i];
			} while (callback_name[i] != '\0');
			i = -1;
			i = -1;
			do
			{
				i++;
				item_ptr->type[i] = categories[callback_type - 1][i];
			} while (categories[callback_type - 1][i] != '\0');
			break;
		case 3:
			system("cls");
			if (!itemNum)
			{
				printf("��� �������\n");
				system("pause");
				break;
			}
			printf("�������� �����, ������� ������ ������� : \n");
			item_ptr = head_ptr;
			i = 1;
			while (item_ptr != NULL)
			{
				printf("[%d] %s\n", i, item_ptr->name);
				i++;
				item_ptr = item_ptr->ptr;
			}
			scanf("%d", &callback_item);
			item_ptr = head_ptr;
			for (i = 0; i < callback_item - 1; i++)
			{
				item_ptr = item_ptr->ptr;
			}
			if (callback_item == 1)
			{
				head_ptr = deleteHead(item_ptr);
			}
			else
			{
				deleteItem(item_ptr, head_ptr);
			}
			itemNum--;
			break;
		case 4:
			system("cls");
			if (!itemNum)
			{
				printf("��� �������\n");
				system("pause");
				break;
			}
			printf("�������� �� ������ �������� �������� ������ : \n");
			printf("[1] �� ��������\n[2] �� ����\n");
			scanf("%d", &callback_printType);
			system("cls");
			structFor(&head_ptr, callback_printType, itemNum);
			item_ptr = head_ptr;
			i = 1;
			while (item_ptr != NULL)
			{
				printf("------[%d]------\n", i);
				printf("ID: %d\n", item_ptr->id);
				printf("���: %s\n", item_ptr->type);
				printf("��������: %s\n", item_ptr->name);
				printf("����: %d\n", item_ptr->price);
				i++;
				item_ptr = item_ptr->ptr;
			}
			system("pause");
			break;
		case 5:
			system("cls");
			if (!itemNum)
			{
				printf("��� �������\n");
				system("pause");
				break;
			}
			for (i = 0; i < COUNT_CATEGORIES; i++)
			{
				printf("[%d] %s\n", i + 1, &categories[i]);
			}
			printf("�������� ���� ������� ��� ����������� �������\n������� �� ������ ����. ����� ��������� �����, ������� 0\n");
			i = 0;
			do
			{
				scanf("%d", &callback_basketTypes[i]);
				if (i) 
				{
					for (int j = 0; j < i; j++)
						if (callback_basketTypes[j] == callback_basketTypes[i])
						{
							printf("����� ��� ������ ��� ����� � �������. �������� ������ ��� ��������� �����.\n");
							i--;
						}
				}
				i++;
			} while (callback_basketTypes[i-1]);
			system("cls");
			i = 0;
			while (callback_basketTypes[i])
			{
				int max = 100000;
				struct item *max_ptr = NULL;
				item_ptr = head_ptr;
				while (item_ptr != NULL)
				{
					if (!strcmp(item_ptr->type, categories[callback_basketTypes[i]-1]))
					{
						if (item_ptr->price < max) 
						{
							max = item_ptr->price;
							max_ptr = item_ptr;
						}
					}
					item_ptr = item_ptr->ptr;
				}
				i++;
				if (!(max_ptr == NULL))
				{
					printf("------[%d]------\n", i);
					printf("ID: %d\n", max_ptr->id);
					printf("���: %s\n", max_ptr->type);
					printf("��������: %s\n", max_ptr->name);
					printf("����: %d\n", max_ptr->price);
				}

			}
			system("pause");
			break;
		default:
			break;
		};
	} while (callback_main);
	if (itemNum) 
	{
		recordData(&head_ptr, countItems);
	}
	freeStruct(&head_ptr);
	system("pause");
}