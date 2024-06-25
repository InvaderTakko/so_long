
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sruff <sruff@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 14:23:17 by sruff             #+#    #+#              #
#    Updated: 2024/05/28 13:23:28 by sruff            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME    := so_long
CFLAGS  := -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX  := ./MLX42
LIBFT   := ./src/libft
HEADERS := -I./include -I$(LIBMLX)/include -I . -I $(LIBFT)
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm -L$(LIBFT) -lft
SRCS    := $(shell find ./src -iname "*.c")
OBJS    := ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	git submodule update MLX42
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@cmake --build $(LIBMLX)/build -j4 

libft:
	$(MAKE) -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	
clean:
	@rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT) clean
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)/build
	$(MAKE) -C $(LIBFT) fclean
	
re: fclean all

.PHONY: all clean fclean re libmlx libft

#ARM MACBOOK
# NAME    := so_long
# CFLAGS  := -Wextra -Wall -Werror -Wunreachable-code -Ofast -arch arm64
# LIBMLX  := ./MLX42
# LIBFT   := ./src/libft
# HEADERS := -I./include -I$(LIBMLX)/include -I . -I $(LIBFT) -I/opt/homebrew/include
# LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -L/opt/homebrew/lib -lglfw -pthread -lm -L$(LIBFT) -lft
# SRCS    := $(shell find ./src -iname "*.c")
# OBJS    := ${SRCS:.c=.o}

# all: libmlx libft $(NAME)

# libmlx:
# 	git submodule update MLX42
# 	@cmake $(LIBMLX) -B $(LIBMLX)/build
# 	@cmake --build $(LIBMLX)/build -j4 

# libft:
# 	$(MAKE) -C $(LIBFT)

# %.o: %.c
# 	@clang $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	
# $(NAME): $(OBJS)
# 	@clang $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	
# clean:
# 	@rm -rf $(OBJS)
# 	$(MAKE) -C $(LIBFT) clean
	
# fclean: clean
# 	@rm -rf $(NAME)
# 	@rm -rf $(LIBMLX)/build
# 	$(MAKE) -C $(LIBFT) fclean
	
# re: fclean all

# .PHONY: all clean fclean re libmlx libft