#include <iostream>
#include <thread>
#include <vector>
#include "logger.h" 

void log_messages_from_thread(int thread_id) {
    for (int i = 0; i < 20; ++i) {
        std::string message = "Thread " + std::to_string(thread_id) + " escrevendo a mensagem " + std::to_string(i);
        Logger::getInstance().log(message);
    }
}

int main() {
    std::cout << "Iniciando teste de log com multiplas threads..." << std::endl;
    Logger::getInstance().log("=== INICIO DO TESTE ===");

    const int NUM_THREADS = 5;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i) {
        threads.emplace_back(log_messages_from_thread, i + 1);
    }

    for (auto& t : threads) {
        t.join();
    }

    Logger::getInstance().log("=== FIM DO TESTE ===");
    std::cout << "Teste finalizado. Verifique o arquivo 'log.txt'." << std::endl;

    return 0;
}