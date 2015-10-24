#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <basetsd.h>
#include <Windows.h>
#include <winnt.h>

void textcolor(int color_number) { // 가져온 함수(글자 색 바꾸기)
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}
/*
여기에서 맨 뒤에 두자리, 즉 16진수로 0x0000 ~ 0x00FF까지가 이 함수에서 의미있는 매개 변수 이다.

각 16진수에 해당하는 색은 다음과 같다.
0 - 검정색, 1 - 파랑색, 2 - 초록색, 3 - 옥색, 4 - 빨간색, 5 - 자주색, 6 - 노랑색, 7 - 흰색, 8 - 회색,
9 - 연한 파랑색, A - 연한 초록색, B - 연한 옥색, C - 연한 빨간색, D - 연한 자주색, E - 연한 노랑색, F - 밝은 흰색

즉, [밝은 흰색]의 음영색을 가진 [빨간색]의 글자를 출력하고 싶다면
0x00F4 라는 매개변수 값을 넘겨주면 되는 것이다.
*/

void intro() {   // 프로그램 초기 화면
		printf("          ..........    @ @   @     @    @ @   @                   ..........\n\
          .........    @   @  @ @   @   @  @   @                   .........\n\
           ........    @@@@@@ @   @ @  @@@@@@  @                   ........\n\
           ......     @     @ @     @ @     @  @@@@@@             ........\n\
           .....      ----------------------------                .......\n\
            ....        by J U N Y O U N G                        .....\n\
            ...       ----------------------------                ....\n\
            ..          &&&         $$$$$                         ...\n\
            ==          &  &        $                            ==\n\
          __||__        &&&&        $$$$$                      __||__\n\
         |      |       &           $                         |      |\n\
_________|______|_____  &   ortable $$$$$ xcutable       _____|______|_________\n\n");

		textcolor(0x0f);   // white
		printf("This program view the Windows 32bit Portable Excutable File's struct member. \n");
		printf("I want P.romote E.xperience in this project! \n");

		textcolor(0x0A);   // green
		printf("You can Copy Modify Distribute this program. \n\n");

		textcolor(0x0F);   // white
		printf("usage > AnalPE [option] filename \n\n");

		textcolor(0x0E);   // yellow
		printf("Option \n");

		textcolor(0x0F);   // white
		printf("-s: save the result to file \n");
		printf("-q: shut up \n\n");

		printf("Copyright 2015 \n");
}

void show_Allhex(char* str, FILE* input)   // 추가 할꺼: fseek
{
	 unsigned char hex;
	 int i, j;

	 char temp[17];

	 system("cls");

	 fseek(input, 0, SEEK_SET);
	 i = 0;

	 while(!feof(input)) {
		 hex = fgetc(input);

		 temp[i%16] = hex;

		 if(i%16 == 0) {
			 printf("%08x ", i);
		 }
		 printf("%02x ", hex);
		
		 if(i%8 == 7) {
			putchar(' ');
		 }
		 if(i%16 == 15) {
			 temp[16] = '\0';
			 printf("  ");

			 for(j=0; j<17; j++) {
				 if(temp[j] >= 0x21 && temp[j] <= 0x7E) {   // 출력 가능한 문자
					 putchar(temp[j]);
				 } else {
					 putchar('.');
				 }
			 }

			 putchar('\n');
		 }
		 if(i%336 == 335) {
			 printf("\nPress 'q' to Quit! \n");

			 if(getch() == 'q') {
				return;
			 }
		 }

		 i++;
	 }
}

void show_fileMemMap(char* str, FILE* input)
{
	printf("show file/Memory Map \n");
}

void show_DosHeader(char* str, FILE* input)
{
	int i, j;
	char* ptr;
	unsigned int tempi;
	unsigned short temps;

	char* varName[19] = { "e_magic", "e_cblp", "e_cp", "e_crlc", "e_cparhdr", "e_minalloc", "e_maxalloc", "e_ss", "e_sp", "e_csum", "e_ip", "e_cs", "e_lfarlc", "e_ovno", "e_res[4]", "e_oemid", "e_oeminfo", "e_res2[10]", "e_lfanew" };

	do {
		system("cls");
		printf("typedef struct _IMAGE_DOS_HEADER {   \n");
		for (i = 0; i < sizeof(varName) / sizeof(char *); i++) {
			if (!strcmp(varName[i], "e_magic")) {
				printf("%10s %10s = ", "WORD", varName[i]);

				fseek(input, 0, SEEK_SET);
				ptr = &temps;
				for (j = 0; j < 2; j++) {
					*(ptr++) = fgetc(input);
				}

				printf("%8X", temps, str);

				ptr = &temps;

				putchar('(');
				for (j = 0; j < 2; j++) {
					putchar(*(ptr++));
				}
				printf(") \n");
			}
			else if (!strcmp(varName[i], "e_lfanew")) {
				printf("%10s %10s = ", "LONG", varName[i]);

				fseek(input, 0x3C, SEEK_SET);
				ptr = &tempi;
				for (j = 0; j < 4; j++) {
					*(ptr++) = fgetc(input);
				}

				printf("%08X \n", tempi);
			}
			else {
				printf("%10s %10s \n", "WORD", varName[i]);
			}
		}
		printf("} IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER   \n\n");

		printf("Press 'q' to Quit! \n");
	} while (getch() != 'q');
}

void show_NTHeaders(char* str, FILE* input)
{
	 
}

void show_SectionHeaders(char* str, FILE* input)
{
	 printf("show Sectionheaders \n");
}

void show(char* str, FILE* input)
{
	 char* details[] = { " allhex", " file/memory map", " dosheader", " ntheaders", " sectionheaders" };
	 void (*subDetail[])(char* str, FILE* input) = { show_Allhex, show_fileMemMap, show_DosHeader, show_NTHeaders, show_SectionHeaders };

	 char flag = 1;
	 int i;

	 for(i=0; i<sizeof(details) / sizeof(char*); i++) {
		 if(!strcmp(str, details[i])) {
			  subDetail[i](str + strlen(details[i]), input);
			  flag = 0;

			  system("cls");
		 }
	 }

	 if(flag) {   // show ?
		 printf("Illegal Instruction!!! \n");
	 }
}

void save(char* str, FILE* input)
{
	printf("saved it! \n");
}

int main(int argc, char * argv[])
{
	FILE * input;
	FILE * output;

	void (*inst[])(char* str, FILE* input) = { show, save };

	char buffer[50] = "Hello";
	char* instName[] = { "show", "save" };

	int len, i;

	
	if(argc<2) {
		intro();
		return -1;
	}

	input = fopen(argv[argc-1], "rb");

	if(input == NULL) {
		printf("usage > PEview [option] filename \n");

		return -1;
	}

	do {
		printf("input: ");
		fgets(buffer, sizeof(buffer), stdin);   // 실행할 명령어 입력

		len = strlen(buffer);
		buffer[len - 1] = '\0';

		for(i=0; i<strlen(buffer); i++) {   // 대문자 -> 소문자
			if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
				buffer[i] += 'a'-'A';
			}
	    }

		for(i=0; i<sizeof(instName)/sizeof(char *); i++) {   // 명령어 찾기 & 실행
			 if(!strncmp(buffer, instName[i], strlen(instName[i]))) {
				inst[i](buffer+strlen(instName[i]), input);
		     }
	    }
	}while(strncmp(buffer, "quit", sizeof(buffer)) && strncmp(buffer, "\\q", sizeof(buffer)));

	printf("\n~bye! \n");

	return 0;
}
