setup: build-boot

build-boot:
	docker exec -it tacos /usr/bin/make -C app/aarch/rasp4/boot clean
	docker exec -it tacos /usr/bin/make -C app/aarch/rasp4/boot

enter:
	docker exec -it --workdir /app tacos bash

start:
	docker-sync-stack start

generate-config:
	docker exec --workdir /generator tacos_sbt sbt "run --filename=$(file)"
	docker exec -it --workdir /app/src tacos g++ -c --std=c++17 kernel/config.cpp -I apex/ -I types/