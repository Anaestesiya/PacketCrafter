#ifndef LANGUAGECONTROLLER_H
#define LANGUAGECONTROLLER_H

#include <QTranslator>




class LanguageController
{
public:
    LanguageController();
    static void changeToUA();
    static void changeToEN();

    enum Elanguage
    {
        UA,
        EN
    };

    static Elanguage currentLanguage;
private:
    static QTranslator *translator;
};

#endif // LANGUAGECONTROLLER_H
