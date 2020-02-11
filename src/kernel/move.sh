#!/bin/bash

if [ -d /run/media/teitur/boot/ ]

then

    sudo rm /run/media/teitur/boot/kernel8-rpi4.elf

    sudo rm /run/media/teitur/boot/kernel8-rpi4.img

    sudo rm /run/media/teitur/boot/kernel8-rpi4.lst

    sudo rm /run/media/teitur/boot/kernel8-rpi4.map

    sudo cp -v /home/teitur/Repositories/FreeTACOS/src/kernel/kernel8-rpi4.elf /run/media/teitur/boot/

    sudo cp -v /home/teitur/Repositories/FreeTACOS/src/kernel/kernel8-rpi4.img /run/media/teitur/boot/

    sudo cp -v /home/teitur/Repositories/FreeTACOS/src/kernel/kernel8-rpi4.lst /run/media/teitur/boot/

    sudo cp -v /home/teitur/Repositories/FreeTACOS/src/kernel/kernel8-rpi4.map /run/media/teitur/boot/

    echo "Sync"

    sync

    echo "Ready to test"

else

    echo "Mounting boot!"

fi

