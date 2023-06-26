#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include <sys/shm.h>
#include <sys/ipc.h>

void printError() {
    std::string s = std::to_string(errno);
    std::perror(s.c_str());
}

int main() {
    std::string keyString;
    std::cin >> keyString;
    int shmKey;
    try {
        shmKey = std::stoi(keyString);
    }
    catch(std::invalid_argument e) {
        std::cout << "Shared memory key is not a integer\n";
        return 0;
    }

    int shmId = shmget(shmKey, 1000, 0);
    if (shmId == -1) {
        printError();
        return 0;
    }

    char* shmAddress = (char*)shmat(shmId, 0, 0);
    if (shmAddress == (char*)(-1)) {
        printError();
        return 0;
    }

    std::cout << shmAddress << "\n";
    
    if (shmdt(shmAddress) == -1) {
        printError();
    }
    if (shmctl(shmId, IPC_RMID, (struct shmid_ds *) 0) == -1) {
        printError();
    }
    return 0;
}