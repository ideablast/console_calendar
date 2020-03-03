#include"ALL.h"


/*�Լ� �̸�: get_cur_date(int* year, int* month)
 *�Լ� ���: ��,���� �Է��ϸ� ���� ��,���� ���� ������Ʈ ���ش�.
 *���ϰ�: ����
 *�޸�
 */
void get_cur_date(int* year, int* month)
{

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	*year = tm.tm_year + 1900;
	*month = tm.tm_mon + 1;
}


/*�Լ� �̸�: menu_select(int sel, int *year, int *month)
*�Լ� ���: 
*1.�������:��¥ ������ ���Ϻ��� ������ ���Ͽ� �����Ѵ�.
*2.������ȸ:������ �ִ� ��¥�� �����ش�. �׸��� ��¥�� �����ϸ� ���Ͽ� ����� ������ �����ش�.//������ �ִ� ��¥ ǥ�� ����
*3.��������:24�ð��� ������ �����Ѵ�
*4.��������:���Ͽ��� ������ �ҷ��ͼ� ������ �����ϰ� �����Ѵ�.
*5.����ڰ� ��¥�� �����ϰ�
*6.���α׷� ����
*���ϰ�: �޴� ���� sel ��
*�޸�
*/

int menu_select(int sel, int *year, int *month)
{
	int day=0;
	
	
	switch (sel)
	{
	case 1:
		calendar(*year, *month);
		puts("������ ��� �� ��¥�� ����ּ���.");
		scanf("%d", &day);
		clear_buf();

		if (file_read_and_check(*year, *month, day)==TRUE)
		{
			puts("�ش� ��¥�� ������ �����մϴ�.");
			puts("���� ��ȸ Ȥ�� ���� ���� �޴��� �������ּ���.");
			break;
		}
		schedule_register(*year,*month, day);//������ �ִ� ��¥�̸� ���� ���� �޴��� �����ؼ� �ٽ� �������� �ϴ� ���
		break;
	case 2:
		calendar(*year, *month);
		puts("������ ��ȸ �� ��¥�� ����ּ���.");
		scanf("%d", &day);
		clear_buf();
		if (file_read_and_check(*year, *month, day) ==FALSE)
		{
			puts("�ش� ��¥�� ������ �������� �ʽ��ϴ�.");
			puts("�켱 ������ ������ּ���.");
			break;
		}
		schedule_check(*year, *month, day);
		break;
	case 3:
		calendar(*year, *month);
		puts("������ ���� �� ��¥�� ����ּ���.");
		scanf("%d", &day);
		clear_buf();
		if (file_read_and_check(*year, *month, day) == FALSE)
		{
			puts("�ش� ��¥�� ������ �������� �ʽ��ϴ�.");
			puts("�켱 ������ ������ּ���.");
			break;
		}

		schedule_revise(*year, *month, day);
		break;
	case 4:
		calendar(*year, *month);
		puts("������ ���� �� ��¥�� ����ּ���.");
		scanf("%d", &day);
		clear_buf();
		schedule_delete(*year, *month, day);
		break;
	case 5:
		calendar(*year, *month);
		puts("���ο� ��/���� �Է����ּ���");
		scanf("%d %d", year, month);
		calendar(*year, *month);
		break;

	case 6:
		puts("���α׷��� �����մϴ�.");
		return -1;
		break;
	}

	return sel;

}
/*�Լ� �̸�: copy_file( char *dst_name,  char *dst_mode, char *src_name, int year, int month, int day)
*�Լ� ���: dst������ �̸��� ���� ��带 �����ָ� src������ �����Ѵ�.
*���ϰ�: ����
*�޸�
*/

