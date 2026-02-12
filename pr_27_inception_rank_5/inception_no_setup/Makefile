NAME=inception
COMPOSE=docker-compose -f srcs/docker-compose.yml --env-file srcs/.env
GREEN=\033[0;32m
END=\033[0m
VOLUME_DIR=$(HOME)/data/mariadb

.PHONY: all up down clean fclean re

all: _create_dirs up 

_create_dirs:
	@mkdir -p $(HOME)/data/mariadb
	@mkdir -p $(HOME)/data/wordpress

_check_docker:
	@docker ps > /dev/null 2>&1 || (echo "Docker not accessible. Run: newgrp docker" && exit 1)

up: _check_docker
	@printf "$(GREEN)Building images (no cache)...$(END)\n"
	$(COMPOSE) build --no-cache
	@printf "$(GREEN)Starting containers...$(END)\n"
	$(COMPOSE) up -d
	@printf "$(GREEN)✓ Containers started$(END)\n"

down:
	@printf "$(GREEN)Stopping containers...$(END)\n"
	$(COMPOSE) down

clean: down

fclean: down
	@printf "$(GREEN)Cleaning volumes...$(END)\n"
	$(COMPOSE) down -v
	sudo rm -rf ~/data/mariadb ~/data/wordpress

re: fclean all
