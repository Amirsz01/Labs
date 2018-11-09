#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define LETTER 1
#define NOT_THE_LETTER 0
#define MAXLEN 1000
void main(void)
{
	HANDLE hStdout; // дескриптор консольного окна
	FILE *fp; // входной файл
	char line[MAXLEN]; // строчка из файла
	char word[MAXLEN]; // слово
	int i;
	int flag; // флаг слово/разделитель
	int prev_flag; // предыдущее значение флага
	char *ptr; // указатель на строчку
	WORD foregroundColor0; // цвет слов
	WORD textAttribute; // атрибут текста - цвет символа и фона
	// Получить стандартный дескриптор
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	foregroundColor0 = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN;
	fp = fopen("test.txt", "rt");
	if (fp == NULL)
		return; // ошибка при открытии файла
	while (!feof(fp))
	{
		ptr = fgets(line, MAXLEN, fp);
		if (ptr == NULL)
			break;
		i = 0;
		prev_flag = flag = NOT_THE_LETTER;
		word[0] = '\0';
		while (*ptr != 0)
		{
			prev_flag = flag; // запомнить флаг
			if (*ptr == ' ' || *ptr == ',' || *ptr == '.' ||*ptr == '\n' || *ptr == '[' || *ptr == ']')
				flag = NOT_THE_LETTER;
			else
				flag = LETTER;
			if (flag != prev_flag)
			{
				word[i] = '\0';
				if (*ptr == '[') 
				{
					textAttribute = foregroundColor0;
					SetConsoleTextAttribute(hStdout, textAttribute);
				}
				else
				{
					SetConsoleTextAttribute(hStdout, 7);
				}
				printf("%s", word); // вывести слово
				i = 0; // начать новое слово
			}
			word[i++] = *ptr++; // запомнить символ
		}
		if (i != 0)
		{
			word[i] = '\0'; // закрыть слово
			printf("%s", word); // вывести слово
		}
	}
	printf("\n");
	system("pause");
}