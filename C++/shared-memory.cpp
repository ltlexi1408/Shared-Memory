#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring> 
#include <semaphore.h>
#include <iostream>
#include <limits>

#define SHM_NAME "/shared-memory"
#define SIZE  256

#define SEM_NAME "/semaphore"

int main(){

    int memory = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if(memory == -1){
        // Error message
        return -1;
    }

    if(ftruncate(memory, SIZE) == -1){
        // Error message
        return -1;
    }

    void* address = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memory, 0);
    if(address == MAP_FAILED){
        // Error message
        return -1;
    }

    sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);

    char text[256] = {0};

    while(text != "exit"){
        std::cout << "Message: ";
        std::cin.getline(text, SIZE);
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        sem_wait(sem);

        memcpy(address, text, SIZE);

        sem_post(sem);
    }

    std::cout << "wait for python" << std::endl;
    std::cin.get();

    if(munmap(address, SIZE) == -1){
        // Error message
        return -1;
    }

    close(memory);
    shm_unlink(SHM_NAME);

    return 0;
}