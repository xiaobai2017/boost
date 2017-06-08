CXXFLAGS = -g -Wall -std=c++11

OBJS =	main.o

LIBS = -pthread \
				-lboost_log \
				-lboost_system \
				-lboost_thread \
				-lboost_regex 
				#-lboost_date_time \
				#-lboost_chrono \
				#-lboost_serialization \
				#-lboost_atomic \
				#-lboost_filesystem \
				#-lboost_log_set

TARGET =	example

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
