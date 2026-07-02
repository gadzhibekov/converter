#pragma once
#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QWidget>

#include "button.h"
#include "settings_window_items.h"
#include "net.h"

class SettingsWindow;
class SettingsWindowPanel;

class SettingsWindow : public QWidget
{
public:
    explicit SettingsWindow(Net& net);
    friend class SettingsWindowPanel;

private:
    void Back();

private:
    Button*                         back;
    SettingsWindowPanel*            panel;
    SettingsWindowItemInformation*  swii;
    SettingsWindowItemUpdate*       swiu;
    SettingsWindowItemLicense*      swil;
    Net&                            net;
};

class SettingsWindowPanel : public QWidget
{
public:
    explicit SettingsWindowPanel(QWidget* parent);

private:
    void    ShowInformationItem();
    void    ShowUpdateItem();
    void    ShowLicenseItem();

private:
    Button*         informationButton;
    Button*         updateButton;
    Button*         licenseButton;
    SettingsWindow* settingsWindow;
};

#endif // SETTINGS_WINDOW_H