# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ajoliet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 16:45:49 by ajoliet           #+#    #+#              #
#    Updated: 2022/12/15 16:45:53 by ajoliet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SER = server
SER_SRCS = server.c \
		   utils_server.c
SER_OBJS = $(SER_SRCS:.c=.o)
CLI = client
CLI_SRCS = client.c \
		   utils_client.c
CLI_OBJS = $(CLI_SRCS:.c=.o)
RM = rm -r
CCF = gcc -g -Wall -Wextra -Werror

all: $(SER) $(CLI)

$(SER): $(SER_OBJS)
	$(CCF) -o $(SER) $(SER_SRCS)

$(CLI): $(CLI_OBJS)
	$(CCF)  -o $(CLI) $(CLI_SRCS)

clean:
	$(RM) $(SER_OBJS) $(CLI_OBJS)

fclean: clean
	$(RM) $(SER) $(CLI)

re: fclean $(SER) $(CLI)

.PHONY: all fclean clean re
