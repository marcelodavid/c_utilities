#include <stripeCardReader.h>

String trackHolder = "";
bool has_been_read = false;

void KbdRptParser::PrintKey(uint8_t m, uint8_t key){
    MODIFIERKEYS mod;
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key){
    PrintKey(mod, key);
    uint8_t c = OemToAscii(mod, key);

    if (c)
        OnKeyPressed(c);
}

void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

    MODIFIERKEYS beforeMod;
    *((uint8_t*)&beforeMod) = before;

    MODIFIERKEYS afterMod;
    *((uint8_t*)&afterMod) = after;
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key){
    PrintKey(mod, key);
}

void KbdRptParser::OnKeyPressed(uint8_t key){
    if ((char)key != '?') {
        trackHolder.concat((char)key);
    }
    else {
        trackHolder.concat("?");
        has_been_read = true;
    }
};

USB     Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

StripeCardReader::StripeCardReader() { }

bool StripeCardReader::begin(){
    if(Usb.Init() == -1)
        return false;

    HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);
    return true;
}

bool StripeCardReader::is_there_a_track(){
    Usb.Task();
    return has_been_read;
}

char* StripeCardReader::getTrack(){
    setTrack(trackHolder);
    return track;
}

void StripeCardReader::setTrack(String& trackHolder) {
    trackHolder.toCharArray(track, 30);
    trackHolder = "";
}

void StripeCardReader::reset(){
    has_been_read = false;
}
