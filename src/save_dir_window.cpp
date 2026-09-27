#include "save_dir_window.h"
#include "main_window.h"
#include "utils.h"
#include "theme.h"
#include "layout.h"

#include <QObject>
#include <QFileDialog>

static std::vector<QString> convertData;

SaveDirWindow::SaveDirWindow()
{
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(400, 200);

    layoutObjPtrs.push_back({"Widget", this});
    objPtrs.push_back({"Widget", this});

    saveDir         = new LineEdit(this);
    fileName        = new LineEdit(this);
    chooseDir       = new Button(this, [this](){ChooseDir();});
    back            = new Button(this, [this](){Back();});
    saveInfoText    = new Label(this);

    saveDir->SetGeometry(5, 5, 350, 40);
    fileName->SetGeometry(5, 50, 350, 40);
    chooseDir->SetGeometry(355, 5, 40, 40);
    back->SetGeometry(360, 160, 35, 35);
    saveInfoText->SetGeometry(5, 90, 350, 100);

    chooseDir->SetText("...");
    back->SetIcon("../res/back.png");

    layoutObjPtrs.push_back({"LineEditPlaceHolder", saveDir});
    layoutObjPtrs.push_back({"LineEditPlaceHolder", fileName});

    saveDir->setAlignment(Qt::AlignCenter);
    fileName->setAlignment(Qt::AlignCenter);
    saveInfoText->setAlignment(Qt::AlignCenter);

    saveDir->Block();

    saveInfoText->SetTextSize(12);
    back->SetIconSize(35, 35);

    objPtrs.push_back({"LineEdit", saveDir});
    objPtrs.push_back({"LineEdit", fileName});
    objPtrs.push_back({"Button2", chooseDir});
    objPtrs.push_back({"Button2", back});
    objPtrs.push_back({"Label", saveInfoText});

    QObject::connect(saveDir, &LineEdit::textChanged, this, &SaveDirWindow::UpdateSaveInfoText);
    QObject::connect(fileName, &LineEdit::textChanged, this, &SaveDirWindow::UpdateSaveInfoText);

    Hide();
}

void SaveDirWindow::ChooseDir()
{
    QString choosedDirectory = QFileDialog::getExistingDirectory(this, GetCurrentLayout()[4], "/home", QFileDialog::ShowDirsOnly);

    if (!choosedDirectory.isEmpty())
    {
        saveDir->SetText(choosedDirectory);
    }
}

void SaveDirWindow::UpdateSaveInfoText()
{
    MainWindow::convertData[0] = fileName->GetText();
    MainWindow::convertData[1] = saveDir->GetText();

    if (fileName->GetText() != "" && saveDir->GetText() != "")
    {
        saveInfoText->SetText(GetCurrentLayout()[2] + fileName->GetText() + GetCurrentLayout()[3] + saveDir->GetText());
    }
}

void SaveDirWindow::Show()
{
    this->show();
}

void SaveDirWindow::Hide()
{
    this->hide();
}

void SaveDirWindow::Back()
{
    this->hide();
}