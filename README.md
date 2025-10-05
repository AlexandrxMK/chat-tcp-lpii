# Trabalho Final — Programação Concorrente

## Tema: Servidor de Chat Multiusuário (TCP)

Este repositório contém o desenvolvimento completo de um servidor de chat multiusuário em C++, como parte do trabalho final da disciplina de Programação Concorrente.  
O projeto foi construído em três etapas, com o progresso de cada uma marcado por tags do Git.

---

## Etapa 1: Biblioteca de Logging Thread-Safe (`v1-logging`)

O foco inicial foi a implementação de uma biblioteca de logging (`Logger`) segura para uso concorrente e a definição da arquitetura inicial do sistema.

---

## Etapa 2: Protótipo de Comunicação CLI (`v2-cli`)

Nesta etapa, foi implementado o protótipo funcional cliente-servidor, permitindo que múltiplos clientes se conectassem, enviassem mensagens e as recebessem em tempo real (broadcast).

---

## Etapa 3: Sistema Completo e Relatório Final (`v3-final`)

A última etapa consistiu em finalizar as funcionalidades (como um histórico de mensagens para novos clientes) e na elaboração de um relatório técnico completo, incluindo um diagrama de sequência e uma análise de concorrência com auxílio de IA.

---

## Como Compilar e Executar o Chat

### 1. Pré-requisitos

- Compilador C++ (g++)
- Git
- Make

### 2. Compilar o Projeto

Na raiz do repositório, execute o seguinte comando. Ele irá gerar os executáveis `server` e `client`:

```sh
make

Para garantir uma compilação limpa, utilize:

make clean && make

3. Executar o Chat
Você precisará de pelo menos dois terminais abertos na pasta do projeto.

No Terminal 1 (Servidor):
Inicie o servidor. Ele ficará rodando e aguardando conexões.

./server

Nos Terminais 2, 3, etc. (Clientes):
Inicie um cliente em cada terminal.

./client

Digite uma mensagem e pressione Enter.
As mensagens dos outros usuários aparecerão em tempo real.
Para sair do chat, digite sair e pressione Enter.

4. Limpar os Arquivos Gerados
Para remover todos os executáveis, arquivos objeto e o log.txt:

make clean