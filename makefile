# Compilador C++
CXX = g++

# Flags de compilação (-pthread é essencial para threads)
CXXFLAGS = -std=c++17 -Wall -g -pthread

# Diretório de includes
IDIR = -Iinclude

# Nome do executável final
TARGET = test_runner

# Fontes: lista todos os .cpp que serão usados
SOURCES = src/logger.cpp tests/test_logger.cpp

# Objetos: converte a lista de .cpp para .o
OBJECTS = $(SOURCES:.cpp=.o)

# Regra principal: compila o alvo
all: $(TARGET)

# Regra de linkagem: junta os arquivos .o para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra de compilação: transforma qualquer .cpp em .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(IDIR) -c -o $@ $<

# Regra para limpar os arquivos gerados
clean:
	rm -f $(TARGET) $(OBJECTS) log.txt

.PHONY: all clean