TARGET=tiny-web
OBJS=main.o sockfd.o

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS)

clean:
	rm *.o
