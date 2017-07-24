#include "Timeout.h"

Timeout::Timeout(const unsigned long milliseconds): MILLISECONDS(milliseconds), elapsed_time(0), startTime(0) {}

void Timeout::start(){
    if(!running){
        running = true;
        startTime = millis();
    }
}

void Timeout::stop(){
    if(running){
        unsigned long stopTime = millis();
        running = false;

        // guardamos el tiempo transcurrido desde el inicio
        elapsed_time += stopTime - startTime;
    }
}

void Timeout::reset(){
    running = false;
    elapsed_time = 0;
}

unsigned long Timeout::elapsed(){
    if(running){
        unsigned long currentTime = millis();

        return elapsed_time + currentTime - startTime;
    }
    else
        return elapsed_time;
}

bool Timeout::isTimeout() {
    return elapsed() >= MILLISECONDS;
}
