// Домашнее задание к занятию «Многопоточность»
// Задание 1.Очередь клиентов

#include <iostream>
#include <thread>
#include <mutex>
#include <functional>


void clientThread(int* maxClients, int* clientCounter, std::mutex* mtx) {
    while (*clientCounter < *maxClients) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(*mtx);
        clientCounter++;
        std::cout << "Client joined, total clients: " << clientCounter << std::endl;
    }
}

void operatorThread() {
    while (clientCounter > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::lock_guard<std::mutex> lock(mtx);
        clientCounter--;
        std::cout << "Client served, total clients: " << clientCounter << std::endl;
    }
}

int main() 
{
    int maxClients = 7;
    int clientCounter = 0;
    std::mutex mtx;

    std::thread client(clientThread(&maxClients, &clientCounter, &mtx));
    std::thread operatorT(operatorThread);

    client.join();
    operatorT.join();

    return 0;
}
