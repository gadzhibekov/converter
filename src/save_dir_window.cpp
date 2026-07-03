#include "save_dir_window.h"
#include "main_window.h"
#include "utils.h"

#include <QObject>
#include <QFileDialog>

static std::vector<QString> convertData;

SaveDirWindow::SaveDirWindow()
{
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setFixedSize(400, 200);
    this->setWindowTitle("Options for saving");
    this->setStyleSheet(ReadAllFile("../styles/widget.css"));

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
    saveDir->SetPlaceholderText("Specify the directory");
    fileName->SetPlaceholderText("Specify the file name");
    back->SetIcon("../res/back.png");

    saveDir->setAlignment(Qt::AlignCenter);
    fileName->setAlignment(Qt::AlignCenter);
    saveInfoText->setAlignment(Qt::AlignCenter);

    saveDir->Block();

    saveInfoText->SetTextSize(12);
    back->SetIconSize(35, 35);

    saveDir->setStyleSheet(ReadAllFile("../styles/line_edit.css"));
    fileName->setStyleSheet(ReadAllFile("../styles/line_edit.css"));
    chooseDir->setStyleSheet(ReadAllFile("../styles/button_2.css"));
    back->setStyleSheet(ReadAllFile("../styles/button_2.css"));
    saveInfoText->setStyleSheet(ReadAllFile("../styles/label.css"));

    QObject::connect(saveDir, &LineEdit::textChanged, this, &SaveDirWindow::UpdateSaveInfoText);
    QObject::connect(fileName, &LineEdit::textChanged, this, &SaveDirWindow::UpdateSaveInfoText);

    Hide();
}

void SaveDirWindow::ChooseDir()
{
    QString choosedDirectory = QFileDialog::getExistingDirectory(this, "Select a folder", "/home", QFileDialog::ShowDirsOnly);

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
        saveInfoText->SetText("The resulting file " + fileName->GetText() + ".pdf\nwill be saved in the directory \n" + saveDir->GetText());
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