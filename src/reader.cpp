#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>

void printError(std::string s) {
    std::string error = s + std::to_string(errno);
    std::perror(error.c_str());
}

void deleteSegment(int shmId) {
    if (shmctl(shmId, IPC_RMID, (struct shmid_ds *) 0) == -1) {
        printError("[writer.cpp:shmctl] ");
    }
}

int main() {
    int shmKey;
    std::cin >> shmKey;
    int shmId = shmget(shmKey, 1000, 0);
    if (shmId == -1) {
        printError("[reader.cpp:shmget] ");
        return 0;
    }

    char* shmAddress = (char*)shmat(shmId, 0, 0);
    if (shmAddress == (char*)(-1)) {
        printError("[reader.cpp:shmat] ");
        deleteSegment(shmId);
        return 0;
    }

    std::cout << shmAddress << "\n";
    
    shmdt(shmAddress);
    deleteSegment(shmId);
    return 0;
}