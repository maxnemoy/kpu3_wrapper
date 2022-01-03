#include "menu_item.h"

MenuItem::MenuItem(String title, int itemId, bool isSelectableValue){
    name = title;
    id = itemId;
    isSelectable = isSelectableValue;
}
