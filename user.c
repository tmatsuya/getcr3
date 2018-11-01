#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
//#define DEBUG

#define	MEM_DEVICE	"/dev/getcr3"
#define	BUF_SIZE	(256)

int main(int argc,char **argv)
{
	char buf[8];
	long long cr3;
	int fd, rc, i;
	if ((fd=open(MEM_DEVICE,O_RDONLY)) <0) {
		fprintf(stderr,"cannot open %s\n",MEM_DEVICE);
		return 1;
	}

	while (1) {
		rc = read(fd, &cr3, 8);
		printf("return code(length)=%d  CR3=%llX\n", rc, cr3);
		sleep( 1 );
	}

	close(fd);
}
