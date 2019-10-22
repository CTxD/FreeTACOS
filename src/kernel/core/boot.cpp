#include <arch.h>
#include <errcode.h>
// int main()
// {
//     /* code */
//     return 0;
// }

ret_t boot(){
    return init_arch();
}

// void freeTACOS()
// {
//     freeTACOS_arch_init();
//     freeTACOS_bsp_init();

//     main();
// }

