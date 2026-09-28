#pragma once
#ifndef SETTINGS_WINDOW_ITEMS_H
#define SETTINGS_WINDOW_ITEMS_H

#include <QWidget>
#include <QRadioButton>

#include "label.h"
#include "button.h"

class SettingsWindowItemInformation : public QWidget
{
public:
    explicit        SettingsWindowItemInformation(QWidget* parent);

private:
    void            CopyCommand();

private:
    Label*          title;
    Label*          information;
    Button*         copyCommandButton;
};

class SettingsWindowItemUpdate : public QWidget
{
public:
                    SettingsWindowItemUpdate(QWidget* parent);

private:
    void            Update();

private:
    QWidget*        updateInformation;
    Label*          updateIcon;
    Label*          currentVersion;
    Label*          aboutCurrentVersion;
    Button*         update;
};

class SettingsWindowItemLicense : public QWidget
{
public:
    explicit        SettingsWindowItemLicense(QWidget* parent);

private:
    QWidget*        pandocLicense;
    QWidget*        converterLicense;
    Label*          pandocLicenseTitle;
    Label*          pandocLicenseIcon;
    Label*          converterLicenseTitle;
    Label*          converterLicenseIcon;
    Label*          pandocLicenseInformation;
    Label*          converterLicenseInformation;
};

class SettingsWindowItemTheme : public QWidget
{
public:
    explicit        SettingsWindowItemTheme(QWidget* parent);

private:
    void            LightTheme();
    void            DarkTheme();

private:
    QWidget*        lightThemePhone;
    QWidget*        darkThemePhone;
    QRadioButton*   lightThemeRadioButton;
    QRadioButton*   darkThemeRadioButton;
    Label*          lightThemeTitle;
    Label*          darkThemeTitle;
    Label*          information;
};

#endif // SETTINGS_WINDOW_ITEMS_H