#include"ALL.h"


/*함수 이름: get_cur_date(int* year, int* month)
 *함수 기능: 년,월을 입력하면 현재 년,월로 값을 업데이트 해준다.
 *리턴값: 없음
 *메모
 */
void get_cur_date(int* year, int* month)
{

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	*year = tm.tm_year + 1900;
	*month = tm.tm_mon + 1;
}


/*함수 이름: menu_select(int sel, int *year, int *month)
*함수 기능: 
*1.일정등록:날짜 선택후 요일별로 일정을 파일에 저장한다.
*2.일정조회:일정이 있는 날짜를 보여준다. 그리고 날짜를 선택하면 파일에 저장된 일정을 보여준다.//일정이 있는 날짜 표시 구현
*3.일정수정:24시간의 일정을 수정한다
*4.일정삭제:파일에서 일정을 불러와서 내용을 삭제하고 저장한다.
*5.사용자가 날짜를 선택하게
*6.프로그램 종료
*리턴값: 메뉴 종료 sel 값
*메모
*/

int menu_select(int sel, int *year, int *month)
{
	int day=0;
	
	
	switch (sel)
	{
	case 1:
		calendar(*year, *month);
		puts("일정을 등록 할 날짜를 골라주세요.");
		scanf("%d", &day);
		clear_buf();

		if (file_read_and_check(*year, *month, day)==TRUE)
		{
			puts("해당 날짜에 일정이 존재합니다.");
			puts("일정 조회 혹은 일정 수정 메뉴를 선택해주세요.");
			break;
		}
		schedule_register(*year,*month, day);//일정이 있는 날짜이면 일정 수정 메뉴를 선택해서 다시 들어오도록 하는 기능
		break;
	case 2:
		calendar(*year, *month);
		puts("일정을 조회 할 날짜를 골라주세요.");
		scanf("%d", &day);
		clear_buf();
		if (file_read_and_check(*year, *month, day) ==FALSE)
		{
			puts("해당 날짜에 일정이 존재하지 않습니다.");
			puts("우선 일정을 등록해주세요.");
			break;
		}
		schedule_check(*year, *month, day);
		break;
	case 3:
		calendar(*year, *month);
		puts("일정을 수정 할 날짜를 골라주세요.");
		scanf("%d", &day);
		clear_buf();
		if (file_read_and_check(*year, *month, day) == FALSE)
		{
			puts("해당 날짜에 일정이 존재하지 않습니다.");
			puts("우선 일정을 등록해주세요.");
			break;
		}

		schedule_revise(*year, *month, day);
		break;
	case 4:
		calendar(*year, *month);
		puts("일정을 삭제 할 날짜를 골라주세요.");
		scanf("%d", &day);
		clear_buf();
		schedule_delete(*year, *month, day);
		break;
	case 5:
		calendar(*year, *month);
		puts("새로운 년/월을 입력해주세요");
		scanf("%d %d", year, month);
		calendar(*year, *month);
		break;

	case 6:
		puts("프로그램을 종료합니다.");
		return -1;
		break;
	}

	return sel;

}
/*함수 이름: copy_file( char *dst_name,  char *dst_mode, char *src_name, int year, int month, int day)
*함수 기능: dst파일의 이름과 개방 모드를 정해주면 src파일을 복사한다.
*리턴값: 없음
*메모
*/

void copy_file( char *dst_name,  char *dst_mode, char *src_name, int year, int month, int day)
{
	//dst_mode는 목적 파일의 내용을 지우고 새로 만들지 이어서 만들지 때문에 추가했다.
	FILE *fp, *fp_copy;
	int read_year, read_month, read_day;
	int read_time, read_mem_size;
	char *schedule;
	int i;
	
	fp = fopen(src_name, "r");// 원래 파일에 복사할 준비
	fp_copy = fopen(dst_name, dst_mode);

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &read_year, &read_month, &read_day);
		if (feof(fp))
			break;
		fprintf(fp_copy, "%d %d %d\n", read_year, read_month, read_day);//읽은 내용을 그대로 쓴다.
		for (i = 0; i < 24; i++)
		{
			fscanf(fp, "%d%d", &read_time, &read_mem_size);
			fprintf(fp_copy, "%d %d ", read_time, read_mem_size);
			schedule = (char*)malloc(read_mem_size * sizeof(char));
			memset(schedule, 0, read_mem_size * sizeof(char));
			fscanf(fp, "%s", schedule);
			fprintf(fp_copy, "%s\n", schedule);
			free(schedule);
		}
	}
	fclose(fp);
	fclose(fp_copy);
}

