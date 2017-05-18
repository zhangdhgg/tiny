TARGET=tiny-web
OBJS=main.o sockfd.o rio_packet.o req_handle.o

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS)

clean:
	rm *.o tiny-web
