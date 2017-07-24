#ifndef __STRIPECARDREADER__
    #define __STRIPECARDREADER__
    #include <Arduino.h>
    #include <hidboot.h>
    #include <usbhub.h>
    
    class KbdRptParser : public KeyboardReportParser{
        void PrintKey(uint8_t mod, uint8_t key);

        protected:
            void OnControlKeysChanged(uint8_t before, uint8_t after);

            void OnKeyDown  (uint8_t mod, uint8_t key);
            void OnKeyUp  (uint8_t mod, uint8_t key);
            void OnKeyPressed(uint8_t key);
    };

    class StripeCardReader {
        public:
            StripeCardReader();
            bool begin();
            bool is_there_a_track();
            char* getTrack();
            void reset();
            void setTrack(String&);

        private:
            char track[30];
    };
#endif
