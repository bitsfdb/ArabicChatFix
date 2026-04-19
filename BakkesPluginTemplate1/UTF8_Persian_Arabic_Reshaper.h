#pragma once
#include <string>

class UTF8_Persian_Arabic_Reshaper
{
public:
    UTF8_Persian_Arabic_Reshaper();
    virtual ~UTF8_Persian_Arabic_Reshaper();

    std::string reshape(const std::string& text, bool reverse_string = true);
    void utf8rev(char* str);
    int strlen_utf8(char* s);

private:
    int FindGlyph(unsigned char chFind);
    bool isFromTheSet1(unsigned char ch);
    bool isFromTheSet2(unsigned char ch);
};

struct prGlyph {
    int AsciiCode;
    const char* codeGlyph;
    const char* isoGlyph;
    const char* iniGlyph;
    const char* midGlyph;
    const char* endGlyph;
};