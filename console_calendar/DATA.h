#pragma once
#ifndef __DATA_H__
#define __DATA_H__
//하루치의 구조체를 만들고 일정이 등록된 구조체에만 메모리를 할당한다
#define TRUE 1
#define FALSE 0
typedef struct {

	int year;
	int month;
	int day;
	char *hour_schedule[24];//일정이 기록된 시간만 메모리 할당하고 쓰게 만들어보자

}oneday_schedule;

typedef struct {
	int year;
	char month;
	char day;

}DATE_RETURN;

#endif
