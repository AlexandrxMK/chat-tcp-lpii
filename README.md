# Trabalho Final — Programação Concorrente (Etapa 1)

## Tema: Servidor de Chat Multiusuário (TCP)

Este repositório contém a primeira etapa do desenvolvimento de um servidor de chat multiusuário em C++, como parte do trabalho final da disciplina de Programação Concorrente.

---

## Objetivo da Etapa 1
O foco desta etapa foi a implementação de uma biblioteca de **logging thread-safe (Logger)** em C++.  
Esta biblioteca foi projetada com uma API clara e segura para garantir que múltiplas threads possam registrar mensagens em um arquivo de log de forma concorrente, sem causar condições de corrida ou corromper o arquivo.

Além da biblioteca, a arquitetura inicial do projeto foi definida e a estrutura de diretórios foi organizada para facilitar o desenvolvimento futuro.

---

## Entregas desta Etapa
- **Logger Thread-Safe:** Implementação completa nos arquivos `include/logger.h` e `src/logger.cpp`.  
- **Teste de Concorrência:** Programa em `tests/test_logger.cpp` que simula múltiplas threads gravando logs simultaneamente, verificando a segurança da implementação.  
- **Arquivo de Log:** O teste gera um arquivo `log.txt` como saída.  
- **Diagrama de Arquitetura:** Arquivo `diagrams/arquitetura.md` descrevendo a arquitetura inicial do sistema.  
- **Makefile:** Makefile funcional para compilar o projeto (`make` ou `make all`) e limpar os arquivos gerados (`make clean`).  

---

## Como Compilar e Executar
Siga os passos abaixo para compilar e executar o programa de teste do logger.

### 1. Compilar o projeto
Na raiz do repositório, execute:
```bash
make
Isso irá compilar o código-fonte e gerar o executável test_runner.

2. Executar o teste
Após a compilação, rode:
./test_runner

3. Verificar a saída
A execução irá gerar (ou sobrescrever) um arquivo chamado log.txt na raiz do projeto.
Você pode abri-lo para verificar os logs gravados pelas diferentes threads.

4. Limpar o projeto
Para remover o executável e o arquivo de log, utilize:

make clean