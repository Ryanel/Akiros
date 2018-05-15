#include <x86/textmode.hpp>
#include <stdint.h>

#include <string.h>
#include <x86/ports.hpp>

using namespace x86;

TextMode x86::textModeBase;

void TextMode::PutChar(char c, char attribute, int x, int y) {
    int location = ((y * width) + x) * 2;
    buffer[location] = c;
    buffer[location + 1] = attribute;
}

void TextMode::UpdateHardwareCursor() {
    uint16_t location = (y * width) + (uint16_t)x;
	outb(0x3D4, 14);
	outb(0x3D5, location >> 8);
	outb(0x3D4, 15);
    outb(0x3D5, location);
}

void TextMode::Print(char c) {
    switch(c) {
    case '\n':
        NewLine();
        break;
    default:
        PutChar(c, currentAttribute, x, y);
        SetCursor(x + 1, y);
        break;
    }
}

void TextMode::Clear() {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            PutChar(0, currentAttribute, x, y);
        }
    }
    x = 0;
    y = 0;
}

void TextMode::SetCursor(int x, int y) {
    bool doScroll = false;
    
    if(x > width) {
        y++;
        x -= width;
    }
    else if(x < 0) {
        x = 0;
    }
    
    if (y > height - 1) {
        doScroll = true;
        y = height - 1; 
    }
    else if (y < 0) {
        y = 0;
    }
    
    this->x = x;
    this->y = y;

    if(doScroll) {
        Scroll();
    }

    UpdateHardwareCursor();
}

void TextMode::Scroll() {
    const int size = width * height * 2;
    uint8_t tempBuffer[size];

    memcpy(&tempBuffer, (void*)(baseAddr + (width * 2)),  size);
    memcpy((void*)baseAddr, &tempBuffer, size);
    memset((void*)(baseAddr + size), 0, width * 2);
}

int TextMode::GetWidth() {
    return 80;
}

int TextMode::GetHeight() {
    return 25;
}

void TextMode::SetColor(char color) {
    currentAttribute = color;
}

void TextMode::NewLine() {
    SetCursor(0, y + 1);
}

void TextMode::Backspace() {
    SetCursor(x - 1, y);
    PutChar(0, currentAttribute, x, y);
}

void TextMode::CarriageReturn() {
    SetCursor(0, y);
}