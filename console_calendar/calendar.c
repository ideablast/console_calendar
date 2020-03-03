#include"ALL.h"

/*�Լ� �̸�: cal_dayoftheweek(int year, int month)
*�Լ� ���: �Է��� ��,���� ���� ���� ��¥�� ���� �����ش�.
*���ϰ�: ��¥��
*�޸�
*/

int calculate_dayoftheweek(int year, int month)
{
	int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day_sum = 0;
	int i;

	day_sum = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;//�۳���� ��¥ ��

	for (i = 0; i < month - 1; i++)
	{

		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) //����
			day[1] = 29;
		else
			day[1] = 28;

		day_sum += day[i];//������ ���� ��¥��
	}

	return day_sum;
}


/*�Լ� �̸�: calendar(int year, int month)
*�Լ� ���: ��,���� �Է��ϸ� �޷��� ������ش�.
*���ϰ�: ����
*�޸�
*/

void calendar(int year, int month)
{
	int day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int day_sum = 0;
	int first_date = 0;
	int last_date = 0;
	int i;

	day_sum = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;//�۳���� ��¥ ��

	for (i = 0; i < month - 1; i++)
	{

		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) //����
			day[1] = 29;
		else
			day[1] = 28;

		day_sum += day[i];//������ ���� ��¥��
	}

	// ó���� ä�� ��ĭ �� ���
	first_date = day_sum % 7;
	last_date = day[month - 1];

	//1�� 1�� 1���� ������
	//���� ������ 1:�Ͽ���
	printf("           %d�� %02d��\n", year, month);
	print_calendar(first_date, last_date);

}



/*�Լ� �̸�: calendar_select(int* year, int* month)
*�Լ� ���: ȭ�鿡 ��µǴ� �޷��� ���� �ٲٴ� ��� �� �ش� ��/���� �����ϴ� ��� �����ϸ� ����� �����ؼ� ���ϰ����� �Ѱ��ش�
*���ϰ�: ������ �޴�
*�޸�
*/

int calendar_select(int* year, int* month)
{
	int point;
	int sel = 0;

	while (1)
	{
		puts("��:������\n��:������\n��:������\n��:������\nENTER:�޴�����\n");
		calendar(*year, *month);
		point = get_keyboard();//Ű���忡�� ���� �Է� �޴´�

		switch (point)
		{
		case 75://���� ������
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
		case 77://������ ������
			screen_out_select_cal();
			if (*month == 12)
				(*year)++;
			(*month)++;
			*month = month_check(month);
			break;
		case 72://���� ������
			(*year)++;
			screen_out_select_cal();
			break;
		case 80://�Ʒ��� ������
			(*year)--;
			screen_out_select_cal();
			break;
		case 13:
			screen_out_select_menu(*year, *month);//1.������� 2.������ȸ 3.�������� 4.�������� 5.���ο� ��/�� �Է� 6. ���α׷� ����
			scanf("%d", &sel);
			break;

		}

		if (point == 13)
			break;
	}

	return sel;
}

/*�Լ� �̸�: month_check(int *month)
*�Լ� ���: �������� ��� �� �Է� ���� �ٷ���� �ش�.
*���ϰ�: ������ ��
*�޸�
*/
int month_check(int *month)
{
	if (*month > 12 || *month <= 0)
	{
		*month = *month % 13 + 1;
	}

	return *month;
}