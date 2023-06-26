#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_KEY 1112

void printError() {
    std::string s = std::to_string(errno);
    std::perror(s.c_str());
}

int main() {
    int shmId = shmget(SHM_KEY, 1000, IPC_CREAT | IPC_EXCL | 0666);
    if (shmId == -1) {
        printError();
        return 0;
    }
    
    char* shmAddress;
    shmAddress = (char*)shmat(shmId, 0, 0);
    if (shmAddress == (char*)(-1)) {
        printError();
        if (shmctl(shmId, IPC_RMID, (struct shmid_ds *) 0) == -1) {
            printError();
        }
        return 0;
    }

    std::string str = "Hello World!";
    std::strncpy(shmAddress, str.c_str(), str.size());

    if (shmdt(shmAddress) == -1) {
        printError();
    }

    std::cout << SHM_KEY << "\n";
    return 0;
}