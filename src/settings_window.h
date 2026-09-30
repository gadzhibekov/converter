#pragma once
#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QWidget>

#include "button.h"
#include "settings_window_items.h"

class SettingsWindow;
class SettingsWindowPanel;
class SettingsWindowItemInformation;
class SettingsWindowItemUpdate;
class SettingsWindowItemLicense;
class SettingsWindowItemTheme;
class SettingsWindowItemLayout;

class SettingsWindow : public QWidget
{
public:
    SettingsWindow();
    friend class SettingsWindowPanel;

private:
    void Back();

private:
    Button*                         back;
    SettingsWindowPanel*            panel;
    SettingsWindowItemInformation*  swii;
    SettingsWindowItemUpdate*       swiu;
    SettingsWindowItemLicense*      swil;
    SettingsWindowItemTheme*        swit;
    SettingsWindowItemLayout*       swilt;
};

class SettingsWindowPanel : public QWidget
{
public:
    explicit SettingsWindowPanel(QWidget* parent);

private:
    void                            ShowInformationItem();
    void                            ShowUpdateItem();
    void                            ShowLicenseItem();
    void                            ShowThemeItem();
    void                            ShowLayoutItem();

private:
    Button*                         informationButton;
    Button*                         updateButton;
    Button*                         licenseButton;
    Button*                         themeButton;
    Button*                         layoutButton;
    SettingsWindow*                 settingsWindow;
};

#endif // SETTINGS_WINDOW_H