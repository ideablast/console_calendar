#include"ALL.h"

//������ �������ָ� ���� ��带 ��������
FILE* file_write(int dayoftheweek)
{
	FILE *fp;

	if (dayoftheweek == 0)//�Ͽ���
	{
		fp = fopen("schedule_sun.txt", "r");

		if (fp != NULL)//�б� ���� ��� �̹� �����ϸ�
		{
			fclose(fp);
			fp = fopen("schedule_sun.txt", "a");//���ٿ� ���� ���� ����
		}
		else
		{
			fp = fopen("schedule_sun.txt", "w");
		}
	}

	if (dayoftheweek == 1)//������
	{
		fp = fopen("schedule_mon.txt", "r");

		if (fp != NULL)//�б� ���� ��� �̹� �����ϸ�
		{
			fclose(fp);
			fp = fopen("schedule_mon.txt", "a");//���ٿ� ���� ���� ����
		}
		else
		{
			fp = fopen("schedule_mon.txt", "w");
		}
	}

	if (dayoftheweek == 2)//ȭ����
	{
		fp = fopen("schedule_tue.txt", "r");

		if (fp != NULL)//�б� ���� ��� �̹� �����ϸ�
		{
			fclose(fp);
			fp = fopen("schedule_tue.txt", "a");//���ٿ� ���� ���� ����
		}
		else
		{
			fp = fopen("schedule_tue.txt", "w");
		}
	}

	if (dayoftheweek == 3)//������
	{
		fp = fopen("schedule_wed.txt", "r");

		if (fp != NULL)//�б� ���� ��� �̹� �����ϸ�
		{
			fclose(fp);
			fp = fopen("schedule_wed.txt", "a");//���ٿ� ���� ���� ����
		}
		else
		{
			fp = fopen("schedule_wed.txt", "w");
		}
	}

	if (dayoftheweek == 4)//�����
	{
		fp = fopen("schedule_thu.txt", "r");

		if (fp != NULL)//�б� ���� ��� �̹� �����ϸ�
		{
			fclose(fp);
			fp = fopen("schedule_thu.txt", "a");//���ٿ� ���� ���� ����
		}
		else
		{
			fp = fopen("schedule_thu.txt", "w");
		}
	}

	if (dayoftheweek == 5)//�ݿ���
	{
		fp = fopen("schedule_fri.txt", "r");

		if (fp != NULL)//�б� ���� ��� �̹� �����ϸ�
		{
			fclose(fp);
			fp = fopen("schedule_fri.txt", "a");//���ٿ� ���� ���� ����
		}
		else
		{
			fp = fopen("schedule_fri.txt", "w");
		}
	}

	if (dayoftheweek == 6)//�����
	{
		fp = fopen("schedule_sat.txt", "r");

		if (fp != NULL)//�б� ���� ��� �̹� �����ϸ�
		{
			fclose(fp);
			fp = fopen("schedule_sat.txt", "a");//���ٿ� ���� ���� ����
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
	get_cur_date(&year, &month);//��, ���� ���� ��,���� ������Ʈ
	while (1)
	{
		sel = calendar_select(&year, &month);// ����ڰ� �� ���� ����  
											 //1.���,2.����,3.����,4.��ȸ,5.���ο� ��� �Է�	6.���α׷� ����
		sel = menu_select(sel, &year, &month);
		sel = menu_exit();

		if (sel == -1)
			break;
	}
	
	return 0;

}