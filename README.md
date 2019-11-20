# FreeTACOS

Free Transparent Arinc Compliant Operating System

## Documentation

Doxygen Documentation

### Generation

To generate the documentation:

```Bash
$ docker exec -it tacos_doxygen bash # Enter the Doxygen container
$ doxygen .doxygen # Generate documentation
```

### OR

**Run Docker and:**

```Bash
make docs
```

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
$ cd aarch/circle-stdlib # Navigate to circle library
$ git submodule update --init --recursive
$ cd ./aarch/circle-stdlib
$ ./configure -p aarch64-elf- -r 4
$ make
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
