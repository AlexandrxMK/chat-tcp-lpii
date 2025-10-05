#include <iostream>
#include <string>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

const int PORT = 8080;
const char* SERVER_IP = "127.0.0.1";
const int BUFFER_SIZE = 1024;

void error(const string& msg);
void receive_messages(int socket_fd);

int main() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) error("Nao foi possivel criar o socket");
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        error("Endereco IP invalido ou nao suportado");
    }

    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        error("Falha na conexao com o servidor");
    }

    cout << "Conectado com sucesso ao servidor! Pode comecar a enviar mensagens." << endl;
    cout << "Digite 'sair' para desconectar." << endl;

    thread(receive_messages, client_fd).detach();

    string line;
    while (getline(cin, line)) {
        if (line == "sair") {
            break;
        }

        send(client_fd, line.c_str(), line.length(), 0);
    }

    cout << "Fechando conexao." << endl;
    close(client_fd);
    return 0;
}

void receive_messages(int socket_fd) {
    char buffer[BUFFER_SIZE];
    while (true) {S
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(socket_fd, buffer, BUFFER_SIZE - 1);
        
        if (bytes_read <= 0) {
            cout << "\nVoce foi desconectado do servidor." << endl;
            close(socket_fd);
            exit(0);
        }
        
        cout << "\n" << string(buffer, bytes_read) << endl;
    }
}

void error(const string& msg) {
    cerr << "ERRO: " << msg << " - " << strerror(errno) << endl;
    exit(1);
}