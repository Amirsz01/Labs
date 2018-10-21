#include <stdio.h>
#define MAXLINE 1024
void main( void )
{
	FILE *fpin; // ������� ����
	FILE *fpout; // �������� ����
	char line[MAXLINE]; // ������� ������
	char *ptr;
	int lineNum = 0;
	int maxLineNum;
	int max_line = -1;
	int i = 0;
	fpin = fopen( "Input.txt", "rt" ); // ������� ���� ��� ������
	if( fpin == NULL )
		return; // ������ ��� �������� �����
	fpout = fopen("Output.txt", "wt" ); // ������� ���� ��� ������
	if( fpout == NULL )
		return; // ������ ��� �������� �����
	while( !feof( fpin ) )// ���� �� ����� �������� �����
	{
		ptr = fgets( line, MAXLINE, fpin ); // ������ ������
		if( ptr == NULL )
			break; // ���� ��������
		lineNum++;
		while( *ptr != '\0' ) // ���� �� ����� ������
		{
			i++;
			ptr++; // ���������� ��������� �� ������
		}
		if (i > max_line)
		{
			max_line = i;
			maxLineNum = lineNum;
		}
		i = 0;
	}
	fclose( fpin ); // ������� ������� ����
	fpin = fopen( "Input.txt", "rt" ); // ������� ���� ��� ������
	while( !feof( fpin ) )// ���� �� ����� �������� �����
	{
		ptr = fgets( line, MAXLINE, fpin ); // ������ ������
		if( ptr == NULL )
			break; // ���� ��������
		if(++i != maxLineNum)
		{
			fputs( line, fpout ); // ������ ������
		}
	}
	fclose( fpin ); // ������� ������� ����
	fclose( fpout ); // ������� �������� ����
}