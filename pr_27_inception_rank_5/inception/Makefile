NAME=inception
COMPOSE=docker compose -f srcs/docker-compose.yml --env-file srcs/.env

all: up

up:
$(COMPOSE) up -d --build

down:
$(COMPOSE) down

clean: down

fclean:
$(COMPOSE) down -v

re: fclean up

.PHONY: all up down clean fclean re
