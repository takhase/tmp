
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <errno.h>

#define REG(address) *(volatile uint32_t*)(address)

int main(){
	cv::Mat img;

//	img = cv::imread("OpenCV_logo.png");
//	cv::imshow("title", img);
//	cv::waitKey(0);

	printf("Hello World!\n");

	long address;
	int fd;

//	if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
	if ((fd = open("/dev/uio4", O_RDWR | O_SYNC)) < 0)
	{
		perror("open");
		return -1;
	}
//	printf("open /dev/mem\n");
	printf("open /dev/uio4\n");

//	address = (long)mmap(NULL, 0x1000,
//			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0xa0000000);
	address = (long)mmap(NULL, 0x1000,
			PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (address == (long)MAP_FAILED) {
		perror("mmap");
		close(fd);
		return -1;
	}
	printf("mmap address %0lx\n", address);

	while(1){
		REG(address + 0) = 0xff;
		usleep(1000 * 1000);
		REG(address + 0) = 0x00;
		usleep(1000 * 1000);
	}

	munmap((void*)address, 0x1000);
	close(fd);

	return 0;
}
