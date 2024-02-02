#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int main() {
	int count = 0;
	struct timespec start, end, proc;
	clock_gettime(CLOCK_REALTIME, &start);
	for(;;) {
		count++;
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);
		if(proc.tv_sec == 2) break;
	}
	clock_gettime(CLOCK_REALTIME, &end);	
	printf("2 c: %d\n", count);
	printf("time: %ldns\n", (end.tv_sec *1000000000 + end.tv_nsec) - (start.tv_sec * 1000000000 + start.tv_nsec));
	
	exit(0);
}
























// версия посикса от 1993 года #define _POSIX_C_SOURCE 199309L
// clock_gettime(CLOCK_REALTIME, &start);: Запись текущего времени в структуру start с использованием системных часов реального времени.
// clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);: Запись текущего времени CPU процесса в структуру proc.
// if(proc.tv_sec == 2) break;: Если прошло 2 секунды CPU времени, выход из цикла.
// (end.tv_sec *1000000000 + end.tv_nsec)
// + end.tv_nsec: Здесь end.tv_nsec представляет количество наносекунд, которые не уместились в секунды (то есть остаток от деления на 1 секунду). Прибавив это значение,
// мы учитываем остаток и получаем полное время в наносекундах.





// Принимает указатель на временную метку (time_t) и конвертирует его в структуру tm, представляющую местное время (UTC/GMT). Функция gmtime используется для преобразования времени из формата time_t в удобочитаемую структуру времени (struct tm).
// Пример:
// c
// Copy code
// time_t t = time(NULL);
// struct tm *tmptr = gmtime(&t);
// clock_gettime(CLOCK_REALTIME, &start):

// Описание: Получает текущее время относительно реального времени (wall-clock time) в структуру timespec. Эта функция полезна для измерения времени прошедшего между двумя событиями в программе. В данном случае, она записывает текущее время в переменную start.
// Пример:
// c
// Copy code
// struct timespec start;
// clock_gettime(CLOCK_REALTIME, &start);
// clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc):

// Описание: Получает текущее время CPU для процесса в структуру timespec. Это время отражает фактическое время, в течение которого CPU был выделен процессу. Эта функция полезна для измерения времени, затраченного процессором на выполнение определенных задач в программе.
// Пример:
// c
// Copy code
// struct timespec proc;
// clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &proc);