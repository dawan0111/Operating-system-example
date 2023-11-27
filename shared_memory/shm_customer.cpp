#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>

#include <sys/mman.h>

int main()
{
    const int SIZE = 4096;
    const std::string name = "OS";

    int fd;
    char *ptr;

    fd = shm_open(name.c_str(), O_RDONLY,0666);

    if (fd == -1) {
        std::cout << "shared memory failed" << std::endl;
		exit(-1);
	}

    ptr = (char *) mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);

    std::cout << std::string(ptr) << std::endl;

    shm_unlink(name.c_str());

    return 0;
}