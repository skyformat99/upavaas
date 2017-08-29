ifeq ($(OS),Windows_NT)
$(error "windows not supported")
else
UNAME_OS := $(shell uname -s)
ifeq ($(UNAME_OS),Linux)
LDFLAGS := -pthread
else
LDFLAGS := -lpthread
endif
endif

FILES := upalight options event
OBJECTS := $(addsuffix .o,$(FILES))
BINARY := upald
CFLAGS ?= -O2

define genrule
$1.o: $1.c $1.h
	$(CC) $(CFLAGS) -c -o $$@ $$<
endef

.PHONY: all
all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(foreach file,$(FILES),$(eval $(call genrule,$(file))))

.PHONY: clean
clean:
	rm -f *.o $(BINARY)
