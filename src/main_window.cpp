#include "main_window.h"
#include "utils.h"
#include "theme.h"
#include "layout.h"

#include <QMessageBox>
#include <QPushButton>
#include <QApplication>

MessageBox* msgBox = nullptr;
std::vector<QString> MainWindow::convertData;

MainWindow::MainWindow(QWidget* parent, Net& net) : QMainWindow(parent), net(net)
{
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
    
    msgBox->Instance()->setParent(centralWidget);

    objPtrs.push_back({"Label", title});
    objPtrs.push_back({"Label", editSourceTextIcon});
    objPtrs.push_back({"Label", editSaveDirIcon});
    objPtrs.push_back({"Label", startConvertIcon});
    
    title->SetTextToCenter();
    editSourceTextIcon->SetTextToCenter();
    editSaveDirIcon->SetTextToCenter();
    startConvertIcon->SetTextToCenter();

    editSourceTextIcon->SetText("1");
    editSaveDirIcon->SetText("2");
    startConvertIcon->SetText("3");

    layoutObjPtrs.push_back({"Label", title});

    title->SetTextSize(40);
    editSourceTextIcon->SetTextSize(30);
    editSaveDirIcon->SetTextSize(30);
    startConvertIcon->SetTextSize(30);

    title->SetGeometry(0, 50, 1200, 250);
    editSourceTextIcon->SetGeometry(250, 245, 100, 100);
    editSaveDirIcon->SetGeometry(550, 245, 100, 100);
    startConvertIcon->SetGeometry(850, 245, 100, 100);

    editSourceTextButton    = new Button(centralWidget, [this](){OpenSourceTextEditor();});
    editSaveDirButton       = new Button(centralWidget, [this](){OpenSaveDirEditor();});
    startConvertButton      = new Button(centralWidget, [this](){StartConvert();});
    settingsButton          = new Button(centralWidget, [this](){OpenSettingsWindow();});
    exit                    = new Button(centralWidget, [this](){Exit();});

    objPtrs.push_back({"Button", editSourceTextButton});
    objPtrs.push_back({"Button", editSaveDirButton});
    objPtrs.push_back({"Button", startConvertButton});
    objPtrs.push_back({"Button2", settingsButton});
    objPtrs.push_back({"Button2", exit});

    layoutObjPtrs.push_back({"Button", editSourceTextButton});
    layoutObjPtrs.push_back({"Button", editSaveDirButton});
    layoutObjPtrs.push_back({"Button", startConvertButton});

    editSourceTextButton->SetGeometry(200, 345, 200, 50);
    editSaveDirButton->SetGeometry(500, 345, 200, 50);
    startConvertButton->SetGeometry(800, 345, 200, 50);
    settingsButton->SetGeometry(10, 555, 35, 35);
    exit->SetGeometry(10, 10, 35, 35);

    settingsButton->SetIcon("../res/settings.png");
    settingsButton->SetIconSize(35, 35);
    exit->SetIcon("../res/back.png");
    exit->SetIconSize(35, 35);

    textEditor              = new TextEditor();
    saveDirWindow           = new SaveDirWindow();
    settingsWindow          = new SettingsWindow(net);

    MainWindow::convertData.resize(3);

    Switch2DarkTheme();
    Translate2Russian();

    ShowWindow();
}

MainWindow::~MainWindow()
{
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
    QMessageBox msgBox;
    msgBox.setWindowTitle(GetCurrentLayout()[0]);
    msgBox.setText(GetCurrentLayout()[1]);
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

void MainWindow::OpenSettingsWindow()
{
    settingsWindow->show();
}

void MainWindow::Exit()
{
    QApplication::quit();
}