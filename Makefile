# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sruff <sruff@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/13 14:23:17 by sruff             #+#    #+#              #
#    Updated: 2024/05/13 18:10:25 by sruff            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME    := so_long
CFLAGS  := -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX  := ./MLX42
HEADERS := -I./include -I$(LIBMLX)/include
LIBS    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS    := $(shell find ./src -iname "*.c")
OBJS    := ${SRCS:.c=.o}
all: libmlx $(NAME)

libmlx:
	git submodule update MLX42
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@cmake --build $(LIBMLX)/build -j4 

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"
	
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	
clean:
	@rm -rf $(OBJS)
	
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)/build
	
re: fclean all
.PHONY: all clean fclean re libmlx
