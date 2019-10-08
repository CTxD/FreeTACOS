#include "../include/arch.h"
#include "../include/bsp.h"

void freeTACOS()
{
    freeTACOS_arch_init();
    freeTACOS_bsp_init();

    main();
}