#pragma once
#ifndef __DATA_H__
#define __DATA_H__
//�Ϸ�ġ�� ����ü�� ����� ������ ��ϵ� ����ü���� �޸𸮸� �Ҵ��Ѵ�
#define TRUE 1
#define FALSE 0
typedef struct {

	int year;
	int month;
	int day;
	char *hour_schedule[24];//������ ��ϵ� �ð��� �޸� �Ҵ��ϰ� ���� ������

}oneday_schedule;

typedef struct {
	int year;
	char month;
	char day;

}DATE_RETURN;

#endif
