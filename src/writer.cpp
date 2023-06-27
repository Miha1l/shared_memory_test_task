#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_KEY 1111

void printError(std::string s) {
    std::string error = s + std::to_string(errno);
    std::perror(error.c_str());
}

void deleteSegment(int shmId) {
    if (shmctl(shmId, IPC_RMID, (struct shmid_ds *) 0) == -1) {
        printError("[reader.cpp:shmctl] ");
    }
}

int main() {
    int shmId = shmget(SHM_KEY, 1000, IPC_CREAT | IPC_EXCL | 0666);
    if (shmId == -1) {
        printError("[writer.cpp:shmget] ");
        return 0;
    }
    
    char* shmAddress;
    shmAddress = (char*)shmat(shmId, 0, 0);
    if (shmAddress == (char*)(-1)) {
        printError("[writer.cpp:shmat] ");
        deleteSegment(shmId);
        return 0;
    }

    std::string s = "Hello World!";
    std::strncpy(shmAddress, s.c_str(), s.size());

    shmdt(shmAddress);
    std::cout << SHM_KEY << "\n";
    return 0;
}