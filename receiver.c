#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shared_memory" // you can find it under `/dev/shm/`
#define SHM_SIZE (1L * 1024 * 1024 * 1024)

int main() {
    // Open the shared memory object
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the process's address space
    void *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Use the shared memory (example: read/write)
    printf("Message from shared memory: %s\n", (char*)shm_ptr);

    // Clean up
    close(shm_fd);

    return 0;
}