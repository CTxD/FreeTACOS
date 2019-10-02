setup: build-boot

build-boot:
	docker exec -it tacos /usr/bin/make -C app/aarch/rasp4/boot clean
	docker exec -it tacos /usr/bin/make -C app/aarch/rasp4/boot

enter:
	docker exec -it --workdir /app tacos bash

start:
	docker-sync-stack start
