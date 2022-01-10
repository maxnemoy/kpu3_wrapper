#ifndef _MENU_H
#define _MENU_H

#include <Arduino.h>
#include "menu_item.h"
#include "sensor.h"

class Menu{
    public:
        Menu(std::vector<MenuItem *> menuItems, Sensor *sensor);
        void next();
        void previous();
        void select();
        void unSelect();
        //TODO: impl hold/reset button
        // void hold();
        // void release();
        void reset();
        std::vector<String> getMenu();
        int index();
        void setValue(int id, float value);
        void setValue(int id, bool value);
        void updateData();
        float getFloatValue(int id);
        bool getBoolValue(int id);
    private:
        int selectedItem = -1;
        int item = 0;
        std::vector<MenuItem *> items;
        Sensor* sensor;
};

#endif