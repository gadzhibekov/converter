#pragma once
#ifndef THEME_H
#define THEME_H

#include <vector>
#include <string>
#include <utility>

extern std::vector<std::pair<std::string, void *>>   objPtrs;
void                                                 Switch2LightTheme();
void                                                 Switch2DarkTheme();

#endif // THEME_H