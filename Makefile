args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`

# Help rule to get the arguments
%:
	@:

help:		## Show this help.
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'

.PHONY: bash
bash: build	## Enter oregex docker
	@docker-compose run oregex bash

.PHONY: build
build:		## Builds oregex docker
	@docker-compose build

.PHONY: test
test: build	## Execute library tests
	@docker-compose run --rm oregex make -f ./docker/Makefile test

.PHONY: memcheck	## Execute valgrind leak check on binary
memcheck: clean
	@docker-compose run --rm oregex make -f ./docker/Makefile memcheck OPTIMIZATION_FLAG='-O0'

.PHONY: clean
clean: build	## Clean all the created data
	@docker-compose run --rm oregex make -f ./docker/Makefile clean
