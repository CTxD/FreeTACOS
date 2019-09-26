setup: build-boot

build-boot:
	docker exec -it arinc_circle /usr/bin/make -C circle/boot clean
	docker exec -it arinc_circle /usr/bin/make -C circle/boot

enter: 
	docker exec -it --workdir /circle arinc_circle bash

