# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melsahha <melsahha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 14:57:25 by melsahha          #+#    #+#              #
#    Updated: 2023/05/05 14:28:58 by melsahha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

PRINTF_DIR = libft/
PRINTF_LIB = libftprintf.a

NAME = minitalk
INCL = .include/

CLIENT_NAME = client
CLIENT_SRC = client.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

SERVER_NAME = server
SERVER_SRC = server.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)

OBJS = $(CLIENT_SRC:.c=.o) $(SERVER_SRC:.c=.o)

BONUS_SERVER_NAME = server_bonus
BONUS_SERVER_SRC = server_bonus.c
BONUS_SERVER_OBJ = $(BONUS_SERVER_SRC:.c=.o)

BONUS_CLIENT_NAME = client_bonus
BONUS_CLIENT_SRC = client_bonus.c
BONUS_CLIENT_OBJ = $(BONUS_CLIENT_SRC:.c=.o)

##############################################

$(NAME): $(SERVER_NAME) $(CLIENT_NAME)

all: $(NAME) bonus

$(PRINTF_LIB):
	make -sC $(PRINTF_DIR)
	mv $(addprefix $(PRINTF_DIR), $(PRINTF_LIB)) .

$(SERVER_NAME): $(SERVER_OBJ) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -L. -lftprintf -o $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJ) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -L. -lftprintf -o $(CLIENT_NAME)

$(CLIENT_OBJ): %.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

$(SERVER_OBJ): %.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

bonus: $(BONUS_CLIENT_NAME) $(BONUS_SERVER_NAME)

$(BONUS_CLIENT_NAME): $(BONUS_CLIENT_OBJ) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(BONUS_CLIENT_OBJ) -L. -lftprintf -o $(BONUS_CLIENT_NAME)

$(BONUS_SERVER_NAME): $(BONUS_SERVER_OBJ) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(BONUS_SERVER_OBJ) -L. -lftprintf -o $(BONUS_SERVER_NAME)

$(BONUS_CLIENT_OBJ): %.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

$(BONUS_SERVER_OBJ): %.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCL) $< -o $@

clean:
	make -C $(PRINTF_DIR) clean
	rm -f $(CLIENT_OBJ) $(SERVER_OBJ) $(BONUS_CLIENT_OBJ) $(BONUS_SERVER_OBJ)

fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME) $(BONUS_CLIENT_NAME) $(BONUS_SERVER_NAME) $(PRINTF_LIB)

re: fclean all

.PHONY: all clean fclean re
