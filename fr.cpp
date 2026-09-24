#include "ev3dev-lang-cpp/ev3dev.h"
#include <iostream>
#include <unistd.h>

int main()
{
    ev3dev::large_motor left(ev3dev::OUTPUT_C);   // левый
    ev3dev::large_motor right(ev3dev::OUTPUT_B);  // правый

    ev3dev::ultrasonic_sensor us_left(ev3dev::INPUT_2);    // левый
    ev3dev::ultrasonic_sensor us_center(ev3dev::INPUT_3);  // центральный
    ev3dev::ultrasonic_sensor us_right(ev3dev::INPUT_4);   // правый

    int base_speed = 500;

    // инициализация хранящих переменных
    int dist_left;
    int dist_center;
    int dist_right;

    int speed_left;
    int speed_right;

    while (true)
    {
        dist_left   = us_left.distance_centimeters();
        dist_center = us_center.distance_centimeters();
        dist_right  = us_right.distance_centimeters();

        // По умолчанию едем прямо
        speed_left  = base_speed;
        speed_right = base_speed;

        // алгоритм строгого неравенства
        if (dist_left > dist_center || dist_right > dist_center)
        {
            // алгоритм сравнения
            if (dist_left > dist_right)
            {
                speed_left  = base_speed - 200;
                speed_right = base_speed + 200;
            }
            else
            {
                speed_left  = base_speed + 200;
                speed_right = base_speed - 200;
            }
        }

        // Задаём скорости моторам
        left.set_speed_sp(speed_left);
        right.set_speed_sp(speed_right);
        left.run_forever();
        right.run_forever();

        usleep(100000); // 0.1 секунды
    }

    return 0;
}
