# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 03:50:25 by sbadr             #+#    #+#              #
#    Updated: 2022/12/22 00:57:47 by sbadr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER				=	server
SERVER_SRC			=	server.c
SERVER_OBJ			=	$(SERVER_SRC:.c=.o)

CLIENT				=	client
CLIENT_SRC			=	client.c 
CLIENT_OBJ			=	$(CLIENT_SRC:.c=.o)

SERVER_BNS			=	server_bns
SERVER_SRC_BNS		=	./bonus/server_bns.c
SERVER_OBJ_BNS		=	$(SERVER_SRC_BNS:.c=.o)

CLIENT_BNS	 		=	client_bns
CLIENT_SRC_BNS		=	./bonus/client_bns.c 
CLIENT_OBJ_BNS		=	$(CLIENT_SRC_BNS:.c=.o)

UTILS			=	utils
UTILS_SRC		=	./utils/ft_atoi.c ./utils/ft_putnbr_fd.c ./utils/ft_putstr.c
UTILS_OBJ		=	$(UTILS_SRC:.c=.o)

HEADER				=	minitalk.h
CC					=	cc
FLAGS				= 	-Wall -Werror -Wextra

all: $(UTILS_OBJ) $(SERVER) $(CLIENT)

bonus: $(UTILS_OBJ) $(SERVER_BNS) $(CLIENT_BNS)

$(SERVER): $(SERVER_OBJ) $(UTILS_OBJ)
	@$(CC) $(FLAGS) $(SERVER_OBJ) $(UTILS_OBJ) -o $(SERVER)

$(CLIENT): $(CLIENT_OBJ) $(UTILS_OBJ)
	@$(CC) $(FLAGS) $(CLIENT_OBJ) $(UTILS_OBJ) -o $(CLIENT)	

$(SERVER_BNS): $(SERVER_OBJ_BNS) $(UTILS_OBJ)
	@$(CC) $(FLAGS) $(SERVER_OBJ_BNS) $(UTILS_OBJ) -o $(SERVER_BNS)

$(CLIENT_BNS): $(CLIENT_OBJ_BNS) $(UTILS_OBJ)
	@$(CC) $(FLAGS) $(CLIENT_OBJ_BNS) $(UTILS_OBJ) -o $(CLIENT_BNS)

server: ${SERVER}

client: ${CLIENT}

bonus_srv: ${SERVER_BNS}

bonus_client: ${CLIENT_BNS}

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@rm -f $(SERVER_OBJ) $(UTILS_OBJ) $(CLIENT_OBJ) $(CLIENT_OBJ_BNS) $(SERVER_OBJ_BNS)

fclean : clean
	@rm -f $(SERVER) $(CLIENT) $(SERVER_BNS) $(CLIENT_BNS)

re : fclean all