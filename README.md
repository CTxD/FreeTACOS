# AAOS
Awesome Avionics Operating System

# Getting Started
Follow this guide for setting up Docker, Docker-Compose and Docker-Sync.

## Installation
**Install this:**

**Docker**: 
https://docs.docker.com/install/

**Docker-Compose**: 
https://docs.docker.com/v17.09/compose/install/

**Docker-Sync**: 
https://docker-sync.readthedocs.io/en/latest/getting-started/installation.html

## Start Containers
```Bash
$ docker-sync-stack start # This will start the containers, including the sync
$ docker exec -it arinc_circle bash # This will 'go into' the container, allowing you to compile the dependencies + project :)
```

### Circle Setup (Only required first time)
```Bash
$ docker exec -it circle_arinc bash # This will 'go into' the container
$ ./makeall clean # Clean all dependencies
$ ./makeall # Compile all dependencies
$ cd boot/
$ make # Compile boot dependencies
```

Now you can compile all samples and drag all generated files from the sample and boot, in order to flash the SDHC Card

## Stop Containers
```Bash
# From circle/ root
$ docker-compose down # Closes the arinc_circle container
$ docker-sync stop # Closes the docker-sync container
```
