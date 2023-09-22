.PHONY: download run clean

CC = gcc

CFLAGS = -lm -g

SRCS = lenet.c main.c lenet_forward.c cnnapi_base.c utils.c

TARGET = lenet

$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

download:
	wget -c http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
	wget -c http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
	gzip -d t10k-labels-idx1-ubyte.gz
	gzip -d t10k-images-idx3-ubyte.gz

run:
	./lenet

clean:
	rm lenet
