#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm> // <-- A CORREÇÃO ESTÁ AQUI
#include "logger.h"

using namespace std;

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

struct ClientInfo {
    int socket_fd;
    string ip_addr;
};

vector<ClientInfo> clients;
mutex clients_mutex;

void error(const string& msg);
void handle_client(int client_fd, string client_ip);

int main() {
    Logger::getInstance().log("=== INICIANDO SERVIDOR DE CHAT ===");

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) error("Nao foi possivel criar o socket");
    Logger::getInstance().log("Socket do servidor criado com sucesso.");

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        error("Falha ao vincular o socket a porta " + to_string(PORT));
    }
    Logger::getInstance().log("Socket vinculado a porta " + to_string(PORT));

    if (listen(server_fd, 10) < 0) error("Falha ao colocar o socket em modo de escuta");
    Logger::getInstance().log("Servidor escutando na porta " + to_string(PORT) + "...");
    cout << "Servidor esta no ar, aguardando conexoes na porta " << PORT << "." << endl;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) {
            Logger::getInstance().log("ERRO: Falha ao aceitar conexao do cliente.");
            continue;
        }

        char client_ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip_str, INET_ADDRSTRLEN);
        string client_ip(client_ip_str);
        
        Logger::getInstance().log("NOVO CLIENTE CONECTADO: IP " + client_ip);
        cout << "Novo cliente conectado: IP " + client_ip << endl;

        {
            lock_guard<mutex> lock(clients_mutex);
            clients.push_back({client_fd, client_ip});
        }

        thread(handle_client, client_fd, client_ip).detach();
    }

    close(server_fd);
    Logger::getInstance().log("=== SERVIDOR FINALIZADO ===");
    return 0;
}

void handle_client(int client_fd, string client_ip) {
    char buffer[BUFFER_SIZE];
    
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);

        if (bytes_read <= 0) {
            cout << "Cliente " << client_ip << " desconectou." << endl;
            Logger::getInstance().log("Cliente desconectado: IP " + client_ip);
            break;
        }

        string received_msg = string(buffer, bytes_read);
        Logger::getInstance().log("Msg recebida de [" + client_ip + "]: " + received_msg);

        string broadcast_msg = "[" + client_ip + "]: " + received_msg;

        lock_guard<mutex> lock(clients_mutex);
        for (const auto& client : clients) {
            if (client.socket_fd != client_fd) {
                send(client.socket_fd, broadcast_msg.c_str(), broadcast_msg.length(), 0);
            }
        }
    }

    {
        lock_guard<mutex> lock(clients_mutex);
        clients.erase(
            remove_if(clients.begin(), clients.end(), [client_fd](const ClientInfo& client) {
                return client.socket_fd == client_fd;
            }),
            clients.end()
        );
    }

    close(client_fd);
}

void error(const string& msg) {
    Logger::getInstance().log("ERRO FATAL: " + msg + " - " + strerror(errno));
    exit(1);
}