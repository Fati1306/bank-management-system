#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 20
#define ADDRESS_MAX 50
#define PHONE_MAX 15
#define TYPE_MAX 10

void display_main_menu(void);

struct  date
{
    int day;
    int month;
    int year;
};

struct account
{
    struct date deposit;
    struct date dob;
    int number;
    int age;
    int citizenship;
    float deposit_amount;
    char    name[NAME_MAX];
    char    address[ADDRESS_MAX];
    char    phone[PHONE_MAX];
    char    type[TYPE_MAX];
} acc, update_acc, transaction_acc, check_acc, remove_acc;

#endif