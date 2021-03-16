
SRC_DIR		:=	src/

BUILD_DIR	:=	build/

INCLUDE_DIR	:=	include/

SRC 		:=	$(shell find $(SRC_DIR) -name '*.c')

OBJECTS		:=	$(addprefix $(BUILD_DIR),$(SRC:$(SRC_DIR)%.c=%.o))

STRUCTURE	:=	$(shell find $(SRC_DIR) -type d) 

BINARY		:=	wolf

CFLAGS		:=	-Wall -g

LDFLAGS		:=	-lm -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio

all: $(BINARY)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	gcc $(CFLAGS) $(LDFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(BINARY)
	rm -rf $(BUILD_DIR)

re: fclean all