default:
	gcc -std=c11 -Wall -Wextra -Wshadow -Werror -g -pthread -o "demo" main.c ./libclient.so

