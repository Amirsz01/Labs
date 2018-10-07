#include <stdio.h>
#define YES 1
#define NO 0
#define MAXLINE 1000
void process_line( char buffer[] );
void main( void )
{
	char line[MAXLINE];
	fgets(line,sizeof(line),stdin);
	process_line( line );
	puts( line );
}
void process_line( char buffer[] )
{
	char *buf_ptr;
	char *end;
	char *begin;
	char c;
	char prev_c;
	int flag;
	int found;
	int obr;
	obr = YES;
	flag = NO;
	found = NO;
	prev_c = ' ';
	buf_ptr = buffer;
	begin = buffer;
	end = buffer;
	do
	{
		c = *buf_ptr;
		if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')))
		{
			if( flag == YES && obr == YES)
			{
				end = buf_ptr - 1;
				if( found == YES )
				{
					char *src = end + 1;
					char *dst = begin;
					while( (*dst++ = *src++ ) != '\0' );
					buf_ptr = begin;
				}
			}
			flag = NO;
			found = NO;
			obr = YES;
		}
		else
		{
			if( flag == NO ){
				begin = buf_ptr;
				flag = YES;
			}
			if(((prev_c == 'a') || (prev_c == 'e') || (prev_c == 'o') || (prev_c == 'u') || (prev_c == 'y')) && ((c == 'a') || (c == 'e') || (c == 'o') || (c == 'u') || (c == 'y')))
			{
					found = YES;
			}
			if(c >= '0' && c <= '9')
			obr = NO;
		}
		prev_c = c;
		buf_ptr++;
	}
	while( c != '\0' );
}
