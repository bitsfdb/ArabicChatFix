#include "pch.h"
#include "UTF8_Persian_Arabic_Reshaper.h"
#include <vector>
#include <cstring>

const prGlyph prForms[] = {
    // Ascii Code, Code, Isolated, Initial, Medial, Final
    {193, "\u0621", "\uFE80", "\uFE80", "\uFE80", "\uFE80" },     //1 HAMZA ء    [*]
    {194, "\u0622", "\uFE81", "\uFE81", "\uFE82", "\uFE82" },     //2 ALEF_MADDA آ [*]
    {195, "\u0623", "\uFE83", "\uFE83", "\uFE84", "\uFE84" },     //3 ALEF_HAMZA_ABOVE أ [*]
    {196, "\u0624", "\uFE85", "\uFE85", "\uFE86", "\uFE86" },     //4 WAW_HAMZA ؤ [*]
    {197, "\u0625", "\uFE87", "\uFE87", "\uFE88", "\uFE88" },     //5 ALEF_HAMZA_BELOW إ [*]
    {198, "\u0626", "\uFE89", "\uFE8B", "\uFE8C", "\uFE8A" },     //6 YEH_HAMZA ئ [*]
    {199, "\u0627", "\uFE8D", "\uFE8D", "\uFE8E", "\uFE8E" },     //7 ALEF ا [*]
    {200, "\u0628", "\uFE8F", "\uFE91", "\uFE92", "\uFE90" },     //8 BEH ب
    {555, "\u0629", "\uFE93", "\uFE93", "\uFE94", "\uFE94" },     //9 TEH_MARBUTA ة [*]
    {202, "\u062A", "\uFE95", "\uFE97", "\uFE98", "\uFE96" },       //10 TEH ت
    {203, "\u062B", "\uFE99", "\uFE9B", "\uFE9C", "\uFE9A" },       //11 THEH ث
    {204, "\u062C", "\uFE9D", "\uFE9F", "\uFEA0", "\uFE9E" },       //12 JEEM ج
    {205, "\u062D", "\uFEA1", "\uFEA3", "\uFEA4", "\uFEA2" },       //13 HAH ح
    {206, "\u062E", "\uFEA5", "\uFEA7", "\uFEA8", "\uFEA6" },       //14 KHAH خ
    {207, "\u062F", "\uFEA9", "\uFEA9", "\uFEAA", "\uFEAA" },     //15 DAL د [*]
    {208, "\u0630", "\uFEAB", "\uFEAB", "\uFEAC", "\uFEAC" },     //16 THAL ذ [*]
    {209, "\u0631", "\uFEAD", "\uFEAD", "\uFEAE", "\uFEAE" },     //17 REH ر [*]
    {210, "\u0632", "\uFEAF", "\uFEAF", "\uFEB0", "\uFEB0" },     //18 ZAIN ز [*]
    {184, "\u0698", "\uFB8A", "\uFB8A", "\uFB8B", "\uFB8B" },     //19 ZHEH ژ [*]
    {211, "\u0633", "\uFEB1", "\uFEB3", "\uFEB4", "\uFEB2" },       //20 SEEN 
    {212, "\u0634", "\uFEB5", "\uFEB7", "\uFEB8", "\uFEB6" },       //21 SHEEN 
    {213, "\u0635", "\uFEB9", "\uFEBB", "\uFEBC", "\uFEBA" },       //22 SAD ص
    {214, "\u0636", "\uFEBD", "\uFEBF", "\uFEC0", "\uFEBE" },       //23 DAD ض
    {215, "\u0637", "\uFEC1", "\uFEC3", "\uFEC4", "\uFEC2" },       //24 TAH ط
    {216, "\u0638", "\uFEC5", "\uFEC7", "\uFEC8", "\uFEC6" },       //25 ZAH ظ
    {217, "\u0639", "\uFEC9", "\uFECB", "\uFECC", "\uFECA" },       //26 AIN ع
    {218, "\u063A", "\uFECD", "\uFECF", "\uFED0", "\uFECE" },       //27 GHAIN غ
    {160, "\u0640", "\u0640", "\u0640", "\u0640", "\u0640" },     //28 TATWEEL ـ
    {161, "\u0641", "\uFED1", "\uFED3", "\uFED4", "\uFED2" },       //29 FEH ف
    {162, "\u0642", "\uFED5", "\uFED7", "\uFED8", "\uFED6" },       //30 QAF ق
    {163, "\u0643", "\uFED9", "\uFEDB", "\uFEDC", "\uFEDA" },     //31 KAF Arabic ك
    {164, "\u0644", "\uFEDD", "\uFEDF", "\uFEE0", "\uFEDE" },       //32 LAM ل
    {165, "\u0645", "\uFEE1", "\uFEE3", "\uFEE4", "\uFEE2" },       //33 MEEM م
    {228, "\u0646", "\uFEE5", "\uFEE7", "\uFEE8", "\uFEE6" },       //34 NOON ن
    {167, "\u0647", "\uFEE9", "\uFEEB", "\uFEEC", "\uFEEA" },       //35 HEH ه
    {168, "\u0648", "\uFEED", "\uFEED", "\uFEEE", "\uFEEE" },     //36 WAW و [*]
    {169, "\u0649", "\uFEEF", "\uFEEF", "\uFEF0", "\uFEF0" },     //37 ALEF_MAKSURA [*]
    {170, "\u064A", "\uFEF1", "\uFEF3", "\uFEF4", "\uFEF2" },        //38 YEH Arabic ي 
    {172, "\u06CC", "\uFBFC", "\uFBFE", "\uFBFF", "\uFBFD" },       //39 YEH Farsi ی
    {141, "\u0686", "\uFB7A", "\uFB7C", "\uFB7D", "\uFB7B" },       //40 CHEH چ
    {222, "\u067E", "\uFB56", "\uFB58", "\uFB59", "\uFB57" },       //41 Peh پ
    {144, "\u06AF", "\uFB92", "\uFB94", "\uFB95", "\uFB93" },       //42 Gaf گ
    {201, "\u06A9", "\uFB8E", "\uFB90", "\uFB91", "\uFB8F" },        //43 Kaf ک
    {32, "\u0020", "\u0020", "\u0020", "\u0020", "\u0020" },      //44 Space
    {44, "\u060C", "\u060C", "\u060C", "\u060C", "\u060C" },      //45 Kama
    {20, "\u200C", "\u200C", "\u200C", "\u200C","\u200C" },       //46 half-space
    {58, "\u003A", "\u003A", "\u003A", "\u003A", "\u003A" },      //47 :
    {187, "\u061B", "\u061B", "\u061B", "\u061B", "\u061B" },     //48 ؛
    {46, "\u002E", "\u002E", "\u002E", "\u002E", "\u002E" },      //49 .
    {191, "\u061F", "\u061F", "\u061F", "\u061F", "\u061F" },     //50 ؟
    {48, "\u06F0", "\u06F0", "\u06F0", "\u06F0", "\u06F0" },      //51 0
    {49, "\u06F1", "\u06F1", "\u06F1", "\u06F1", "\u06F1" },      //52 1
    {50, "\u06F2", "\u06F2", "\u06F2", "\u06F2", "\u06F2" },      //53 2
    {51, "\u06F3", "\u06F3", "\u06F3", "\u06F3", "\u06F3" },      //54 3
    {52, "\u06F4", "\u06F4", "\u06F4", "\u06F4", "\u06F4" },      //55 4
    {53, "\u06F5", "\u06F5", "\u06F5", "\u06F5", "\u06F5" },      //56 5
    {54, "\u06F6", "\u06F6", "\u06F6", "\u06F6", "\u06F6" },      //57 6
    {55, "\u06F7", "\u06F7", "\u06F7", "\u06F7", "\u06F7" },      //58 7
    {56, "\u06F8", "\u06F8", "\u06F8", "\u06F8", "\u06F8" },      //59 8
    {57, "\u06F9", "\u06F9", "\u06F9", "\u06F9", "\u06F9" },      //60 9
    {41, "\u0028", "\u0028", "\u0028", "\u0028", "\u0028" },      //61 (  
    {40, "\u0029", "\u0029", "\u0029", "\u0029", "\u0029" }       //62 )
};

