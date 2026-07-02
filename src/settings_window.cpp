#include "settings_window.h"
#include "utils.h"

SettingsWindow::SettingsWindow(Net& net) : net(net)
{   
    this->setFixedSize(1000, 500);
    this->setWindowTitle("Settings");
    this->setStyleSheet(ReadAllFile("../styles/widget.css"));

    swii    = new SettingsWindowItemInformation(this);
    swiu    = new SettingsWindowItemUpdate(this, net);
    swil    = new SettingsWindowItemLicense(this);
    panel   = new SettingsWindowPanel(this);
    back    = new Button(this, [this](){Back();});

    back->SetGeometry(5, 5, 35, 35);
    back->SetIcon("../res/back.png");
    back->SetIconSize(35, 35);

    back->setStyleSheet(ReadAllFile("../styles/button.css"));

    swii->show();
    swiu->hide();
    swil->hide();
    this->hide();
}

void SettingsWindow::Back()
{
    this->hide();
}

SettingsWindowPanel::SettingsWindowPanel(QWidget* parent) : QWidget(parent), settingsWindow(dynamic_cast<SettingsWindow*>(parent))
{
    this->setGeometry(436, 450, 128, 44);
    this->setStyleSheet("background-color: red;");
    this->setStyleSheet(ReadAllFile("../styles/panel.css"));

    informationButton   = new Button(this, [this](){ShowInformationItem();});
    updateButton        = new Button(this, [this](){ShowUpdateItem();});
    licenseButton       = new Button(this, [this](){ShowLicenseItem();});

    informationButton->SetIcon("../res/information.png");
    updateButton->SetIcon("../res/update.png");
    licenseButton->SetIcon("../res/mit.png");

    informationButton->SetIconSize(40, 40);
    updateButton->SetIconSize(40, 40);
    licenseButton->SetIconSize(40, 40);

    informationButton->SetGeometry(2, 2, 40, 40);
    updateButton->SetGeometry(44, 2, 40, 40);
    licenseButton->SetGeometry(86, 2, 40, 40);

    informationButton->setStyleSheet(ReadAllFile("../styles/panel_item.css"));
    updateButton->setStyleSheet(ReadAllFile("../styles/panel_item.css"));
    licenseButton->setStyleSheet(ReadAllFile("../styles/panel_item.css"));
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