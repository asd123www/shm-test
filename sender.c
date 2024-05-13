#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHM_NAME "/my_shared_memory"
#define SHM_SIZE (1L * 1024 * 1024 * 1024) // 1GB

int main() {
    // Create shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Map the shared memory object into the process's address space
    void *shm_ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Initialize memory (optional)
    memset(shm_ptr, 0, SHM_SIZE);
    strcpy((char*)shm_ptr, "asd123www: shared!");

    printf("Shared memory created and initialized.\n");

    // Clean up
    close(shm_fd);
    // Do not unlink if you want to keep the shared memory for other processes to use
    // shm_unlink(SHM_NAME);

    return 0;
}
