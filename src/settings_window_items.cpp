#include "settings_window_items.h"
#include "utils.h"

#include <QMessageBox>
#include <QProcess>
#include <QCoreApplication>
#include <iostream>

SettingsWindowItemInformation::SettingsWindowItemInformation(QWidget* parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 1000, 500);

    title               = new Label(this);
    information         = new Label(this);

    title->SetText("LaTeX & MarkDown Converter");
    information->SetText(
          (QString)"This program uses the pandoc utility to convert LaTeX and MarkDown codes into readable PDF format.\n"
        + (QString)"The program's source code is protected by the MIT license; more details can be found in the third tab.\n"
        + (QString)"Before you begin, make sure that you have downloaded the pandoc utility and its modules.\nYou can download them by entering the appropriate command in bash for Ubuntu-based distributions.\n\n"
        + (QString)"sudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y"
        + (QString)"\n\nThe command can be copied to the clipboard by clicking the \"Copy\" button below."
    );

    title->SetTextToCenter();
    information->SetTextToCenter();

    title->SetGeometry(0, 60, 1000, 50);
    information->SetGeometry(0, 120, 1000, 200);

    title->SetTextSize(30);
    information->SetTextSize(13);

    title->setStyleSheet(ReadAllFile("../styles/label.css"));
    information->setStyleSheet(ReadAllFile("../styles/label.css"));

    copyCommandButton   = new Button(this, [this](){CopyCommand();});
    copyCommandButton->setText("Copy");
    copyCommandButton->setGeometry(400, 330, 200, 50);
    copyCommandButton->setStyleSheet(ReadAllFile("../styles/button.css"));
}

void SettingsWindowItemInformation::CopyCommand()
{
    ToClipboard("sudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y");
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
    update->setText("Update");
    update->SetGeometry(400, 295, 200, 50);

    updateInformation->setStyleSheet(ReadAllFile("../styles/entity.css"));
    currentVersion->setStyleSheet(ReadAllFile("../styles/label.css"));
    aboutCurrentVersion->setStyleSheet(ReadAllFile("../styles/label.css"));
    update->setStyleSheet(ReadAllFile("../styles/button.css"));
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
                    QMessageBox::critical(nullptr, "Error", "Failed to replace files");
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Working with updates");


                    msgBox.setText("The program has been updated to version " + 
                                ConvertToDecimal(ReadAllFile(converterDataDir + "/version.txt").toInt()) + 
                                "\n\n" + 
                                ReadAllFile(converterDataDir + "/information.txt")
                                + ". The changes will take effect after a reboot.");


                    msgBox.setIcon(QMessageBox::Information);

                    QPushButton *restartButton = msgBox.addButton("Reboot", QMessageBox::AcceptRole);

                    msgBox.exec();

                    if (msgBox.clickedButton() == restartButton)
                    {
                        QString appDirPath = QCoreApplication::applicationDirPath();
                        QString appImagePath = qEnvironmentVariable("APPIMAGE");
                        
                        if (!appImagePath.isEmpty())
                        {
                            QFileInfo appImageInfo(appImagePath);
                            appDirPath = appImageInfo.absolutePath();
                            qDebug() << "Running from AppImage, using path:" << appDirPath;
                        }

                        
                        QProcess::startDetached("sh", QStringList() << "-c" 
                            << QString("chmod a+x \"%1\" && \"%1\"").arg(appImagePath));
                        
                        qApp->quit();
                    }
                }
            }
            else
            {
                QMessageBox::critical(nullptr, "Error", "Failed to download update");
            }

            RemoveDir(converterDataDir);
            net.Disconnect();
        }
        else
        {
            QMessageBox::information(nullptr, "Working with updates", "You have the current version of the program.");
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "Error", "Failed to establish connection to the server");
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
    pandocLicenseTitle->SetText("MIT License");
    converterLicenseTitle->SetText("MIT License");
    pandocLicenseTitle->SetTextSize(22);
    converterLicenseTitle->SetTextSize(22);
    pandocLicenseTitle->SetTextToCenter();
    converterLicenseTitle->SetTextToCenter();
    pandocLicenseTitle->SetGeometry(0, 55, 910, 50);
    converterLicenseTitle->SetGeometry(0, 55, 910, 50);

    pandocLicenseInformation    = new Label(pandocLicense);
    converterLicenseInformation = new Label(converterLicense);
    pandocLicenseInformation->setText(
        "<a href=\"https://github.com/ueberdosis/pandoc/blob/main/LICENSE.md\">"
        "Pandoc License by Hans Pagel</a>"
    );
    converterLicenseInformation->setText(
        "<a href=\"https://github.com/gadzhibekov/converter/blob/main/LICENSE\">"
        "LaTeX & MarkDown Converter License by Beibala Gadzhibekov</a>"
    );
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

    pandocLicense->setStyleSheet(ReadAllFile("../styles/entity.css"));
    converterLicense->setStyleSheet(ReadAllFile("../styles/entity.css"));
    pandocLicenseTitle->setStyleSheet(ReadAllFile("../styles/label.css"));
    converterLicenseTitle->setStyleSheet(ReadAllFile("../styles/label.css"));
    pandocLicenseInformation->setStyleSheet(ReadAllFile("../styles/label.css"));
    converterLicenseInformation->setStyleSheet(ReadAllFile("../styles/label.css"));
}