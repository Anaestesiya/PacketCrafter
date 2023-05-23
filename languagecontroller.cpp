#include "languagecontroller.h"
#include "qapplication.h"

LanguageController::LanguageController()
{

}

LanguageController::Elanguage LanguageController::currentLanguage = EN;
QTranslator *LanguageController::translator = new QTranslator();

void LanguageController::changeToEN()
{
    translator->load("PacketCrafter_en_US");
    qApp->installTranslator(translator);
}

void LanguageController::changeToUA()
{
    translator->load("PacketCrafter_uk_UA");
    qApp->installTranslator(translator);
}


