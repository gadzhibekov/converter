#pragma once
#ifndef SETTINGS_WINDOW_ITEMS_H
#define SETTINGS_WINDOW_ITEMS_H

#include <QWidget>

#include "label.h"
#include "button.h"
#include "utils.h"

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
    explicit SettingsWindowItemUpdate(QWidget* parent);

private:
};

class SettingsWindowItemLicense : public QWidget
{
public:
    explicit SettingsWindowItemLicense(QWidget* parent);

private:
};

#endif // SETTINGS_WINDOW_ITEMS_H