const int N_DISTINCT_CHARACTERS = 62;

UTF8_Persian_Arabic_Reshaper::UTF8_Persian_Arabic_Reshaper() {}

UTF8_Persian_Arabic_Reshaper::~UTF8_Persian_Arabic_Reshaper() {}

bool UTF8_Persian_Arabic_Reshaper::isFromTheSet1(unsigned char ch) {
    const unsigned char theSet1[18] = {
        32, '\0', 199, 194, 207, 208, 209, 210,
        184, 168, 191, 40, 41, 46, 33, 44, 58, 248 };
    for (int i = 0; i < 18; ++i) {
        if (ch == theSet1[i]) return true;
    }
    return false;
}

bool UTF8_Persian_Arabic_Reshaper::isFromTheSet2(unsigned char ch) {
    const unsigned char theSet2[10] = {
        32, '\0', 191, 40, 41, 46, 33, 44,
        58, 248 };
    for (int i = 0; i < 10; ++i) {
        if (ch == theSet2[i]) return true;
    }
    return false;
}

int UTF8_Persian_Arabic_Reshaper::FindGlyph(unsigned char chFind) {
    for (int i = 0; i < N_DISTINCT_CHARACTERS; i++) {
        if (prForms[i].AsciiCode == chFind) {
            return i;
        }
    }
    return -1;
}

