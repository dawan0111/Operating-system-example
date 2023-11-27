#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main()
{
    const int SIZE = 4096;
    const std::string name = "OS";

    const std::string message_0 = "Hello";
    const std::string message_1 = "World!";
    const std::string message_2 = "wow";

    int fd;
    char *ptr;

    fd = shm_open(name.c_str(), O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);

    ptr = (char *) mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    sprintf(ptr, "%s", message_0.c_str());
    ptr += strlen(message_0.c_str());

    sprintf(ptr, "%s", message_1.c_str());
    ptr += strlen(message_1.c_str());

    sprintf(ptr, "%s", message_2.c_str());
    ptr += strlen(message_2.c_str());

    return 0;

}