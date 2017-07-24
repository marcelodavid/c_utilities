#ifndef __PULSE__
    #define __PULSE__
    #include <Arduino.h>
    #include <Timeout.h>
    
    /*! \class Pulse
     *  \brief Brief class description
     *
     *  Suministra un pulso o tren de pulsos
     *  sobre un pin definido como salida
     *
     *  el ancho del pulso depende del Timeout
     *  El pulso es activo en Low por defecto pudiendose
     *  cambiar esta propiedad
     *
     *  tambien puede configuranse el numero de pulso que
     *  se generara en la salida
     */
    class Pulse{
        public:
            Pulse(uint8_t, Timeout&);
            void begin();
            void setActiveHigh();
            void setActiveLow();
            void setRetries(uint8_t);
            bool write();

        private:
            uint8_t outputPin;
            Timeout& timer;
            uint8_t retries;
            bool isActiveLow;
            bool make();
            void changeState();
    };
#endif
