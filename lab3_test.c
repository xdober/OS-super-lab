#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
	int testdev;
	int i;
	char buf[] = {"abc"}, buf2[10], buf3[10];
	testdev = open("/dev/mydev",O_RDWR);
	if ( testdev == -1 ) {
		printf("Cann't open file \n");
		return 0;
	}
	write(testdev, buf, 3);
	write(testdev, "defg", 4);
	close(testdev);
	testdev = open("/dev/mydev",O_RDWR);
	read(testdev,buf2,4);
    read(testdev,buf3,3);
	close(testdev);
		printf("%s\n%s\n",buf2, buf3);
	return 0;
}
