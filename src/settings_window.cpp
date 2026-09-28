#include "settings_window.h"
#include "utils.h"
#include "theme.h"
#include "layout.h"

SettingsWindow::SettingsWindow()
{   
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(1000, 500);

    objPtrs.push_back({"Widget", this});
    layoutObjPtrs.push_back({"Widget", this});

    swii    = new SettingsWindowItemInformation(this);
    swiu    = new SettingsWindowItemUpdate(this);
    swil    = new SettingsWindowItemLicense(this);
    swit    = new SettingsWindowItemTheme(this);
    panel   = new SettingsWindowPanel(this);
    back    = new Button(this, [this](){Back();});

    back->SetGeometry(5, 5, 35, 35);
    back->SetIcon("../res/back.png");
    back->SetIconSize(35, 35);

    objPtrs.push_back({"Button2", back});

    swii->show();
    swiu->hide();
    swil->hide();
    swit->hide();
    this->hide();
}

void SettingsWindow::Back()
{
    this->hide();
}

SettingsWindowPanel::SettingsWindowPanel(QWidget* parent) : QWidget(parent), settingsWindow(dynamic_cast<SettingsWindow*>(parent))
{
    this->setGeometry(415, 445, 170, 44);

    objPtrs.push_back({"Panel", this});

    informationButton   = new Button(this, [this](){ShowInformationItem();});
    updateButton        = new Button(this, [this](){ShowUpdateItem();});
    licenseButton       = new Button(this, [this](){ShowLicenseItem();});
    themeButton         = new Button(this, [this](){ShowThemeItem();});

    informationButton->SetIcon("../res/information.png");
    updateButton->SetIcon("../res/update.png");
    licenseButton->SetIcon("../res/mit.png");
    themeButton->SetIcon("../res/theme.png");

    informationButton->SetIconSize(40, 40);
    updateButton->SetIconSize(40, 40);
    licenseButton->SetIconSize(40, 40);
    themeButton->SetIconSize(40, 40);

    informationButton->SetGeometry(2, 2, 40, 40);
    updateButton->SetGeometry(44, 2, 40, 40);
    licenseButton->SetGeometry(86, 2, 40, 40);
    themeButton->SetGeometry(86 + 42, 2, 40, 40);

    objPtrs.push_back({"PanelItem", informationButton});
    objPtrs.push_back({"PanelItem", updateButton});
    objPtrs.push_back({"PanelItem", licenseButton});
    objPtrs.push_back({"PanelItem", themeButton});
}

void SettingsWindowPanel::ShowInformationItem()
{
    settingsWindow->swii->show();
    settingsWindow->swiu->hide();
    settingsWindow->swil->hide();
    settingsWindow->swit->hide();
}

void SettingsWindowPanel::ShowUpdateItem()
{
    settingsWindow->swii->hide();
    settingsWindow->swiu->show();
    settingsWindow->swil->hide();
    settingsWindow->swit->hide();
}

void SettingsWindowPanel::ShowLicenseItem()
{
    settingsWindow->swii->hide();
    settingsWindow->swiu->hide();
    settingsWindow->swil->show();
    settingsWindow->swit->hide();
}

void SettingsWindowPanel::ShowThemeItem()
{
    settingsWindow->swii->hide();
    settingsWindow->swiu->hide();
    settingsWindow->swil->hide();
    settingsWindow->swit->show();
}