void schedule_register_module(char *file_name, char *file_mode, int year, int month, int day)
{
	FILE *fp;
	int i;
	char *schedule;
	char empty[] = "Empty";
	int mem_size = 0;

	fp = fopen(file_name, file_mode);

	fprintf(fp, "%d %d %d\n", year, month, day);
	for (i = 0; i < 24; i++)
	{
		printf("%02d시 일정: ", i);
		schedule = get_string_return_ptr();
		mem_size = strlen(schedule);//문자 입력이 엔터만 들어온 상태에서는 strlen 값이 0이 나옴
		puts("");
		if (mem_size == 0)
		{
			free(schedule);
			fprintf(fp, "%d %d %s\n", i, 6, empty);//읽어올떄는 이 사이즈 그대로 메모리 할당 해주면 끝
		}
		else
		{
			fprintf(fp, "%d %d %s\n", i, mem_size + 1, schedule);//읽어올떄는 이 사이즈 그대로 메모리 할당 해주면 끝
			free(schedule);
		}

	}
	fclose(fp);

}

void schedule_delete(int year, int month, int day)
{
	seperate_file(year, month, day);
	copy_file(select_file_name(calculate_file_date(year, month, day)), "w", "temp_1.txt", year, month, day);
	copy_file(select_file_name(calculate_file_date(year, month, day)), "a", "temp_2.txt", year, month, day);
}

void schedule_revise(int year, int month, int day)
{
	
	seperate_file(year, month, day);//선택한 일정을 기준으로 이전, 이후, 원본으로 파일을 3개로 분리함
									//temp_1.txt, temp_2.txt, 원래 있던 파일

	schedule_register_module("temp_1.txt", "a", year, month, day);

	copy_file(select_file_name(calculate_file_date(year, month, day)), "w", "temp_1.txt", year, month, day);
	copy_file(select_file_name(calculate_file_date(year, month, day)), "a", "temp_2.txt", year, month, day);
	
	puts("일정 수정 완료!");
	system("pause");
	system("cls");

}

void seperate_file(int year, int month, int day)
{
	FILE *fp, *fp_copy_1, *fp_copy_2;
	char *file_name = select_file_name(calculate_file_date(year, month, day));
	char *string;
	int read_year, read_month, read_day;
	int read_time, read_mem_size;
	int i;


	fp = fopen(file_name, "r");
	fp_copy_1 = fopen("temp_1.txt", "w");
	fp_copy_2 = fopen("temp_2.txt", "w");

	while (!feof(fp))
	{
		//무조건 형식에 맞춰서 읽어줘야 한다는 사실을 까먹지 말것
		//그렇지 않으면 원치 않는 결과를 확인 할 지도 모른다.
		fscanf(fp, "%d%d%d", &read_year, &read_month, &read_day);//읽으면 파일 위치지시자는 이동한다
		if (read_year == year&&read_month == month&&read_day == day)//타겟 날짜를 읽어들이면 여기까지는 
																	//파일 위치 지시자가 지나갔다는 이야기
		{

			for (i = 0; i < 24; i++)
			{
				fscanf(fp, "%d%d", &read_time, &read_mem_size);
				string = (char*)malloc(read_mem_size * sizeof(char));
				memset(string, 0, read_mem_size * sizeof(char));
				fscanf(fp, "%s", string);
				free(string);

				if (i == 23)
					puts("");
			}
			break;
		}
		else//타겟 날짜가 아니면 복사
		{
			fprintf(fp_copy_1, "%d %d %d\n", read_year, read_month, read_day);//읽은 내용을 그대로 쓴다.
			for (i = 0; i < 24; i++)
			{
				fscanf(fp, "%d%d", &read_time, &read_mem_size);
				fprintf(fp_copy_1, "%d %d ", read_time, read_mem_size);
				string = (char*)malloc(read_mem_size * sizeof(char));
				memset(string, 0, read_mem_size * sizeof(char));
				fscanf(fp, "%s", string);
				fprintf(fp_copy_1, "%s\n", string);
				free(string);
				if (i == 22)
					puts("");
			}
			fprintf(fp_copy_1, "\n");
		}
		//타겟 날짜의 윗부분까지 복사함
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d%d%d", &read_year, &read_month, &read_day);//읽으면 파일 위치지시자는 이동한다
		if (feof(fp))
			break;
		fprintf(fp_copy_2, "%d %d %d\n", read_year, read_month, read_day);//읽은 내용을 그대로 쓴다.
		for (i = 0; i < 24; i++)
		{
			fscanf(fp, "%d%d", &read_time, &read_mem_size);
			fprintf(fp_copy_2, "%d %d ", read_time, read_mem_size);
			string = (char*)malloc(read_mem_size * sizeof(char));
			memset(string, 0, read_mem_size * sizeof(char));
			fscanf(fp, "%s", string);
			fprintf(fp_copy_2, "%s\n", string);
			free(string);
			if (i == 22)
				puts("");
		}
		fprintf(fp_copy_2, "\n");
		//타겟 날짜의 일정이 끝나는 부분부터 끝까지 복사함
	}
	fclose(fp);
	fclose(fp_copy_1);
	fclose(fp_copy_2);
}




