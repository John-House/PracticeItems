#include <stdio.h>
#define PTNONE printf("%4s", "")

int checkInput(int y, int m, int d);

/* verify user input */
int checkInput(int y, int m, int d) {
    if (m<0 || m>12)
        return 0;
    if (d<0 || d>31)
        return 0;
    if (y<1582)
        return 0;
    if (y==1582 && m<10)
        return 0;
    if (y>=1582 && m==10 && d<15)
        return 0;
    if ((y%4!=0 && y%400!=0) && m==2 && (d<0 || d>28))
        return 0;
    if ((y%4==0 || y%400==0) && m==2 && (d<0 || d>29))
        return 0;
    return 1;
}

int main(void) {
    /* declare variables for user input and verified result */
    int year, month, day, days, flag;
    /* declare modified variables for calculation */
    int mYear, mMonth, mCentury;
    /* set default in February days for non-leap year */
    int Feb = 28;
    do {
        printf("Entry correct date, show you the calendar.\n年份:");
        scanf("%d", &year);
        printf("\n月份:");
        scanf("%d", &month);
        printf("\n日期:");
        scanf("%d", &day);
        flag = checkInput(year, month, day);
    } while (!flag);
    /* calculate what day 1st each month is */
    if (month == 1 || month == 2) {
        mYear = (year - 1) % 100;
        mCentury = (year - 1) / 100;
        mMonth = month + 12;
    } else {
        mYear = year % 100;
        mCentury = year / 100;
        mMonth = month;
    }
    int weekStart = (mYear + mYear/4 + mCentury/4 - 2*mCentury + 26*(mMonth+1)/10) % 7;
    while (1) {
        if (weekStart<0)
            weekStart += 7;
        else
            break;
    }
    /* calculate printed specific days */
    if (year%4 == 0 || year%400 == 0)
        Feb = 29;
    switch (month) {
        case 1:
            days = 31;
            break;
        case 2:
            days = Feb;
            break;
        case 3:
            days = 31;
            break;
        case 4:
            days = 30;
            break;
        case 5:
            days = 31;
            break;
        case 6:
            days = 30;
            break;
        case 7:
            days = 31;
            break;
        case 8:
            days = 31;
            break;
        case 9:
            days = 30;
            break;
        case 10:
            days = 31;
            break;
        case 11:
            days = 30;
            break;
        case 12:
            days = 31;
            break;
    }
    /* build display interface */
    printf("%10sCalendar%10s\nMon Tue Wed Thu Fri Sat Sun\n", "", "");
    for (int i=1; i<weekStart; i++)
        PTNONE;
    for (int i=1,j=weekStart; i<=days; i++,j++) {
        printf("%3d ", i);
        if ((j+7)%7 == 0)
            printf("\n");
    }
}
