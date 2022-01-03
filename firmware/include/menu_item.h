#ifndef _MENU_ITEM_H
#define _MENU_ITEM_H

#include "Arduino.h"

#define IS_RUN_ITEM 1
#define PSI_VALUE_ITEM 1
#define MMoM_VALUE_ITEM 2
#define IS_VACUUM_ITEM 3
#define C_LIMIT_ITEM 4
#define V_LIMIT_ITEM 5
#define SCALE_ITEM 6

class MenuItem{
    public:
        MenuItem(String title, int id, bool isSelectable = true);
        String name;
        bool isSelectable;
        int id;
        virtual String printValue() = 0;
        virtual void add() = 0;
        virtual void remove() = 0;
        virtual void reset() = 0;
        virtual void setValue(bool value) = 0;
        virtual void setValue(float value) = 0;
        virtual bool getValueBool() = 0;
        virtual float getValueFloat() = 0;
};

class BoolMenuItem : public MenuItem{
    public:
        BoolMenuItem(String title, int id, bool defaultValue = false, bool isSelectable = true);
        String printValue();
        void add();
        void remove();
        void reset();
        void setValue(bool value);
        void setValue(float value){};
        bool getValueBool();
        float getValueFloat(){return 0.0f;};

    private: 
        bool _value;
        bool _defaultValue;
};

class FloatMenuItem : public MenuItem{
    public:
        FloatMenuItem(String title, int id, float defaultValue = 1.0, float step = 0.5, bool isSelectable = true);
        String printValue();
        void add();
        void remove();
        void reset();
        void setValue(float value);
        void setValue(bool value){};
        bool getValueBool(){return false;};
        float getValueFloat();
    private: 
        float _value;
        float _defaultValue;
        float _step;
};

#endif