void schedule_check(int year, int month, int day)
{
	FILE* fp;
	char *file_name = select_file_name(calculate_file_date(year, month, day));
	char *schedule=NULL;
	int read_year, read_month, read_day;
	int time;
	int mem_size = 0;
	int i;

	fp = fopen(file_name, "r");

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &read_year, &read_month, &read_day);//읽고 파일 지시자를 이동 시켜 줘야함
		if (read_year == year&&read_month == month&&read_day == day)
		{
			for (i = 0; i < 24; i++)
			{
				fscanf(fp, "%d%d", &time, &mem_size);
				schedule = (char*)malloc(mem_size * sizeof(char));
				memset(schedule, 0, mem_size * sizeof(char));
				fscanf(fp, "%s", schedule);
				printf("%02d시: %s\n", time, schedule);
				free(schedule);
			}
			break;
		}
		else
		{
			for (i = 0; i < 24; i++)
			{
				fscanf(fp, "%d%d", &time, &mem_size);
				schedule = (char*)malloc(mem_size, sizeof(char));
				memset(schedule, 0, mem_size * sizeof(char));
				fscanf(fp, "%s", schedule);
				free(schedule);
			}
		}
	}
	puts("일정 조회 완료!");
	system("pause");
	system("cls");
	fclose(fp);
}

void schedule_register(int year, int month, int day)
{
	FILE *fp;
	int i;
	char *schedule;
	char empty[] = "Empty";
	int mem_size = 0;
	
	//0:일요일, 1:월요일, 2:화요일, 3:수요일, 4:목요일, 5:금요일, 6:토요일
	fp = file_write(calculate_file_date(year, month, day));//요일별 쓰기 파일을 연다
	fprintf(fp, "%d %d %d\n", year, month, day);
	for (i = 0; i < 24; i++)
	{
		printf("%02d시 일정: ",i);
		schedule = get_string_return_ptr();
		mem_size = strlen(schedule);//문자 입력이 엔터만 들어온 상태에서는 strlen 값이 0이 나옴
		puts("");
		if (mem_size == 0)
		{
			free(schedule);
			fprintf(fp, "%d %d %s\n", i, 6, empty);//읽어올떄는 이 사이즈 그대로 메모리 할당 해주면 끝
		}
		else 
		{
			fprintf(fp, "%d %d %s\n", i, mem_size + 1, schedule);//읽어올떄는 이 사이즈 그대로 메모리 할당 해주면 끝
			free(schedule);
		}
		
	}
	puts("일정 등록 완료!");
	system("pause");
	system("cls");
	fclose(fp);
}

int calculate_file_date(int year, int month, int day)//어떤 요일의 파일에 저장되어있는지 찾기 위한 계산
{
	int sum;
	sum = calculate_dayoftheweek(year, month);

	return (sum + day) % 7;

}

int file_read_and_check(int year, int month, int day)//파일 이름을 찾고 특정 날짜가 파일에서 조회되면 일정이 있음으로 간주한다
{
	FILE *fp;
	char *file_name;
	char *string;
	int read_year, read_month, read_day;
	int read_time, read_mem_size;
	int i;

	file_name = select_file_name(calculate_file_date(year, month, day));//파일 이름을 찾아준다.

	fp = fopen(file_name, "r");

	if (fp == NULL)
		return FALSE;//해당 날짜에 일정이 없음, 해당 요일에 파일 자체가 만들어진게 없으므로
	else
	{
		while (!feof(fp))//파일에 들어와서 정해진 포맷으로 계속 읽으면서 값을 체크한다
		{
			fscanf(fp, "%d%d%d", &read_year, &read_month, &read_day);
			if (read_year == year&&read_month == month&&read_day == day)
				return TRUE;
			for (i = 0; i < 24; i++)
			{
				fscanf(fp, "%d%d", &read_time, &read_mem_size);
				string = (char*)malloc(read_mem_size * sizeof(char));
				fscanf(fp, "%s", string);
				free(string);
				if (i == 23)
					puts("");
			}
			
		}
		return FALSE;// 끝까지 못찾으면
	}


}
int Is_there_any_file(int idx)
{
	FILE *fp = fopen(select_file_name(idx), "r");

	if (fp == NULL)
		return FALSE;//없다
	else
		return TRUE;//있다
}

char* select_file_name(int idx)//파일 이름을 찾아준다.
{
	char *name[7] = { "schedule_sun.txt" , "schedule_mon.txt", "schedule_tue.txt", "schedule_wed.txt", "schedule_thu.txt",  "schedule_fri.txt", "schedule_sat.txt" };

	return name[idx];
}

void read_oneday_schedule(FILE *fp)//위치 지시자 옮길 용도
{
	int i;
	int read_year, read_month, read_day;
	int time, mem_size;
	char *schedule;

	fscanf(fp, "%d %d %d", &read_year, &read_month, &read_day);//읽고 파일 지시자를 이동 시켜 줘야함
	for (i = 0; i < 24; i++)
	{
		fscanf(fp, "%d%d", &time, &mem_size);


		schedule = (char*)calloc(mem_size + 1, sizeof(char));
		fgets(schedule, mem_size + 1, fp);//+1을 안하면 왜 엔터가하나 더 생기는것인가?
		printf("%02d시: %s\n", time, schedule);
		free(schedule);
	}

}