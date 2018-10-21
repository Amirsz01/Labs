#include <stdio.h>
#define MAXLINE 1024
void main( void )
{
	FILE *fpin; // входной файл
	FILE *fpout; // выходной файл
	char line[MAXLINE]; // текущая строка
	char *ptr;
	int lineNum = 0;
	int maxLineNum;
	int max_line = -1;
	int i = 0;
	fpin = fopen( "Input.txt", "rt" ); // открыть файл для чтения
	if( fpin == NULL )
		return; // ошибка при открытии файла
	fpout = fopen("Output.txt", "wt" ); // открыть файл для записи
	if( fpout == NULL )
		return; // ошибка при открытии файла
	while( !feof( fpin ) )// цикл до конца входного файла
	{
		ptr = fgets( line, MAXLINE, fpin ); // чтение строки
		if( ptr == NULL )
			break; // файл исчерпан
		lineNum++;
		while( *ptr != '\0' ) // цикл до конца строки
		{
			i++;
			ptr++; // продвигаем указатель по строке
		}
		if (i > max_line)
		{
			max_line = i;
			maxLineNum = lineNum;
		}
		i = 0;
	}
	fclose( fpin ); // закрыть входной файл
	fpin = fopen( "Input.txt", "rt" ); // открыть файл для чтения
	while( !feof( fpin ) )// цикл до конца входного файла
	{
		ptr = fgets( line, MAXLINE, fpin ); // чтение строки
		if( ptr == NULL )
			break; // файл исчерпан
		if(++i != maxLineNum)
		{
			fputs( line, fpout ); // запись строки
		}
	}
	fclose( fpin ); // закрыть входной файл
	fclose( fpout ); // закрыть выходной файл
}