#include "settings_window_items.h"
#include "utils.h"
#include "theme.h"
#include "message_box.h"
#include "layout.h"

#include <QMessageBox>
#include <QProcess>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QPixmap>

SettingsWindowItemInformation::SettingsWindowItemInformation(QWidget* parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 1000, 500);

    title               = new Label(this);
    information         = new Label(this);

    layoutObjPtrs.push_back({"Label", title});
    layoutObjPtrs.push_back({"Label", information});

    title->SetTextToCenter();
    information->SetTextToCenter();

    title->SetGeometry(0, 60, 1000, 50);
    information->SetGeometry(0, 120, 1000, 200);

    title->SetTextSize(30);
    information->SetTextSize(13);

    objPtrs.push_back({"Label", title});
    objPtrs.push_back({"Label", information});

    copyCommandButton   = new Button(this, [this](){CopyCommand();});
    copyCommandButton->setGeometry(400, 330, 200, 50);

    objPtrs.push_back({"Button", copyCommandButton});
    layoutObjPtrs.push_back({"Button", copyCommandButton});
}

void SettingsWindowItemInformation::CopyCommand()
{
    ToClipboard("sudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y");

    MessageBox::Message(DONE_ICON, GetCurrentLayout()[5]);
}


SettingsWindowItemUpdate::SettingsWindowItemUpdate(QWidget* parent) : QWidget(parent)
{
    updateInformation           = new QWidget(this);
    updateInformation->setGeometry(45, 75, 910, 200);

    updateIcon                  = new Label(updateInformation);
    updateIcon->SetGeometry(430, 5, 50, 50);
    updateIcon->SetIcon("../res/update.png");

    currentVersion              = new Label(updateInformation);
    currentVersion->SetText(ConvertToDecimal(version));
    currentVersion->SetTextSize(22);
    currentVersion->SetTextToCenter();
    currentVersion->SetGeometry(0, 55, 910, 50);

    aboutCurrentVersion         = new Label(updateInformation);
    aboutCurrentVersion->SetTextSize(18);
    aboutCurrentVersion->SetTextToCenter();
    aboutCurrentVersion->SetGeometry(0, 110, 910, 50);

    update                      = new Button(this, [this](){Update();});
    update->SetGeometry(400, 295, 200, 50);

    layoutObjPtrs.push_back({"Button", update});
    layoutObjPtrs.push_back({"Label", aboutCurrentVersion});

    objPtrs.push_back({"Entity", updateInformation});
    objPtrs.push_back({"Label", currentVersion});
    objPtrs.push_back({"Label", aboutCurrentVersion});
    objPtrs.push_back({"Button", update});
}

void SettingsWindowItemUpdate::Update()
{
    QString tag{};

    tag += QString::number((version + 1) / 100);        tag += ".";
    tag += QString::number(((version + 1) / 10) % 10);  tag += ".";
    tag += QString::number((version + 1) % 10);

    OpenUrl("https://github.com/gadzhibekov/converter/releases/download/" + tag + "/" + tag + ".zip");

    MessageBox::Message(WARNING_ICON, GetCurrentLayout()[24], 15.0f);
}

SettingsWindowItemLicense::SettingsWindowItemLicense(QWidget* parent) : QWidget(parent)
{
    pandocLicense               = new QWidget(this);
    converterLicense            = new QWidget(this);
    pandocLicense->setGeometry(45, 20, 910, 200);
    converterLicense->setGeometry(45, 240, 910, 200);

    pandocLicenseIcon           = new Label(pandocLicense);
    converterLicenseIcon        = new Label(converterLicense);
    pandocLicenseIcon->SetGeometry(430, 5, 50, 50);
    converterLicenseIcon->SetGeometry(430, 5, 50, 50);
    pandocLicenseIcon->SetIcon("../res/mit.png");
    converterLicenseIcon->SetIcon("../res/mit.png");

    pandocLicenseTitle          = new Label(pandocLicense);
    converterLicenseTitle       = new Label(converterLicense);
    pandocLicenseTitle->SetTextSize(22);
    converterLicenseTitle->SetTextSize(22);
    pandocLicenseTitle->SetTextToCenter();
    converterLicenseTitle->SetTextToCenter();
    pandocLicenseTitle->SetGeometry(0, 55, 910, 50);
    converterLicenseTitle->SetGeometry(0, 55, 910, 50);

    layoutObjPtrs.push_back({"Label", pandocLicenseTitle});
    layoutObjPtrs.push_back({"Label", converterLicenseTitle});

    pandocLicenseInformation    = new Label(pandocLicense);
    converterLicenseInformation = new Label(converterLicense);
    pandocLicenseInformation->setTextFormat(Qt::RichText);
    converterLicenseInformation->setTextFormat(Qt::RichText);
    pandocLicenseInformation->setOpenExternalLinks(true);
    converterLicenseInformation->setOpenExternalLinks(true);
    pandocLicenseInformation->SetTextSize(18);
    converterLicenseInformation->SetTextSize(18);
    pandocLicenseInformation->SetTextToCenter();
    converterLicenseInformation->SetTextToCenter();
    pandocLicenseInformation->SetGeometry(0, 110, 910, 50);
    converterLicenseInformation->SetGeometry(0, 110, 910, 50);

    layoutObjPtrs.push_back({"Label", pandocLicenseInformation});
    layoutObjPtrs.push_back({"Label", converterLicenseInformation});

    objPtrs.push_back({"Entity", pandocLicense});
    objPtrs.push_back({"Entity", converterLicense});
    objPtrs.push_back({"Label",  pandocLicenseTitle});
    objPtrs.push_back({"Label",  converterLicenseTitle});
    objPtrs.push_back({"Label",  pandocLicenseInformation});
    objPtrs.push_back({"Label",  converterLicenseInformation});
}

