CXX = g++
CXXFLAGS = -std=gnu++17 -Wall -Wextra -Wpedantic -O2
INCLUDES = -Iinclude
SRC_DIR = src
BIN = estadio

MONGO_CFLAGS := $(shell pkg-config --cflags libmongocxx 2>/dev/null)
MONGO_LIBS := $(shell pkg-config --libs libmongocxx 2>/dev/null)

CPPFLAGS := $(MONGO_CFLAGS)
LDFLAGS := $(MONGO_LIBS)

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
  $(SRC_DIR)/utils/MongoConnection.cpp \
  $(SRC_DIR)/utils/MongoStore.cpp \
  $(SRC_DIR)/utils/InputUtils.cpp \
  $(SRC_DIR)/utils/OrdenamientoController.cpp \
  $(SRC_DIR)/utils/BSTDemo.cpp \
  $(SRC_DIR)/structures/HashTable.cpp \
  $(SRC_DIR)/structures/BinarySearchTree.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@

run: all
	./$(BIN)

clean:
	rm -f $(OBJS) $(BIN)

.PHONY: all run clean
