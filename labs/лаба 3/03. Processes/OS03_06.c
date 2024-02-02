#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

// system вызывает bash - интерпритатор и системная оболочка командной строки
// почему прыгает со знач на знач - потмоу что сначала запускается bash и делает +1 pid, потом уже сама команда 
int main(){ 
    //child
    system("OS03_05_1");
    //parent
    for (int i = 0; i < 100; i++) {
		printf("OS03_06 - PID: %d-#%d\n", getpid(), i);
		sleep(1);
	}

	return 0;
}