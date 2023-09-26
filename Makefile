.PHONY: download run clean

CC = gcc

CFLAGS = -g
LDFLAGS = -lm

SRCDIR = src
INCDIR = include

#SRCS = $(wildcard $(SRCDIR)/*.c)
SRCS = $(SRCDIR)/main.c $(SRCDIR)/lenet.c $(SRCDIR)/lenet_forward.c $(SRCDIR)/cnnapi.c $(SRCDIR)/normal_instr.c $(SRCDIR)/utils.c
INCLUDES = -I$(INCDIR)

TARGET = lenet

$(TARGET): $(SRCS)
	$(CC) $(INCLUDES) $(SRCS) -o $(TARGET) $(LDFLAGS) $(CFLAGS)

download:
	wget -c http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
	wget -c http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
	gzip -d t10k-labels-idx1-ubyte.gz
	gzip -d t10k-images-idx3-ubyte.gz

run:
	./lenet

clean:
	rm lenet
