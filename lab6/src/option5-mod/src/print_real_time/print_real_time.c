#include "print_real_time.h"

void print_real_time()
{
    time_t now = time(0);
    struct tm *ltm = localtime(&now);
    printf(
        "%02d:%02d:%02d\n",
        1 + ltm->tm_hour,                               // часы
        1 + ltm->tm_min,                                // минуты
        1 + ltm->tm_sec                                 // секунды
    );
}