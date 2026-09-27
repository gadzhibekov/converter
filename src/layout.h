#pragma once
#ifndef LAYOUT_H
#define LAYOUT_H

#include <QString>
#include <vector>
#include <utility>

extern QString                                  currentLayout;
extern std::vector<std::pair<QString, void *>>  layoutObjPtrs;
extern std::vector<QString>                     lezgiLanguagePackDynamic;
extern std::vector<QString>                     russianLanguagePackDynamic;
extern std::vector<QString>                     englishLanguagePackDynamic;
extern std::vector<QString>                     lezgiLanguagePack;
extern std::vector<QString>                     russianLanguagePack;
extern std::vector<QString>                     englishLanguagePack;

std::vector<QString>                            GetCurrentLayout();
void                                            Translate2Lezgi();
void                                            Translate2Russian();
void                                            Translate2English();

#endif // LAYOUT_H