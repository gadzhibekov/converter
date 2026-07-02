#pragma once
#ifndef SETTINGS_WINDOW_ITEMS_H
#define SETTINGS_WINDOW_ITEMS_H

#include <QWidget>

#include "label.h"
#include "button.h"
#include "net.h"

class SettingsWindowItemInformation : public QWidget
{
public:
    explicit SettingsWindowItemInformation(QWidget* parent);

private:
    void CopyCommand();

private:
    Label*  title;
    Label*  information;
    Button* copyCommandButton;
};

class SettingsWindowItemUpdate : public QWidget
{
public:
    SettingsWindowItemUpdate(QWidget* parent, Net& net);

private:
    void Update();

private:
    QWidget*    updateInformation;
    Label*      updateIcon;
    Label*      currentVersion;
    Label*      aboutCurrentVersion;
    Button*     update;
    Net&        net;
};

class SettingsWindowItemLicense : public QWidget
{
public:
    explicit SettingsWindowItemLicense(QWidget* parent);

private:
    QWidget*    pandocLicense;
    QWidget*    converterLicense;
    Label*      pandocLicenseTitle;
    Label*      pandocLicenseIcon;
    Label*      converterLicenseTitle;
    Label*      converterLicenseIcon;
    Label*      pandocLicenseInformation;
    Label*      converterLicenseInformation;
};

#endif // SETTINGS_WINDOW_ITEMS_H