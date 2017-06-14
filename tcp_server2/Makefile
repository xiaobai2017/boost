#CXXFLAGS = -g -Wall -std=c++11

INC_DIR = ./inc
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))
CFLAGS = -std=c++11 -g -Wall

LDLIBS = -pthread \
				-lboost_log \
				-lboost_system \
				-lboost_thread \
				-lboost_regex \
				-lboost_date_time
				#-lboost_chrono \
				#-lboost_serialization \
				#-lboost_atomic \
				#-lboost_filesystem \
				#-lboost_log_set
				
INCLUDES = -I$(INC_DIR)
TARGET = tcp_server
BIN_TARGET = $(BIN_DIR)/$(TARGET)
CC = g++

$(BIN_TARGET):$(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN_TARGET) $(INCLUDES) $(LDLIBS) 

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	find ${DIR_BIN} -name ${TARGET} -exec rm -rf {} \;
