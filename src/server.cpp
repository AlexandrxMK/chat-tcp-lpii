#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <deque> 
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "logger.h"

using namespace std;

struct ClientInfo {
    int socket_fd;
    string ip_addr;
};

vector<ClientInfo> clients;
mutex client_mutex;
deque<string> message_history; 
const int MAX_HISTORY_SIZE = 10;

void add_to_history(const string& message) {
    lock_guard<mutex> lock(client_mutex);
    message_history.push_back(message);
    if (message_history.size() > MAX_HISTORY_SIZE) {
        message_history.pop_front();
    }
}

void broadcast_message(const string& message, int sender_fd) {
    lock_guard<mutex> lock(client_mutex);
    for (const auto& client : clients) {
        if (client.socket_fd != sender_fd) {
            send(client.socket_fd, message.c_str(), message.length(), 0);
        }
    }
}

void handle_client(int client_fd, string client_ip) {
    Logger::getInstance().log("Novo cliente conectado: " + client_ip);
    cout << "Novo cliente conectado: IP " << client_ip << endl;

    {
        lock_guard<mutex> lock(client_mutex);
        clients.push_back({client_fd, client_ip});

        Logger::getInstance().log("Enviando historico para " + client_ip);
        for (const string& msg : message_history) {
            string history_msg = msg + "\n";
            send(client_fd, history_msg.c_str(), history_msg.length(), 0);
        }
    }

    char buffer[4096];
    while (true) {
        memset(buffer, 0, 4096);
        int bytes_received = recv(client_fd, buffer, 4096, 0);

        if (bytes_received <= 0) {
            Logger::getInstance().log("Cliente " + client_ip + " desconectou.");
            cout << "Cliente " + client_ip + " desconectou." << endl;
            break;
        }

        string received_message(buffer, bytes_received);
        string formatted_message = "[" + client_ip + "]: " + received_message;

        Logger::getInstance().log("Mensagem recebida de " + client_ip + ": " + received_message);
        cout << formatted_message;

        add_to_history(formatted_message);
        broadcast_message(formatted_message + "\n", client_fd);
    }

    {
        lock_guard<mutex> lock(client_mutex);
        clients.erase(
            remove_if(clients.begin(), clients.end(), [client_fd](const ClientInfo& client) {
                return client.socket_fd == client_fd;
            }),
            clients.end()
        );
    }
    close(client_fd);
}


int main() {
    const int PORT = 8080;
    int server_fd;
    struct sockaddr_in address;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        Logger::getInstance().log("ERRO: Falha ao criar o socket do servidor.");
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    Logger::getInstance().log("Socket do servidor criado com sucesso.");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        Logger::getInstance().log("ERRO: Falha ao fazer o bind do socket na porta " + to_string(PORT));
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    Logger::getInstance().log("Bind do socket na porta " + to_string(PORT) + " realizado com sucesso.");

    if (listen(server_fd, 10) < 0) {
        Logger::getInstance().log("ERRO: Falha ao colocar o servidor para escutar.");
        perror("listen");
        exit(EXIT_FAILURE);
    }

    Logger::getInstance().log("Servidor esta no ar, aguardando conexoes na porta " + to_string(PORT));
    cout << "Servidor esta no ar, aguardando conexoes na porta " << PORT << "..." << endl;

    while (true) {
        struct sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);
        int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_len);

        if (client_fd < 0) {
            Logger::getInstance().log("ERRO: Falha ao aceitar nova conexao.");
            perror("accept");
            continue; 
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);

        thread(handle_client, client_fd, string(client_ip)).detach();
    }

    close(server_fd);
    return 0;
}