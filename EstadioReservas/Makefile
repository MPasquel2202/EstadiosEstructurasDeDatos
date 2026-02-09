CXX = g++
CXXFLAGS = -std=gnu++17 -Wall -Wextra -Wpedantic -O2
INCLUDES = -Iinclude
SRC_DIR = src
BIN = estadio

SRCS = \
  $(SRC_DIR)/main.cpp \
  $(SRC_DIR)/model/Fecha.cpp \
  $(SRC_DIR)/model/Usuario.cpp \
  $(SRC_DIR)/model/Evento.cpp \
  $(SRC_DIR)/model/InventarioEvento.cpp \
  $(SRC_DIR)/model/Reserva.cpp \
  $(SRC_DIR)/view/MenuView.cpp \
  $(SRC_DIR)/view/Printer.cpp \
  $(SRC_DIR)/controller/AuthController.cpp \
  $(SRC_DIR)/controller/EventoController.cpp \
  $(SRC_DIR)/controller/ReservaController.cpp \
  $(SRC_DIR)/utils/CedulaEC.cpp \
  $(SRC_DIR)/utils/DateUtils.cpp \
  $(SRC_DIR)/utils/JsonStore.cpp \
  $(SRC_DIR)/utils/InputUtils.cpp \
  $(SRC_DIR)/utils/OrdenamientoController.cpp \
  $(SRC_DIR)/utils/EstrategiasController.cpp \
  $(SRC_DIR)/utils/BSTDemo.cpp \
  $(SRC_DIR)/structures/HashTable.cpp \
  $(SRC_DIR)/structures/BinarySearchTree.cpp

OBJS = $(SRCS:.cpp=.o)

JSON_HEADER = include/nlohmann/json.hpp

all: check-json libDLLBigO.so $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

libDLLBigO.so:
	$(CXX) -shared -fPIC -o libDLLBigO.so DLLBigO/DLLBigO/dllmain.cpp

run: all
	./$(BIN)

clean:
	rm -f $(OBJS) $(BIN) libDLLBigO.so

check-json:
	@if [ ! -f "$(JSON_HEADER)" ]; then \
		echo ">> json.hpp no encontrado. Intentando descargar..."; \
		bash ./scripts/fetch_json.sh || true; \
	fi
	@if [ ! -f "$(JSON_HEADER)" ]; then \
		echo "ERROR: Falta include/nlohmann/json.hpp. Ejecuta scripts/fetch_json.sh (Linux/macOS) o scripts/fetch_json.ps1 (Windows)"; \
		exit 1; \
	fi

.PHONY: all run clean check-json
