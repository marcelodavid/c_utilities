#ifndef __TIMEOUT__
#define __TIMEOUT__
#include <Arduino.h>
/* Timeout permite definir un tiempo a vencer
 * con la posibilid de reiniciar y detener el cronometro
 */
class Timeout
{
    public:
        Timeout(const unsigned long);
        bool isTimeout();
        void stop();
        void start();
        void reset();

    private:
        bool running;
        const unsigned long MILLISECONDS;
        unsigned long startTime;
        unsigned long elapsed_time;

        unsigned long elapsed();
};
#endif
