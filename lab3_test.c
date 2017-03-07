#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int testdev;
	int i;
	char buf[10] = {"abcdefghij"}, buf2[10];
	testdev = open("/dev/mydev",O_RDWR);
	if ( testdev == -1 ) {
		printf("Cann't open file \n");
		return 0;
	}
	write(testdev, buf, 3);
	write(testdev, buf, 3);
	close(testdev);
	testdev = open("/dev/mydev",O_RDWR);
	read(testdev,buf2,10);
	for (i = 0; i < 10;i++)
		printf("%c\n",buf2[i]);
	close(testdev);
	return 0;
}
