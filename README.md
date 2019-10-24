# FreeTACOS [![CircleCI](https://circleci.com/gh/CTxD/FreeTACOS/tree/master.svg?style=svg)](https://circleci.com/gh/CTxD/FreeTACOS/tree/master)

Free Transparent Arinc Compliant Operating System

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
$ make start # This will start the containers, including the sync (let this run in a terminal by itself - you can not terminate)
$ make enter # This will 'go into' the container, allowing you to compile the dependencies + project :)
```

### Circle Setup (Only required first time)
#### Use Make
```Bash
$ make build-boot # Build boot files
$ make enter # Enter docker container
$ cd aarch/rasp4 # Navigate to circle library
$ ./makeall clean # Clear dependencies
$ ./makeall # Compile dependencies - This must be done within the container
```

Done.

## Stop Containers
```Bash
# From circle/ root
$ docker-compose down # Closes the arinc_circle container
$ docker-sync stop # Closes the docker-sync container
```
OR
Interrupt CTRL+C the running docker-sync process
