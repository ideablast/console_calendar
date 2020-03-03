#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__
/*------------������ ���--------------*/
void clear_buf();
int get_keyboard();
void get_string(char**str_ptr);
char* get_string_return_ptr();

/*-----------------------------*/
/*-------------ȭ�� ���---------------*/
void screen_out_select_cal();
void screen_out_select_menu(int year, int month);
int menu_exit();

/*-----------------------------*/
/*--------------Ķ���� ���---------------*/
int calculate_dayoftheweek(int year, int month);
void print_calendar(int first_date, int last_date);
void calendar(int year, int month);
void print_calendar(int first_date, int last_date);
void get_cur_date(int* year, int* month);
int calendar_select(int* year, int* month);
int menu_select(int sel, int *year, int *month);
void schedule_register(int year, int month, int day);
int month_check(int *month);
void seperate_file(int year, int month, int day);
void schedule_revise(int year, int month, int day);
void schedule_check(int year, int month, int day);
void schedule_register(int year, int month, int day);
void copy_file(char *dst_name, char *dst_mode, char *src_name, int year, int month, int day);
void schedule_register_module(char *file_name, char *file_mode, int year, int month, int day);
void schedule_delete(int year, int month, int day);
int calculate_file_date(int year, int month, int day);
int file_read_and_check(int year, int month, int day);
char* select_file_name(int idx);
int Is_there_any_file(int idx);

//FILE* file_write(char dayoftheweek);

/*-----------------------------*/
/*--------------���� ����� ����---------------*/



/*-----------------------------*/


#endif
