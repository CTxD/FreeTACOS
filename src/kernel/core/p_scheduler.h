//
// Created by teamt on 06/11/2019.
//

#ifndef FREETACOS_P_SCHEDULER_H
#define FREETACOS_P_SCHEDULER_H


class p_scheduler {

    void FIND_NEXT() {
        int high = 0;
        int current = 0
        for (int i = 0; i < PROCESS_AMOUNT; i++) {
            current = process_list[i].GET_PRIORITY();
            if(current > high){
                high = current;
            }
        }
    }
};

#endif //FREETACOS_P_SCHEDULER_H
