#include "settings_window_items.h"
#include "utils.h"
#include "theme.h"
#include "message_box.h"
#include "layout.h"

#include <QMessageBox>
#include <QProcess>
#include <QCoreApplication>

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


SettingsWindowItemUpdate::SettingsWindowItemUpdate(QWidget* parent, Net& net) : QWidget(parent), net(net)
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
    aboutCurrentVersion->setText(aboutVersion);
    aboutCurrentVersion->SetTextSize(18);
    aboutCurrentVersion->SetTextToCenter();
    aboutCurrentVersion->SetGeometry(0, 110, 910, 50);

    update                      = new Button(this, [this](){Update();});
    update->SetGeometry(400, 295, 200, 50);

    layoutObjPtrs.push_back({"Button", update});

    objPtrs.push_back({"Entity", updateInformation});
    objPtrs.push_back({"Label", currentVersion});
    objPtrs.push_back({"Label", aboutCurrentVersion});
    objPtrs.push_back({"Button", update});
}

void SettingsWindowItemUpdate::Update()
{
    if (net.Connect())
    {
        if (version != ConverQstrToInt(net.RequestVersion()))
        {
            CreateDir(converterDataDir);

            if (net.RequestUpdates(converterDataDir.toStdString()))
            {
                if (!CopyDirectoryToAppDir(converterDataDir))
                {
                    MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[6]);
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle(GetCurrentLayout()[7]);


                    msgBox.setText(GetCurrentLayout()[8] + 
                                ConvertToDecimal(ReadAllFile(converterDataDir + "/version.txt").toInt()) + 
                                "\n\n" + 
                                ReadAllFile(converterDataDir + "/information.txt")
                                + GetCurrentLayout()[9]);


                    msgBox.setIcon(QMessageBox::Information);

                    QPushButton *restartButton = msgBox.addButton(GetCurrentLayout()[10], QMessageBox::AcceptRole);

                    msgBox.exec();

                    if (msgBox.clickedButton() == restartButton)
                    {
                        QString appDirPath = QCoreApplication::applicationDirPath();
                        QString appImagePath = qEnvironmentVariable("APPIMAGE");
                        
                        if (!appImagePath.isEmpty())
                        {
                            QFileInfo appImageInfo(appImagePath);
                            appDirPath = appImageInfo.absolutePath();
                        }

                        
                        QProcess::startDetached("sh", QStringList() << "-c" 
                            << QString("chmod a+x \"%1\" && \"%1\"").arg(appImagePath));
                        
                        qApp->quit();
                    }
                }
            }
            else
            {
                MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[11]);
            }

            RemoveDir(converterDataDir);
            net.Disconnect();
        }
        else
        {
            MessageBox::Message(DONE_ICON, GetCurrentLayout()[12]);
        }
    }
    else
    {
        MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[13]);
    }
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
    QObject::connect(darkThemeRadioButton, &QRadioButton::clicked, this, &SettingsWindowItemTheme::DarkTheme);
}

void SettingsWindowItemTheme::LightTheme()
{
    Switch2LightTheme();
    MessageBox::Message(DONE_ICON, GetCurrentLayout()[14]);
}

void SettingsWindowItemTheme::DarkTheme()
{
    Switch2DarkTheme();
    MessageBox::Message(DONE_ICON, GetCurrentLayout()[15]);
}