# Compilador C++
CXX = g++

# Flags de compilação (-pthread é essencial para threads)
CXXFLAGS = -std=c++17 -Wall -g -pthread

# Diretório de includes
IDIR = -Iinclude

# --- Alvos/Executáveis ---
SERVER_TARGET = server
CLIENT_TARGET = client
TEST_TARGET = test_runner

# --- Fontes e Objetos ---
COMMON_SOURCES = src/logger.cpp
SERVER_SOURCES = src/server.cpp $(COMMON_SOURCES)
CLIENT_SOURCES = src/client.cpp $(COMMON_SOURCES) # Adicionamos o client.cpp aqui
TEST_SOURCES = tests/test_logger.cpp $(COMMON_SOURCES)

# Regra para converter .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(IDIR) -c -o $@ $<

# --- Regras Principais ---

# 'make' ou 'make all' agora compila o servidor E o cliente
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Regra de linkagem para o servidor
$(SERVER_TARGET): $(SERVER_SOURCES:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra de linkagem para o cliente
$(CLIENT_TARGET): $(CLIENT_SOURCES:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar e rodar o teste do logger
test: $(TEST_TARGET)
$(TEST_TARGET): $(TEST_SOURCES:.cpp=.o)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para limpar tudo
clean:
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET) $(TEST_TARGET) src/*.o tests/*.o log.txt

.PHONY: all clean test