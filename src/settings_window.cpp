#include "settings_window.h"

SettingsWindow::SettingsWindow()
{   
    this->setFixedSize(1000, 500);
    this->setWindowTitle("Настройки");

    swii    = new SettingsWindowItemInformation(this);
    swiu    = new SettingsWindowItemUpdate(this);
    swil    = new SettingsWindowItemLicense(this);
    panel   = new SettingsWindowPanel(this);

    swii->show();
    swiu->hide();
    swil->hide();
    this->hide();
}

SettingsWindowPanel::SettingsWindowPanel(QWidget* parent) : QWidget(parent), settingsWindow(dynamic_cast<SettingsWindow*>(parent))
{
    this->setGeometry(436, 450, 128, 44);
    this->setStyleSheet("background-color: red;");

    informationButton   = new Button(this, [this](){ShowInformationItem();});
    updateButton        = new Button(this, [this](){ShowUpdateItem();});
    licenseButton       = new Button(this, [this](){ShowLicenseItem();});

    informationButton->SetText("I");
    updateButton->SetText("U");
    licenseButton->SetText("L");

    informationButton->SetGeometry(2, 2, 40, 40);
    updateButton->SetGeometry(44, 2, 40, 40);
    licenseButton->SetGeometry(86, 2, 40, 40);
}

void SettingsWindowPanel::ShowInformationItem()
{
    settingsWindow->swii->show();
    settingsWindow->swiu->hide();
    settingsWindow->swil->hide();
}

void SettingsWindowPanel::ShowUpdateItem()
{
    settingsWindow->swii->hide();
    settingsWindow->swiu->show();
    settingsWindow->swil->hide();
}

void SettingsWindowPanel::ShowLicenseItem()
{
    settingsWindow->swii->hide();
    settingsWindow->swiu->hide();
    settingsWindow->swil->show();
}