# Trabalho Final — Programação Concorrente (Etapas 1 e 2)

## Tema: Servidor de Chat Multiusuário (TCP)

Este repositório contém o desenvolvimento de um servidor de chat multiusuário em C++, como parte do trabalho final da disciplina de Programação Concorrente.  
O projeto é construído em etapas, com progresso marcado por tags do Git (`v1-logging`, `v2-cli`, etc.).

---

## Etapa 1: Biblioteca de Logging Thread-Safe

**Tag:** `v1-logging`

O foco desta etapa foi a implementação de uma biblioteca de logging thread-safe (`Logger`) e a definição da arquitetura inicial do sistema.  
Essa base garante que eventos possam ser registrados de forma segura em um ambiente concorrente.

**Entregas principais da Etapa 1:**
- **Logger Thread-Safe:** `include/logger.h` e `src/logger.cpp`
- **Teste de Concorrência:** `tests/test_logger.cpp`
- **Arquivo de log:** `log.txt` gerado pelo teste
- **Diagrama de Arquitetura:** `diagrams/arquitetura.md`

---

## Etapa 2: Protótipo de Comunicação CLI

**Tag:** `v2-cli`

Nesta etapa, foi implementado o protótipo funcional cliente-servidor.

### Servidor (`server`)
- Executável que inicia um servidor TCP na porta 8080.
- Cria uma thread para cada cliente conectado (concorrente).
- Todas as mensagens recebidas são retransmitidas (broadcast) para os demais clientes.

### Cliente (`client`)
- Executável de linha de comando para conectar-se ao servidor.
- Permite enviar mensagens e receber mensagens de outros usuários em tempo real.

### Logging
O logger da Etapa 1 foi totalmente integrado para registrar eventos importantes, como conexões, desconexões e mensagens recebidas.

---

## Como Compilar e Executar

### 1. Compilar o Projeto

Na raiz do repositório, execute:

```sh
make

Isso irá compilar o projeto e gerar os executáveis principais: server e client.

Para garantir uma compilação limpa, utilize:

make clean && make

2. Executar o Chat
Você precisará de pelo menos dois terminais abertos na pasta do projeto.

No Terminal 1 (Servidor):

./server

O servidor ficará rodando e aguardando conexões.

Nos Terminais 2, 3, 4, etc. (Clientes):

./client

Digite sua mensagem e pressione Enter.
As mensagens dos outros usuários aparecerão em tempo real.

Para sair do chat, digite:

sair

3. Limpar os Arquivos Gerados
Para remover todos os executáveis, arquivos objeto e o arquivo log.txt:

make clean