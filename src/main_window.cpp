#include "main_window.h"
#include "utils.h"

#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QCoreApplication>
#include <QProcess>

std::vector<QString> MainWindow::convertData;

MainWindow::MainWindow(QWidget* parent, Net& net) : QMainWindow(parent), net(net)
{
    centralWidget           = new QWidget(this);
    this->setCentralWidget(centralWidget);
    this->setFixedSize(1200, 600);
    this->setWindowTitle("LaTeX & MarkDown Converter by Gadzhibekov");

    title                   = new Label(centralWidget);
    editSourceTextIcon      = new Label(centralWidget);
    editSaveDirIcon         = new Label(centralWidget);
    startConvertIcon        = new Label(centralWidget);
    versionLabel            = new Label(centralWidget);
    informationLabel        = new Label(centralWidget);
    
    title->SetTextToCenter();
    editSourceTextIcon->SetTextToCenter();
    editSaveDirIcon->SetTextToCenter();
    startConvertIcon->SetTextToCenter();
    informationLabel->SetTextToCenter();

    title->SetText("LaTeX & MarkDown Converter");
    editSourceTextIcon->SetText("1");
    editSaveDirIcon->SetText("2");
    startConvertIcon->SetText("3");
    versionLabel->SetText("v " + QString::number(ConvertToDecimal(version)));
    informationLabel->SetText((QString)"Перед началом убедитесь, что у вас скачана утилита pandoc и его модули.\nСкачать их можно введя соответствующую команду в bash для дистрибутивов основанных на Ubuntu."
        + (QString)"\nКоманду можно скопировать в буфер обмена нажав на кнопку 'Скопировать' ниже.");

    title->SetTextSize(40);
    editSourceTextIcon->SetTextSize(30);
    editSaveDirIcon->SetTextSize(30);
    startConvertIcon->SetTextSize(30);
    versionLabel->SetTextSize(18);
    informationLabel->SetTextSize(13);

    title->SetGeometry(0, 0, 1200, 250);
    editSourceTextIcon->SetGeometry(250, 195, 100, 100);
    editSaveDirIcon->SetGeometry(550, 195, 100, 100);
    startConvertIcon->SetGeometry(850, 195, 100, 100);
    versionLabel->SetGeometry(1200 - 70, 600 - 30, 65, 25);
    informationLabel->SetGeometry(150, 600 - 250, 900, 200);

    editSourceTextButton    = new Button(centralWidget, [this](){OpenSourceTextEditor();});
    editSaveDirButton       = new Button(centralWidget, [this](){OpenSaveDirEditor();});
    startConvertButton      = new Button(centralWidget, [this](){StartConvert();});
    updateButton            = new Button(centralWidget, [this](){Update();});
    copyCommandButton       = new Button(centralWidget, [this](){CopyCommand();});

    editSourceTextButton->SetText("Исходный текст");
    editSaveDirButton->SetText("Сохранить как");
    startConvertButton->SetText("Сконвертировать");
    updateButton->SetText("Обновить");
    copyCommandButton->SetText("Скопировать");

    editSourceTextButton->SetGeometry(200, 295, 200, 50);
    editSaveDirButton->SetGeometry(500, 295, 200, 50);
    startConvertButton->SetGeometry(800, 295, 200, 50);
    updateButton->SetGeometry(5, 600 - 30, 100, 25);
    copyCommandButton->SetGeometry(110, 600 - 30, 100, 25);

    textEditor              = new TextEditor();
    saveDirWindow           = new SaveDirWindow();

    MainWindow::convertData.resize(3);

    ShowWindow();
}

MainWindow::~MainWindow()
{
    delete textEditor;
    delete saveDirWindow;
}

void MainWindow::Update()
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
                    QMessageBox::critical(nullptr, "Ошибка", "Не удалсось сделать замену файлов");
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Работа с обновлениями");


                    msgBox.setText("Программа обновлена до версии " + 
                                QString::number(ConvertToDecimal(ReadAllFile(converterDataDir + "/version.txt").toInt())) + 
                                "\n\n" + 
                                ReadAllFile(converterDataDir + "/information.txt")
                                + ". Изменения вступят в силу после перезагрузки");


                    msgBox.setIcon(QMessageBox::Information);

                    QPushButton *restartButton = msgBox.addButton("Перезагрузить", QMessageBox::AcceptRole);

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
                QMessageBox::critical(nullptr, "Ошибка", "Не удалсось скачать обновление");
            }

            RemoveDir(converterDataDir);
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
    textEditor->Show();
}

void MainWindow::OpenSaveDirEditor()
{
    saveDirWindow->Show();
}

void MainWindow::StartConvert()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Выберите формат");
    msgBox.setText("В каком формате вы хотите создать документ ?");
    msgBox.setIcon(QMessageBox::Question);

    QPushButton *latexButton = msgBox.addButton("LaTeX", QMessageBox::AcceptRole);
    QPushButton *markdownButton = msgBox.addButton("MarkDown", QMessageBox::AcceptRole);

    msgBox.exec();

    if (msgBox.clickedButton() == latexButton)          ConvertLatexToPdf();
    else if (msgBox.clickedButton() == markdownButton)  ConvertMarkdownToPdf();
}

void MainWindow::SetTitle(const QString& title)
{
    this->setWindowTitle(title);
}

void MainWindow::ShowWindow()
{
    this->show();
}

void MainWindow::CopyCommand()
{
    ToClipboard("sudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y");
}