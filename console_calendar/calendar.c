#include"ALL.h"

/*함수 이름: cal_dayoftheweek(int year, int month)
*함수 기능: 입력한 년,월의 전달 까지 날짜의 합을 구해준다.
*리턴값: 날짜합
*메모
*/

int calculate_dayoftheweek(int year, int month)
{
	int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day_sum = 0;
	int i;

	day_sum = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;//작년까지 날짜 합

	for (i = 0; i < month - 1; i++)
	{

		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) //윤년
			day[1] = 29;
		else
			day[1] = 28;

		day_sum += day[i];//지난달 까지 날짜합
	}

	return day_sum;
}


/*함수 이름: calendar(int year, int month)
*함수 기능: 년,월을 입력하면 달력을 출력해준다.
*리턴값: 없음
*메모
*/

void calendar(int year, int month)
{
	int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day_sum = 0;
	int first_date = 0;
	int last_date = 0;
	int i;

	day_sum = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;//작년까지 날짜 합

	for (i = 0; i < month - 1; i++)
	{

		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) //윤년
			day[1] = 29;
		else
			day[1] = 28;

		day_sum += day[i];//지난달 까지 날짜합
	}

	// 처음에 채울 빈칸 수 계산
	first_date = day_sum % 7;
	last_date = day[month - 1];

	//1년 1월 1일은 월요일
	//시작 나머지 1:일요일
	printf("           %d년 %02d월\n", year, month);
	print_calendar(first_date, last_date);

}



/*함수 이름: calendar_select(int* year, int* month)
*함수 기능: 화면에 출력되는 달력의 월을 바꾸는 기능 및 해당 년/월을 선택하는 기능 선택하면 기능을 선택해서 리턴값으로 넘겨준다
*리턴값: 선택한 메뉴
*메모
*/

int calendar_select(int* year, int* month)
{
	int point;
	int sel = 0;

	while (1)
	{
		puts("←:이전달\n→:다음달\n↑:다음해\n↓:이전해\nENTER:메뉴선택\n");
		calendar(*year, *month);
		point = get_keyboard();//키보드에서 값을 입력 받는다

		switch (point)
		{
		case 75://왼쪽 이전달
			screen_out_select_cal();
			if (*month == 1)
			{
				(*year)--;
				*month = 12;
				break;
			}
			(*month)--;
			*month = month_check(month);
			break;
		case 77://오른쪽 다음달
			screen_out_select_cal();
			if (*month == 12)
				(*year)++;
			(*month)++;
			*month = month_check(month);
			break;
		case 72://위쪽 다음해
			(*year)++;
			screen_out_select_cal();
			break;
		case 80://아래쪽 이전해
			(*year)--;
			screen_out_select_cal();
			break;
		case 13:
			screen_out_select_menu(*year, *month);//1.일정등록 2.일정조회 3.일정수정 4.일정삭제 5.새로운 년/월 입력 6. 프로그램 종료
			scanf("%d", &sel);
			break;

		}

		if (point == 13)
			break;
	}

	return sel;
}

/*함수 이름: month_check(int *month)
*함수 기능: 범위에서 벗어난 월 입력 값을 바로잡아 준다.
*리턴값: 보정된 월
*메모
*/
int month_check(int *month)
{
	if (*month > 12 || *month <= 0)
	{
		*month = *month % 13 + 1;
	}

	return *month;
}