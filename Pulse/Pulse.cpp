#include <Pulse.h>

Pulse::Pulse(uint8_t pin, Timeout& pulseWidth):outputPin(pin), timer(pulseWidth), retries(1), isActiveLow(true){}

void Pulse::begin(){
    pinMode(outputPin, OUTPUT);
    setActiveLow();
}

void Pulse::setActiveLow(){
    isActiveLow = true;
    digitalWrite(outputPin, HIGH);
}

void Pulse::setActiveHigh(){
    isActiveLow = false;
    digitalWrite(outputPin, LOW);
}

void Pulse::setRetries(uint8_t times){
    retries = times;
}

void Pulse::changeState(){
    if(isActiveLow){
        setActiveHigh();
    } else {
        setActiveLow();
    }
}

bool Pulse::make(){
    /*
     * Esta funcion genera un pulso
     * cuyo periodo activo es igual a el
     * timer, retorna verdadero al culminar el pulso 
     */

    static uint8_t state = 1;
    if(state == 1){ // inicia el pulso con un cambio de su estado
        changeState();
        state = 2;
    }
    if(state == 2){
        timer.start();
        if(timer.isTimeout()){
            state = 3;  // cambia a su estado original
            timer.reset();
        }
    }
    if(state == 3){
        changeState();
        state = 1;
        return true;    // fin del pulso
    }
    return false;
}

bool Pulse::write(){
    /*
     * Genera la cantidad de pulsos
     * que se requieren de acuerdo
     * al valor que desee el cliente
     * por defecto genera un solo pulso
     */
    
    static uint8_t number_of_pulses = 0;
    static int enable = true;

    // makes pulses
    if(enable && make()){
        ++number_of_pulses;
        enable = false;
    }

    if(!enable){    // esperamos un tiempo igual para volver a habilitar el pulso
        timer.start();
        if(timer.isTimeout()){
            enable = true;
        }
    }

    if(number_of_pulses == retries){
        number_of_pulses = 0;
        enable = true;
        return true;
    }
    return false;
}


