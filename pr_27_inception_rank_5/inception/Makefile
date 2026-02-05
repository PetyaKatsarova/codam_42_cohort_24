NAME=inception
COMPOSE=docker-compose -f srcs/docker-compose.yml --env-file srcs/.env
GREEN=\033[0;32m
END=\033[0m
VOLUME_DIR=$(HOME)/data/mariadb
SETUP_MARKER=.setup_done

.PHONY: all up down clean fclean re setup

setup:
	@printf "$(GREEN)Running Docker setup...$(END)\n"
	@bash setup.sh && touch $(SETUP_MARKER)

all: _check_setup _create_dirs up 

_check_setup:
	@if [ ! -f "$(SETUP_MARKER)" ] || [ ! -d "$(VOLUME_DIR)" ]; then \
		printf "$(GREEN)Running initial setup...$(END)\n"; \
		bash setup.sh && touch $(SETUP_MARKER); \
	fi

_create_dirs:
	@mkdir -p $(HOME)/data/mariadb
	@mkdir -p $(HOME)/data/wordpress

_check_docker:
	@docker ps > /dev/null 2>&1 || (echo "Docker not accessible. Run: newgrp docker" && exit 1)

up: _check_docker
	@printf "$(GREEN)Starting Inception containers...$(END)\n"
	$(COMPOSE) up -d --build
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
