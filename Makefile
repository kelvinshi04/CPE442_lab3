CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -I /usr/include/openv4
LDFLAGS = -lopencv_imgcodecs -lopencv_core -lopencv_highgui -lopencv_videoio
TARGET = lab3
SRC = lab3.cpp

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)