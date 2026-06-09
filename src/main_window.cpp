#include "main_window.h"
#include "utils.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent, Net& net) : QMainWindow(parent), net(net)
{
    centralWidget           = new QWidget(this);
    this->setCentralWidget(centralWidget);
    this->SetSized(1200, 600);
    this->setWindowTitle("LaTeX Converter by Gadzhibekov");

    title                   = new Label(centralWidget);
    editSourceTextIcon      = new Label(centralWidget);
    editSaveDirIcon         = new Label(centralWidget);
    startConvertIcon        = new Label(centralWidget);
    versionLabel            = new Label(centralWidget);
    
    title->SetTextToCenter();
    editSourceTextIcon->SetTextToCenter();
    editSaveDirIcon->SetTextToCenter();
    startConvertIcon->SetTextToCenter();

    title->SetText("LaTeX Converter");
    editSourceTextIcon->SetText("1");
    editSaveDirIcon->SetText("2");
    startConvertIcon->SetText("3");
    versionLabel->SetText("v 1." + QString::number(version));


    title->SetTextSize(40);
    editSourceTextIcon->SetTextSize(30);
    editSaveDirIcon->SetTextSize(30);
    startConvertIcon->SetTextSize(30);
    versionLabel->SetTextSize(18);


    title->SetGeometry(0, 0, 1200, 250);
    editSourceTextIcon->SetGeometry(250, 195, 100, 100);
    editSaveDirIcon->SetGeometry(550, 195, 100, 100);
    startConvertIcon->SetGeometry(850, 195, 100, 100);
    versionLabel->SetGeometry(1200 - 70, 600 - 30, 65, 25);

    editSourceTextButton    = new Button(centralWidget, [this](){OpenSourceTextEditor();});
    editSaveDirButton       = new Button(centralWidget, [this](){OpenSaveDirEditor();});
    startConvertButton      = new Button(centralWidget, [this](){StartConvert();});
    updateButton            = new Button(centralWidget, [this](){Update();});

    editSourceTextButton->SetText("Source text");
    editSaveDirButton->SetText("Save dir");
    startConvertButton->SetText("Start convert");
    updateButton->SetText("Update");

    editSourceTextButton->SetGeometry(200, 295, 200, 50);
    editSaveDirButton->SetGeometry(500, 295, 200, 50);
    startConvertButton->SetGeometry(800, 295, 200, 50);
    updateButton->SetGeometry(5, 600 - 30, 100, 25);

    this->ShowWindow();
}

void MainWindow::Update()
{
    if (net.Connect())
    {
        if (version != ConverQstrToInt(net.RequestVersion()))
        {
            CreateUpdatedDataDir();

            if (net.RequestUpdates(UpdatedDataDir.toStdString()))
            {
                if (!CopyDirectoryToAppDir(UpdatedDataDir))
                {
                    QMessageBox::critical(nullptr, "Ошибка", "Не удалсось сделать замену файлов");
                }
                else
                {
                    QString updatedVersion = "1." + ReadAllFile(UpdatedDataDir + "/version.txt");

                    QMessageBox::information(nullptr, "Работа с обновлениями", 
                        "Программа обновлена до версии " + updatedVersion + "\n\nПерезагрузите программу");
                }
            }
            else
            {
                QMessageBox::critical(nullptr, "Ошибка", "Не удалсось скчать обновление");
            }

            RemoveUpdatedDataDir();
            net.Disconnect();
        }
        else
        {
            QMessageBox::information(nullptr, "Работа с обновлениями", "У вас актуальная версия");
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалсось установить соединение с сервером");
    }
}

void MainWindow::OpenSourceTextEditor()
{
    QMessageBox::information(nullptr, "", "Тут будет редакотор текста");
}

void MainWindow::OpenSaveDirEditor()
{
    QMessageBox::information(nullptr, "", "Тут будет окно чтоб указать путь для сохранения результов");
}

void MainWindow::StartConvert()
{
    QMessageBox::information(nullptr, "", "Кнопка Старт");
}

void MainWindow::SetSized(int w, int h)
{
    this->setFixedSize(w, h);
}

void MainWindow::SetTitle(const QString& title)
{
    this->setWindowTitle(title);
}

void MainWindow::ShowWindow()
{
    this->show();
}