CC 				:= 	gcc
CFLAGS 		:= 	-Iinclude \
							-std=c99

LDLIBS 		:=
LDFLAGS 	:=

SRC_DIR 	:=	src
BUILD_DIR := 	build

MAIN  		:=	$(BUILD_DIR)/robochess

CSRCS 		:= 	$(wildcard $(SRC_DIR)/*.c)

OBJS 			:= 	$(notdir $(CSRCS))
OBJS 			:= 	$(patsubst %.c, $(BUILD_DIR)/%.o, $(OBJS))

.PHONY: all
all: $(MAIN)

# make the build folder
$(BUILD_DIR):
	mkdir -p $@

# link
$(MAIN): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)
