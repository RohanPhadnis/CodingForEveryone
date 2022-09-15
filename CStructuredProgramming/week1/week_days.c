#include <stdio.h>

enum day {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY};

void print_day(enum day day) {
    switch (day) {
        case SUNDAY: printf("sunday"); break;
        case MONDAY: printf("monday"); break;
        case TUESDAY: printf("tuesday"); break;
        case WEDNESDAY: printf("wednesday"); break;
        case THURSDAY: printf("thursday"); break;
        case FRIDAY: printf("friday"); break;
        case SATURDAY: printf("saturday"); break;
        default: printf("%d is an error\n", day);
    }
}

enum day tomorrow(enum day today) {
    return (today + 1) % 7;
}

int main() {
    enum day today = SATURDAY;
    printf("Today is ");
    print_day(today);
    printf("\n");
    printf("Tomorrow is ");
    print_day(tomorrow(today));
    printf("\n");
    return 0;
}
