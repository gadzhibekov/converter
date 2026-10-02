#include "main_window.h"
#include "utils.h"
#include "theme.h"
#include "layout.h"
#include "message_box.h"

#include <QMessageBox>
#include <QPushButton>
#include <QApplication>

#include <iostream>

ConfigData              configData;
MessageBox*             msgBox                      = nullptr;
std::vector<QString>    MainWindow::convertData;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    configData = Config::Read();

    centralWidget           = new QWidget(this);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setCentralWidget(centralWidget);
    this->setFixedSize(1200, 600);

    layoutObjPtrs.push_back({"MainWindow", this});

    objPtrs.push_back(std::make_pair("Widget", centralWidget));

    title                   = new Label(centralWidget);
    editSourceTextIcon      = new Label(centralWidget);
    editSaveDirIcon         = new Label(centralWidget);
    startConvertIcon        = new Label(centralWidget);
    horizontalLine_1        = new Label(centralWidget);
    horizontalLine_2        = new Label(centralWidget);

    objPtrs.push_back({"Label", title});
    objPtrs.push_back({"Label", editSourceTextIcon});
    objPtrs.push_back({"Label", editSaveDirIcon});
    objPtrs.push_back({"Label", startConvertIcon});
    
    title->SetTextToCenter();
    editSourceTextIcon->SetTextToCenter();
    editSaveDirIcon->SetTextToCenter();
    startConvertIcon->SetTextToCenter();

    editSourceTextIcon->SetIcon("../res/add.png");
    editSaveDirIcon->SetIcon("../res/save_dir.png");
    startConvertIcon->SetIcon("../res/flash.png");
    horizontalLine_1->SetIcon("../res/horizontal_line.png");
    horizontalLine_2->SetIcon("../res/horizontal_line.png");

    editSourceTextIcon->SetIconSize(60, 60);
    editSaveDirIcon->SetIconSize(60, 60);
    startConvertIcon->SetIconSize(60, 60);
    horizontalLine_1->SetIconSize(190, 50);
    horizontalLine_2->SetIconSize(190, 50);

    layoutObjPtrs.push_back({"Label", title});

    title->SetTextSize(40);

    title->SetGeometry(0, 50, 1200, 250);
    editSourceTextIcon->SetGeometry(270, 270, 80, 70);
    horizontalLine_1->SetGeometry(350, 275, 80, 190);
    editSaveDirIcon->SetGeometry(570, 270, 80, 70);
    horizontalLine_2->SetGeometry(665, 275, 80, 190);
    startConvertIcon->SetGeometry(870, 270, 80, 70);

    editSourceTextButton    = new Button(centralWidget, [this](){OpenSourceTextEditor();});
    editSaveDirButton       = new Button(centralWidget, [this](){OpenSaveDirEditor();});
    startConvertButton      = new Button(centralWidget, [this](){StartConvert();});
    settingsButton          = new Button(centralWidget, [this](){OpenSettingsWindow();});
    exit                    = new Button(centralWidget, [this](){Exit();});
    minimize                = new Button(centralWidget, [this](){Minimize();});

    objPtrs.push_back({"Button", editSourceTextButton});
    objPtrs.push_back({"Button", editSaveDirButton});
    objPtrs.push_back({"Button", startConvertButton});
    objPtrs.push_back({"Button2", settingsButton});
    objPtrs.push_back({"Button3", exit});
    objPtrs.push_back({"Button3", minimize});

    layoutObjPtrs.push_back({"Button", editSourceTextButton});
    layoutObjPtrs.push_back({"Button", editSaveDirButton});
    layoutObjPtrs.push_back({"Button", startConvertButton});

    editSourceTextButton->SetGeometry(200, 345, 210, 50);
    editSaveDirButton->SetGeometry(500, 345, 210, 50);
    startConvertButton->SetGeometry(800, 345, 210, 50);
    settingsButton->SetGeometry(10, 555, 35, 35);
    exit->SetGeometry(5, 5, 20, 20);
    minimize->SetGeometry(30, 5, 20, 20);

    settingsButton->SetIcon("../res/settings.png");
    exit->SetIcon("../res/red_circle.png");
    minimize->SetIcon("../res/yellow_circle.png");

    settingsButton->SetIconSize(35, 35);
    exit->SetIconSize(20, 20);
    minimize->SetIconSize(20, 20);

    textEditor              = new TextEditor();
    saveDirWindow           = new SaveDirWindow();
    settingsWindow          = new SettingsWindow();

    MainWindow::convertData.resize(3);

    msgBox->Instance()->SetDefaultParent(centralWidget);

    ShowWindow();

    if (configData.language == "lezgian")   Translate2Lezgian();
    if (configData.language == "russian")   Translate2Russian();
    if (configData.language == "english")   Translate2English();
    if (configData.theme    == "light")     Switch2LightTheme();
    if (configData.theme    == "dark")      Switch2DarkTheme();

    if (configData.showAgain == "yes")
    {
        MessageBox::Dialog( GetCurrentLayout()[29],
                            GetCurrentLayout()[30],
                            DEFAULT_BUTTON_COLOR,
                            NO_ACTION,
                            GetCurrentLayout()[31],
                            RED_BUTTON_COLOR,
                            [](){configData.showAgain = "no";} );
    }
}

MainWindow::~MainWindow()
{
    Config::Write(configData);

    if (msgBox) delete msgBox;

    delete textEditor;
    delete saveDirWindow;
    delete settingsWindow;
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
    MessageBox::Dialog( GetCurrentLayout()[1],
                        "LaTeX",
                        BLUE_BUTTON_COLOR,
                        [](){LatexToPdf();},
                        "MarkDown",
                        GREEN_BUTTON_COLOR,
                        [](){MarkdownToPdf();});
}

void MainWindow::SetTitle(const QString& title)
{
    this->setWindowTitle(title);
}

void MainWindow::ShowWindow()
{
    this->show();
}

void MainWindow::OpenSettingsWindow()
{
    settingsWindow->show();
}

void MainWindow::Exit()
{
    QApplication::quit();
}

void MainWindow::Minimize()
{
    this->setWindowState(this->windowState() | Qt::WindowMinimized);
}