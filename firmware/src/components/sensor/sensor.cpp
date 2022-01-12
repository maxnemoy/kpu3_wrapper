// подключение необходимых заголовочных файлов
#include "sensor.h"
// Определение конструктора
Sensor::Sensor(int data_pin, int sck_pin){
    _sensor.begin(data_pin, sck_pin, 64u);
    _sensor.set_scale(_scaleFactor);
}
// определение функции возврата значения
// давления в паскалях 
float Sensor::getPsi(){
    return _sensor.get_units(_step);
}
// определение функции возврата среднего
// значения согласно шага в мм/рс
float Sensor::getMillimetersOfMercury(){
    return (_sensor.get_units(_step) / PSI_IN_MOM);
}
// определение функции изменения шага 
void Sensor::setStepSize(int step){
    _step = step;
};
// определение функции установки делителя
// для пересчета значениня возвращаемего сенсором
void Sensor::setScaleFactor(float scale){
    _scaleFactor = scale;
    _sensor.set_scale(_scaleFactor);
};