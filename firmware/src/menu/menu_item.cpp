// подключение необходимых заголовочных файлов
#include "menu_item.h"

// определение конструктора абстрактного класса пункта меню
MenuItem::MenuItem(String title, int itemId, bool isSelectableValue){
    name = title;
    id = itemId;
    isSelectable = isSelectableValue;
}
