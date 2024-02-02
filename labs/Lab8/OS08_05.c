#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int main() {
	time_t t = time(&t);
	struct tm * tmptr;
	tmptr = gmtime(&t);
	printf("%d.", tmptr->tm_mday);
	printf("%d.", tmptr->tm_mon + 1);
	printf("%d.", tmptr->tm_year+1900);
	printf(" ");
	printf("%d.", tmptr->tm_hour+3);
	printf("%d.", tmptr->tm_min);
	printf("%d\n", tmptr->tm_sec);

	exit(0);
}























//time_t t = time(&t);: Получение текущего времени в формате time_t.
//tmptr = gmtime(&t);: Преобразование времени t в местное время и сохранение результата в структуре tm.
//time_t представляет собой целочисленное значение, которое обычно представляет количество секунд, прошедших с 00:00:00 1 января 1970 года UTC 
//(эту дату иногда называют "эпохой Unix"). Этот момент времени часто используется в программировании и называется Unix-временем или POSIX-временем.