SettingsWindowItemTheme::SettingsWindowItemTheme(QWidget* parent) : QWidget(parent)
{
    lightThemePhone         = new QWidget(this);
    darkThemePhone          = new QWidget(this);

    lightThemePhone->setGeometry(100, 60, 290, 180);
    darkThemePhone->setGeometry(550, 60, 290, 180);

    objPtrs.push_back({"LTP",  lightThemePhone});
    objPtrs.push_back({"DTP",  darkThemePhone});

    lightThemeTitle         = new Label(this);
    darkThemeTitle          = new Label(this);
    information             = new Label(this);

    layoutObjPtrs.push_back({"Label", lightThemeTitle});
    layoutObjPtrs.push_back({"Label", darkThemeTitle});
    layoutObjPtrs.push_back({"Label", information});

    lightThemeTitle->SetTextToCenter();
    darkThemeTitle->SetTextToCenter();
    information->SetTextToCenter();

    lightThemeTitle->SetTextSize(18);
    darkThemeTitle->SetTextSize(18);
    information->SetTextSize(16);

    lightThemeTitle->SetGeometry(100, 250, 290, 30);
    darkThemeTitle->SetGeometry(550, 250, 290, 30);
    information->SetGeometry(100, 325, 800, 100);

    objPtrs.push_back({"Label",  lightThemeTitle});
    objPtrs.push_back({"Label",  darkThemeTitle});
    objPtrs.push_back({"Label",  information});

    lightThemeRadioButton    = new QRadioButton(this);
    darkThemeRadioButton     = new QRadioButton(this);

    lightThemeRadioButton->setGeometry(225, 280, 50, 50);
    darkThemeRadioButton->setGeometry(675, 280, 50, 50);

    objPtrs.push_back({"RadioButton",  lightThemeRadioButton});
    objPtrs.push_back({"RadioButton",  darkThemeRadioButton});

    darkThemeRadioButton->setChecked(true);

    QObject::connect(lightThemeRadioButton, &QRadioButton::clicked, this, &SettingsWindowItemTheme::LightTheme);
    QObject::connect(darkThemeRadioButton,  &QRadioButton::clicked, this, &SettingsWindowItemTheme::DarkTheme);
}

void SettingsWindowItemTheme::LightTheme()
{
    Switch2LightTheme();
    MessageBox::Message(INFORMATION_ICON, GetCurrentLayout()[14]);
}

void SettingsWindowItemTheme::DarkTheme()
{
    Switch2DarkTheme();
    MessageBox::Message(INFORMATION_ICON, GetCurrentLayout()[15]);
}