void copy_file( char *dst_name,  char *dst_mode, char *src_name, int year, int month, int day)
{
	//dst_mode�� ���� ������ ������ ����� ���� ������ �̾ ������ ������ �߰��ߴ�.
	FILE *fp, *fp_copy;
	int read_year, read_month, read_day;
	int read_time, read_mem_size;
	char *schedule;
	int i;
	
	fp = fopen(src_name, "r");// ���� ���Ͽ� ������ �غ�
	fp_copy = fopen(dst_name, dst_mode);

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d", &read_year, &read_month, &read_day);
		if (feof(fp))
			break;
		fprintf(fp_copy, "%d %d %d\n", read_year, read_month, read_day);//���� ������ �״�� ����.
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
		printf("%02d�� ����: ", i);
		schedule = get_string_return_ptr();
		mem_size = strlen(schedule);//���� �Է��� ���͸� ���� ���¿����� strlen ���� 0�� ����
		puts("");
		if (mem_size == 0)
		{
			free(schedule);
			fprintf(fp, "%d %d %s\n", i, 6, empty);//�о�Ë��� �� ������ �״�� �޸� �Ҵ� ���ָ� ��
		}
		else
		{
			fprintf(fp, "%d %d %s\n", i, mem_size + 1, schedule);//�о�Ë��� �� ������ �״�� �޸� �Ҵ� ���ָ� ��
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
	
	seperate_file(year, month, day);//������ ������ �������� ����, ����, �������� ������ 3���� �и���
									//temp_1.txt, temp_2.txt, ���� �ִ� ����

	schedule_register_module("temp_1.txt", "a", year, month, day);

	copy_file(select_file_name(calculate_file_date(year, month, day)), "w", "temp_1.txt", year, month, day);
	copy_file(select_file_name(calculate_file_date(year, month, day)), "a", "temp_2.txt", year, month, day);
	
	puts("���� ���� �Ϸ�!");
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
		//������ ���Ŀ� ���缭 �о���� �Ѵٴ� ����� ����� ����
		//�׷��� ������ ��ġ �ʴ� ����� Ȯ�� �� ���� �𸥴�.
		fscanf(fp, "%d%d%d", &read_year, &read_month, &read_day);//������ ���� ��ġ�����ڴ� �̵��Ѵ�
		if (read_year == year&&read_month == month&&read_day == day)//Ÿ�� ��¥�� �о���̸� ��������� 
																	//���� ��ġ �����ڰ� �������ٴ� �̾߱�
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
		else//Ÿ�� ��¥�� �ƴϸ� ����
		{
			fprintf(fp_copy_1, "%d %d %d\n", read_year, read_month, read_day);//���� ������ �״�� ����.
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
		//Ÿ�� ��¥�� ���κб��� ������
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d%d%d", &read_year, &read_month, &read_day);//������ ���� ��ġ�����ڴ� �̵��Ѵ�
		if (feof(fp))
			break;
		fprintf(fp_copy_2, "%d %d %d\n", read_year, read_month, read_day);//���� ������ �״�� ����.
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
		//Ÿ�� ��¥�� ������ ������ �κк��� ������ ������
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
		fscanf(fp, "%d %d %d", &read_year, &read_month, &read_day);//�а� ���� �����ڸ� �̵� ���� �����
		if (read_year == year&&read_month == month&&read_day == day)
		{
			for (i = 0; i < 24; i++)
			{
				fscanf(fp, "%d%d", &time, &mem_size);
				schedule = (char*)malloc(mem_size * sizeof(char));
				memset(schedule, 0, mem_size * sizeof(char));
				fscanf(fp, "%s", schedule);
				printf("%02d��: %s\n", time, schedule);
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
	puts("���� ��ȸ �Ϸ�!");
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
	
	//0:�Ͽ���, 1:������, 2:ȭ����, 3:������, 4:�����, 5:�ݿ���, 6:�����
	fp = file_write(calculate_file_date(year, month, day));//���Ϻ� ���� ������ ����
	fprintf(fp, "%d %d %d\n", year, month, day);
	for (i = 0; i < 24; i++)
	{
		printf("%02d�� ����: ",i);
		schedule = get_string_return_ptr();
		mem_size = strlen(schedule);//���� �Է��� ���͸� ���� ���¿����� strlen ���� 0�� ����
		puts("");
		if (mem_size == 0)
		{
			free(schedule);
			fprintf(fp, "%d %d %s\n", i, 6, empty);//�о�Ë��� �� ������ �״�� �޸� �Ҵ� ���ָ� ��
		}
		else 
		{
			fprintf(fp, "%d %d %s\n", i, mem_size + 1, schedule);//�о�Ë��� �� ������ �״�� �޸� �Ҵ� ���ָ� ��
			free(schedule);
		}
		
	}
	puts("���� ��� �Ϸ�!");
	system("pause");
	system("cls");
	fclose(fp);
}

int calculate_file_date(int year, int month, int day)//� ������ ���Ͽ� ����Ǿ��ִ��� ã�� ���� ���
{
	int sum;
	sum = calculate_dayoftheweek(year, month);

	return (sum + day) % 7;

}

int file_read_and_check(int year, int month, int day)//���� �̸��� ã�� Ư�� ��¥�� ���Ͽ��� ��ȸ�Ǹ� ������ �������� �����Ѵ�
{
	FILE *fp;
	char *file_name;
	char *string;
	int read_year, read_month, read_day;
	int read_time, read_mem_size;
	int i;

	file_name = select_file_name(calculate_file_date(year, month, day));//���� �̸��� ã���ش�.

	fp = fopen(file_name, "r");

	if (fp == NULL)
		return FALSE;//�ش� ��¥�� ������ ����, �ش� ���Ͽ� ���� ��ü�� ��������� �����Ƿ�
	else
	{
		while (!feof(fp))//���Ͽ� ���ͼ� ������ �������� ��� �����鼭 ���� üũ�Ѵ�
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
		return FALSE;// ������ ��ã����
	}


}
int Is_there_any_file(int idx)
{
	FILE *fp = fopen(select_file_name(idx), "r");

	if (fp == NULL)
		return FALSE;//����
	else
		return TRUE;//�ִ�
}

char* select_file_name(int idx)//���� �̸��� ã���ش�.
{
	char *name[7] = { "schedule_sun.txt" , "schedule_mon.txt", "schedule_tue.txt", "schedule_wed.txt", "schedule_thu.txt",  "schedule_fri.txt", "schedule_sat.txt" };

	return name[idx];
}

void read_oneday_schedule(FILE *fp)//��ġ ������ �ű� �뵵
{
	int i;
	int read_year, read_month, read_day;
	int time, mem_size;
	char *schedule;

	fscanf(fp, "%d %d %d", &read_year, &read_month, &read_day);//�а� ���� �����ڸ� �̵� ���� �����
	for (i = 0; i < 24; i++)
	{
		fscanf(fp, "%d%d", &time, &mem_size);


		schedule = (char*)calloc(mem_size + 1, sizeof(char));
		fgets(schedule, mem_size + 1, fp);//+1�� ���ϸ� �� ���Ͱ��ϳ� �� ����°��ΰ�?
		printf("%02d��: %s\n", time, schedule);
		free(schedule);
	}

}