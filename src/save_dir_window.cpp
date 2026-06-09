#include "save_dir_window.h"
#include "main_window.h"

#include <QObject>
#include <QFileDialog>

static std::vector<QString> convertData;

SaveDirWindow::SaveDirWindow()
{
    this->setGeometry(0, 0, 400, 200);
    this->setWindowTitle("Save Dir Window");

    saveDir         = new LineEdit(this);
    fileName        = new LineEdit(this);
    chooseDir       = new Button(this, [this](){ChooseDir();});
    saveInfoText    = new Label(this);

    saveDir->SetGeometry(5, 5, 350, 40);
    fileName->SetGeometry(5, 50, 350, 40);
    chooseDir->SetGeometry(355, 5, 40, 40);
    saveInfoText->SetGeometry(5, 80, 380, 100);

    chooseDir->SetText("...");
    saveDir->SetPlaceholderText("Укажите директорию");
    fileName->SetPlaceholderText("Укажите название файла");

    saveDir->setAlignment(Qt::AlignCenter);
    fileName->setAlignment(Qt::AlignCenter);
    saveInfoText->setAlignment(Qt::AlignCenter);

    saveDir->Block();

    saveInfoText->SetTextSize(12);

    QObject::connect(saveDir, &LineEdit::textChanged, this, &SaveDirWindow::UpdateSaveInfoText);
    QObject::connect(fileName, &LineEdit::textChanged, this, &SaveDirWindow::UpdateSaveInfoText);

    Hide();
}

void SaveDirWindow::ChooseDir()
{
    QString choosedDirectory = QFileDialog::getExistingDirectory(this, "Выберите папку", "/home", QFileDialog::ShowDirsOnly);

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
        saveInfoText->SetText("Полученный файл " + fileName->GetText() + ".pdf\nбудет сохранён в директорию \n" + saveDir->GetText());
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