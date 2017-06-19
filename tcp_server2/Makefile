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
				-lboost_date_time \
				-lboost_unit_test_framework \
				-lboost_test_exec_monitor
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


TEST_DIR = ./test
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(TEST_SOURCES)))
TEST_OBJECTS += $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS))
TEST_TARGET = test_main
BIN_TEST_TARGET = $(BIN_DIR)/$(TEST_TARGET)

test:$(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $(BIN_TEST_TARGET) $(INCLUDES) $(LDLIBS) 

$(OBJ_DIR)/%.o:$(TEST_DIR)/%.cpp 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {} \;
	find ${DIR_BIN} -name ${TARGET}  -exec rm -rf {} \;
	find ${DIR_BIN} -name ${TEST_TARGET}  -exec rm -rf {} \;