std::string UTF8_Persian_Arabic_Reshaper::reshape(const std::string& inputText, bool reverse_string) {
    std::string prBuffer = "";
    int stat = 0;
    unsigned char pLetter = ' ';
    unsigned char letter;
    unsigned char nLetter;
    unsigned char temp;

    const char* Text = inputText.c_str();

    while ((temp = *Text++) != '\0') {
        if (temp >= '0' && temp <= '9') {
            letter = temp;
        }
        else if (temp >= 128) {
            letter = *Text++;
            letter += 32;
            temp += 32;
            if (letter == 207) {
                if (temp == 218 || temp == 250) {
                    letter = 144; //گ
                }
            }
            else if (letter == 166) {
                if (temp == 218 || temp == 250) { //چ
                    letter = 141;
                }
                else {
                    letter = 228; //ن
                }
            }
        }
        else {
            letter = temp;
        }

        if (letter == 172) {
            if (temp == 248 || temp == 32) {
                letter = 44;
            }
        }

        temp = *Text++;
        if (temp >= 128) {
            nLetter = *Text++;
            nLetter += 32;
            temp += 32;
            if (nLetter == 207) {
                if (temp == 218 || temp == 250) {
                    nLetter = 144; //گ
                }
            }
            else if (nLetter == 166) {
                if (temp == 218 || temp == 250) { //چ
                    nLetter = 141;
                }
                else {
                    nLetter = 228; //ن
                }
            }
            Text--; // Replaced invalid *Text--
            Text--;
        }
        else {
            nLetter = temp;
            Text--; // Replaced invalid *Text--
        }

        if (nLetter == 172) {
            if (temp == 248 || temp == 32) {
                nLetter = 44;
            }
        }

        int isunk = 0;

        if (isFromTheSet1(pLetter))
            if (isFromTheSet2(nLetter))
                stat = 0;  //Isolated
            else
                stat = 1;  //Initial
        else
            if (isFromTheSet2(nLetter))
                stat = 2;  //Final
            else
                stat = 3;  //Medial

        int number = FindGlyph(letter);

        if (number != -1) {
            switch (stat) {
            case 0: prBuffer += prForms[number].isoGlyph; break;
            case 1: prBuffer += prForms[number].iniGlyph; break;
            case 2: prBuffer += prForms[number].endGlyph; break;
            case 3: prBuffer += prForms[number].midGlyph; break;
            default: isunk = 1; break;
            }
        }
        else {
            isunk = 1;
            prBuffer += letter; // Fallback to raw char if not found
        }

        if (isunk == 0)
            pLetter = letter;
    }

    if (reverse_string && !prBuffer.empty()) {
        std::vector<char> writableBuf(prBuffer.begin(), prBuffer.end());
        writableBuf.push_back('\0');
        utf8rev(writableBuf.data());
        prBuffer = std::string(writableBuf.data());
    }

    return prBuffer;
}

void UTF8_Persian_Arabic_Reshaper::utf8rev(char* str) {
    char* scanl, * scanr, * scanr2, c;
    for (scanl = str, scanr = str + strlen(str); scanl < scanr;)
        c = *scanl, * scanl++ = *--scanr, *scanr = c;
    for (scanl = scanr = str; c = *scanr++;) {
        if ((c & 0x80) == 0)
            scanl = scanr;
        else if ((c & 0xc0) == 0xc0) {
            scanr2 = scanr;
            switch (scanr - scanl) {
            case 4: c = *scanl, *scanl++ = *--scanr, *scanr = c;
            case 3:
            case 2: c = *scanl, *scanl++ = *--scanr, *scanr = c;
            }
            scanr = scanl = scanr2;
        }
    }
}

int UTF8_Persian_Arabic_Reshaper::strlen_utf8(char* s) {
    int i = 0, j = 0;
    while (s[i]) {
        if ((s[i] & 0xc0) != 0x80) j++;
        i++;
    }
    return j;
}