SettingsWindowItemLayout::SettingsWindowItemLayout(QWidget* parent) : QWidget(parent)
{
    lezgianAlbanFlag        = new QWidget(this);
    lezgianFlag             = new QWidget(this);
    ruFlag                  = new QWidget(this);
    enFlag                  = new QWidget(this);

    lezgianAlbanFlag->setGeometry(101, 90, 162, 100);
    lezgianFlag->setGeometry(313, 90, 162, 100);
    ruFlag->setGeometry(525, 90, 162, 100);
    enFlag->setGeometry(737, 90, 162, 100);

    objPtrs.push_back({"QWidget",  lezgianAlbanFlag});
    objPtrs.push_back({"QWidget",  lezgianFlag});
    objPtrs.push_back({"QWidget",  ruFlag});
    objPtrs.push_back({"QWidget",  enFlag});

    lezgianAlbanFlagIcon    = new Label(lezgianAlbanFlag);
    lezgianFlagIcon         = new Label(lezgianFlag);
    ruFlagIcon              = new Label(ruFlag);
    enFlagIcon              = new Label(enFlag);

    QVBoxLayout *layoutLezgianAlban = new QVBoxLayout(lezgianAlbanFlag);
    QVBoxLayout *layoutLezgian      = new QVBoxLayout(lezgianFlag);
    QVBoxLayout *layoutRussian      = new QVBoxLayout(ruFlag);
    QVBoxLayout *layoutEnglish      = new QVBoxLayout(enFlag);

    lezgianAlbanFlagIcon->setPixmap(QPixmap("../res/lezgi_flag_alban.jpeg"));
    lezgianFlagIcon->setPixmap(QPixmap("../res/lezgi_flag.jpeg"));
    ruFlagIcon->setPixmap(QPixmap("../res/ru_flag.jpeg"));
    enFlagIcon->setPixmap(QPixmap("../res/en_flag.jpeg"));

    lezgianAlbanFlagIcon->setScaledContents(true);
    lezgianFlagIcon->setScaledContents(true);
    ruFlagIcon->setScaledContents(true);
    enFlagIcon->setScaledContents(true);

    layoutLezgianAlban->addWidget(lezgianAlbanFlagIcon);
    layoutLezgian->addWidget(lezgianFlagIcon);
    layoutRussian->addWidget(ruFlagIcon);
    layoutEnglish->addWidget(enFlagIcon);

    lezgianAlbanFlagTitle   = new Label(this);
    lezgianFlagTitle        = new Label(this);
    ruFlagTitle             = new Label(this);
    enFlagTitle             = new Label(this);
    information             = new Label(this);

    layoutObjPtrs.push_back({"Label", lezgianAlbanFlagTitle});
    layoutObjPtrs.push_back({"Label", lezgianFlagTitle});
    layoutObjPtrs.push_back({"Label", ruFlagTitle});
    layoutObjPtrs.push_back({"Label", enFlagTitle});
    layoutObjPtrs.push_back({"Label", information});

    lezgianAlbanFlagTitle->SetTextToCenter();
    lezgianFlagTitle->SetTextToCenter();
    ruFlagTitle->SetTextToCenter();
    enFlagTitle->SetTextToCenter();
    information->SetTextToCenter();

    lezgianAlbanFlagTitle->SetTextSize(15);
    lezgianFlagTitle->SetTextSize(15);
    ruFlagTitle->SetTextSize(15);
    enFlagTitle->SetTextSize(15);
    information->SetTextSize(16);

    lezgianAlbanFlagTitle->setGeometry(72, 190, 222, 50);
    lezgianFlagTitle->setGeometry(313, 190, 162, 50);
    ruFlagTitle->setGeometry(525, 190, 162, 50);
    enFlagTitle->setGeometry(737, 190, 162, 50);
    information->SetGeometry(100, 310, 800, 80);

    objPtrs.push_back({"Label",  lezgianAlbanFlagTitle});
    objPtrs.push_back({"Label",  lezgianFlagTitle});
    objPtrs.push_back({"Label",  ruFlagTitle});
    objPtrs.push_back({"Label",  enFlagTitle});
    objPtrs.push_back({"Label",  information});

    translateToLezgianAlbanRB   = new QRadioButton(this);
    translateToLezgianRB        = new QRadioButton(this);
    translateToRussianRB        = new QRadioButton(this);
    translateToEnglishRB        = new QRadioButton(this);

    translateToLezgianAlbanRB->setGeometry(171, 250, 162, 22);
    translateToLezgianRB->setGeometry(383, 250, 162, 22);
    translateToRussianRB->setGeometry(595, 250, 162, 22);
    translateToEnglishRB->setGeometry(807, 250, 162, 22);

    objPtrs.push_back({"RadioButton",  translateToLezgianAlbanRB});
    objPtrs.push_back({"RadioButton",  translateToLezgianRB});
    objPtrs.push_back({"RadioButton",  translateToRussianRB});
    objPtrs.push_back({"RadioButton",  translateToEnglishRB});

    translateToEnglishRB->setChecked(true);

    QObject::connect(translateToLezgianAlbanRB, &QRadioButton::clicked, this, &SettingsWindowItemLayout::TranslateToLezgianAlban);
    QObject::connect(translateToLezgianRB,      &QRadioButton::clicked, this, &SettingsWindowItemLayout::TranslateToLezgian);
    QObject::connect(translateToRussianRB,      &QRadioButton::clicked, this, &SettingsWindowItemLayout::TranslateToRussian);
    QObject::connect(translateToEnglishRB,      &QRadioButton::clicked, this, &SettingsWindowItemLayout::TranslateToEnglish);
}

void SettingsWindowItemLayout::TranslateToLezgianAlban()
{
    MessageBox::Message(WARNING_ICON, GetCurrentLayout()[25]);
}

void SettingsWindowItemLayout::TranslateToLezgian()
{
    Translate2Lezgian();
    MessageBox::Message(INFORMATION_ICON, GetCurrentLayout()[26], 3.0f);
}

void SettingsWindowItemLayout::TranslateToRussian()
{
    Translate2Russian();
    MessageBox::Message(INFORMATION_ICON, GetCurrentLayout()[27], 3.0f);
}

void SettingsWindowItemLayout::TranslateToEnglish()
{
    Translate2English();
    MessageBox::Message(INFORMATION_ICON, GetCurrentLayout()[28], 3.0f);
}