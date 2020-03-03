#include"ALL.h"

//요일을 설정해주면 파일 모드를 결정해줌
FILE* file_write(int dayoftheweek)
{
	FILE *fp;

	if (dayoftheweek == 0)//일요일
	{
		fp = fopen("schedule_sun.txt", "r");

		if (fp != NULL)//읽기 모드로 열어서 이미 존재하면
		{
			fclose(fp);
			fp = fopen("schedule_sun.txt", "a");//덧붙여 쓰는 모드로 연다
		}
		else
		{
			fp = fopen("schedule_sun.txt", "w");
		}
	}

	if (dayoftheweek == 1)//월요일
	{
		fp = fopen("schedule_mon.txt", "r");

		if (fp != NULL)//읽기 모드로 열어서 이미 존재하면
		{
			fclose(fp);
			fp = fopen("schedule_mon.txt", "a");//덧붙여 쓰는 모드로 연다
		}
		else
		{
			fp = fopen("schedule_mon.txt", "w");
		}
	}

	if (dayoftheweek == 2)//화요일
	{
		fp = fopen("schedule_tue.txt", "r");

		if (fp != NULL)//읽기 모드로 열어서 이미 존재하면
		{
			fclose(fp);
			fp = fopen("schedule_tue.txt", "a");//덧붙여 쓰는 모드로 연다
		}
		else
		{
			fp = fopen("schedule_tue.txt", "w");
		}
	}

	if (dayoftheweek == 3)//수요일
	{
		fp = fopen("schedule_wed.txt", "r");

		if (fp != NULL)//읽기 모드로 열어서 이미 존재하면
		{
			fclose(fp);
			fp = fopen("schedule_wed.txt", "a");//덧붙여 쓰는 모드로 연다
		}
		else
		{
			fp = fopen("schedule_wed.txt", "w");
		}
	}

	if (dayoftheweek == 4)//목요일
	{
		fp = fopen("schedule_thu.txt", "r");

		if (fp != NULL)//읽기 모드로 열어서 이미 존재하면
		{
			fclose(fp);
			fp = fopen("schedule_thu.txt", "a");//덧붙여 쓰는 모드로 연다
		}
		else
		{
			fp = fopen("schedule_thu.txt", "w");
		}
	}

	if (dayoftheweek == 5)//금요일
	{
		fp = fopen("schedule_fri.txt", "r");

		if (fp != NULL)//읽기 모드로 열어서 이미 존재하면
		{
			fclose(fp);
			fp = fopen("schedule_fri.txt", "a");//덧붙여 쓰는 모드로 연다
		}
		else
		{
			fp = fopen("schedule_fri.txt", "w");
		}
	}

	if (dayoftheweek == 6)//토요일
	{
		fp = fopen("schedule_sat.txt", "r");

		if (fp != NULL)//읽기 모드로 열어서 이미 존재하면
		{
			fclose(fp);
			fp = fopen("schedule_sat.txt", "a");//덧붙여 쓰는 모드로 연다
		}
		else
		{
			fp = fopen("schedule_sat.txt", "w");
		}
	}

	return fp;
}
void read_oneday_schedule(FILE *fp);
int main()
{
	int sel;
	int year, month;
	get_cur_date(&year, &month);//년, 월을 현재 년,월로 업데이트
	while (1)
	{
		sel = calendar_select(&year, &month);// 사용자가 년 월을 선택  
											 //1.등록,2.수정,3.삭제,4.조회,5.새로운 년월 입력	6.프로그램 종료
		sel = menu_select(sel, &year, &month);
		sel = menu_exit();

		if (sel == -1)
			break;
	}
	
	return 0;

}