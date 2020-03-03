#include"ALL.h"
void screen_out_select_cal()
{
	system("cls");
	puts("새로운 달력이 출력됩니다.");
	system("pause");
}

void screen_out_select_menu(int year,int month)
{
	system("cls");
	puts("");
	printf("%d년 %02d월을 선택하셨습니다.\n메뉴를 선택해주세요\n\n", year, month);
	printf("1.  %d년 %02d월에 일정 등록.\n", year, month);
	printf("2.  %d년 %02d월의 일정 조회.\n", year, month);
	printf("3.  %d년 %02d월의 일정 수정.\n", year, month);
	printf("4.  %d년 %02d월의 일정 삭제.\n", year, month);
	printf("5.  새로운 연도와 월을 입력.\n");
	printf("6.  프로그램 종료\n");
}

int menu_exit()
{
	int sel = 0;
	puts("이어서 프로그램을 사용하시겠습니까?");
	puts("1. yes 2. no");
	scanf("%d", &sel);
	if (sel == 2)
		return -1;

}


/*함수 이름: print_calendar(int first_date, int last_date)
*함수 기능: 프린트 하고 싶은 해당 달의 첫날과 끝날을 입력하면 달력을 그려준다
*메모
*/
void print_calendar(int first_date, int last_date)
{
	int i;
	int count = 0;
	printf("SUN  MON  TUE  WED  THU  FRI  SAT\n");
	puts("");

	for (i = 0; i <= first_date; i++)
	{
		printf("     ");
		count++;
	}

	for (i = 1; i <= last_date; i++)
	{
		if (count >= 7)
		{
			printf("\n");
			count = 0;
		}
		printf("%3d  ", i);
		count++;
	}
	printf("\n\n");
}





#ifdef GO
Console_Calendar
#
#
               02월              
MON^^TUE  WED  THU  FRI  SAT  SUN
001  *02
008
015

<------------|ENTER|------------>
화살표 왼쪽(이전달)/오른쪽(다음달)/엔터(선택)

─ │ ┌ ┐ ┘ └ ├ ┬ ┤ ┴ ┼

^^^^^^^^^1^^^^^^^^^2^^^^^^^^^3^^^^^^^^^4^^^^^^^^^5
┌────┬────┬────┬────┬────┬────┬────┐
│^MON│^TUE│^WED│^THU│^FRI│^SAT│^SUN│

├────┼────┼────┼────┼────┼────┼────┤  이렇게 두줄이 한세트로 출력된다면 가능 할듯
│^^1^│^^2^│*^3^│^^4^│^^5^│^^6^│^^7^│

├────┼────┼────┼────┼────┼────┼────┤
│^^8^│^^9^│*10^│^11^│^12^│^13^│^14^│


└────┴────┴────┴────┴────┴────┴────┘

#endif

#ifdef GO
#include <stdio.h>
int main() {
	FILE *fp = fopen("some_data.txt", "r");
	char data[10];
	char c;

	if (fp == NULL) {
		printf("file open error ! \n");
		return 0;
	}
	//some_data.txt에 있는 내용은 아래와 같다
	//There is some data in this FILE!!!!
	fgets(data, 5, fp);//fp로 부터 5바이트를 data에 입력 받는다 이떄 5바이트 안에는 문자열을 입력 받으므로 널문자가 포함된다
	//추가적으로 fgets은 \n을 기준으로 입력을 받는다
	printf("입력 받은 데이터 : %s \n", data);
	//따라서 Ther'\0'이렇게 해서 5바이트가 들어가있다
	//출력되는 문자는 Ther 이다.
	c = fgetc(fp);//현재 가르키는 위치는 e
	printf("그 다음에 입력 받은 문자 : %c \n", c);
	//e가 출력된다 출력하고 나서 파일 위치 지시자는 
	fseek(fp, -1, SEEK_CUR);

	c = fgetc(fp);
	printf("그렇다면 무슨 문자가? : %c \n", c);

	fclose(fp);
}

#endif

