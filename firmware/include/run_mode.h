#ifndef _BUTTON_H
#define _BUTTON_H

#include "kpu_data.h"

class RunMode{
    public:
        RunMode(KpuData *kpuData);
        
    private:
        KpuData *data;
};

RunMode::RunMode(KpuData *kpuData){
    data = kpuData;
}

#endif