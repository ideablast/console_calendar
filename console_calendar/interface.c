#include"ALL.h"
void screen_out_select_cal()
{
	system("cls");
	puts("���ο� �޷��� ��µ˴ϴ�.");
	system("pause");
}

void screen_out_select_menu(int year,int month)
{
	system("cls");
	puts("");
	printf("%d�� %02d���� �����ϼ̽��ϴ�.\n�޴��� �������ּ���\n\n", year, month);
	printf("1.  %d�� %02d���� ���� ���.\n", year, month);
	printf("2.  %d�� %02d���� ���� ��ȸ.\n", year, month);
	printf("3.  %d�� %02d���� ���� ����.\n", year, month);
	printf("4.  %d�� %02d���� ���� ����.\n", year, month);
	printf("5.  ���ο� ������ ���� �Է�.\n");
	printf("6.  ���α׷� ����\n");
}

int menu_exit()
{
	int sel = 0;
	puts("�̾ ���α׷��� ����Ͻðڽ��ϱ�?");
	puts("1. yes 2. no");
	scanf("%d", &sel);
	if (sel == 2)
		return -1;

}


/*�Լ� �̸�: print_calendar(int first_date, int last_date)
*�Լ� ���: ����Ʈ �ϰ� ���� �ش� ���� ù���� ������ �Է��ϸ� �޷��� �׷��ش�
*�޸�
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
               02��              
MON^^TUE  WED  THU  FRI  SAT  SUN
001  *02
008
015

<------------|ENTER|------------>
ȭ��ǥ ����(������)/������(������)/����(����)

�� �� �� �� �� �� �� �� �� �� ��

^^^^^^^^^1^^^^^^^^^2^^^^^^^^^3^^^^^^^^^4^^^^^^^^^5
������������������������������������������������������������������������
��^MON��^TUE��^WED��^THU��^FRI��^SAT��^SUN��

������������������������������������������������������������������������  �̷��� ������ �Ѽ�Ʈ�� ��µȴٸ� ���� �ҵ�
��^^1^��^^2^��*^3^��^^4^��^^5^��^^6^��^^7^��

������������������������������������������������������������������������
��^^8^��^^9^��*10^��^11^��^12^��^13^��^14^��


������������������������������������������������������������������������

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
	//some_data.txt�� �ִ� ������ �Ʒ��� ����
	//There is some data in this FILE!!!!
	fgets(data, 5, fp);//fp�� ���� 5����Ʈ�� data�� �Է� �޴´� �̋� 5����Ʈ �ȿ��� ���ڿ��� �Է� �����Ƿ� �ι��ڰ� ���Եȴ�
	//�߰������� fgets�� \n�� �������� �Է��� �޴´�
	printf("�Է� ���� ������ : %s \n", data);
	//���� Ther'\0'�̷��� �ؼ� 5����Ʈ�� ���ִ�
	//��µǴ� ���ڴ� Ther �̴�.
	c = fgetc(fp);//���� ����Ű�� ��ġ�� e
	printf("�� ������ �Է� ���� ���� : %c \n", c);
	//e�� ��µȴ� ����ϰ� ���� ���� ��ġ �����ڴ� 
	fseek(fp, -1, SEEK_CUR);

	c = fgetc(fp);
	printf("�׷��ٸ� ���� ���ڰ�? : %c \n", c);

	fclose(fp);
}

#endif

