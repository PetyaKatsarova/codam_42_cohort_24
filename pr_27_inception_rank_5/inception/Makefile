COMPOSE=docker-compose -f srcs/docker-compose.yml --env-file srcs/.env
GREEN=\033[0;32m
END=\033[0m
VOLUME_DIR=$(HOME)/data/mariadb
SETUP_MARKER=.setup_done

.PHONY: all up down clean fclean re

all: _create_dirs up 

_create_dirs:
	@mkdir -p $(HOME)/data/mariadb
	@mkdir -p $(HOME)/data/wordpress
	@mkdir -p $(HOME)/data/redis

_check_docker:
	@docker ps > /dev/null 2>&1 || (echo "Docker not accessible. Run: newgrp docker" && exit 1)

up: _check_docker
	@printf "$(GREEN)Building images (no cache)...$(END)\n"
	$(COMPOSE) build --no-cache
	@printf "$(GREEN)Starting containers...$(END)\n"
	$(COMPOSE) up -d
	@printf "$(GREEN)✓ Containers started$(END)\n"
	@printf "$(GREEN)Testing Redis...$(END)\n"
	@sleep 2
	@docker exec redis redis-cli ping && echo "✓ Redis is running" || echo "✗ Redis failed"

down:
	@printf "$(GREEN)Stopping containers...$(END)\n"
	$(COMPOSE) down

clean: down

fclean: down
	@printf "$(GREEN)Cleaning volumes...$(END)\n"
	$(COMPOSE) down -v
	sudo rm -rf ~/data/mariadb ~/data/wordpress ~/data/redis

re: fclean all
