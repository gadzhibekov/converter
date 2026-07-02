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
    this->setWindowTitle("LaTeX & MarkDown Converter by Beibala Gadzhibekov");
    this->setStyleSheet(ReadAllFile("../styles/widget.css"));

    title                   = new Label(centralWidget);
    editSourceTextIcon      = new Label(centralWidget);
    editSaveDirIcon         = new Label(centralWidget);
    startConvertIcon        = new Label(centralWidget);

    title->setStyleSheet(ReadAllFile("../styles/label.css"));
    editSourceTextIcon->setStyleSheet(ReadAllFile("../styles/label.css"));
    editSaveDirIcon->setStyleSheet(ReadAllFile("../styles/label.css"));
    startConvertIcon->setStyleSheet(ReadAllFile("../styles/label.css"));
    
    title->SetTextToCenter();
    editSourceTextIcon->SetTextToCenter();
    editSaveDirIcon->SetTextToCenter();
    startConvertIcon->SetTextToCenter();

    title->SetText("LaTeX & MarkDown Converter");
    editSourceTextIcon->SetText("1");
    editSaveDirIcon->SetText("2");
    startConvertIcon->SetText("3");

    title->SetTextSize(40);
    editSourceTextIcon->SetTextSize(30);
    editSaveDirIcon->SetTextSize(30);
    startConvertIcon->SetTextSize(30);

    title->SetGeometry(0, 0, 1200, 250);
    editSourceTextIcon->SetGeometry(250, 195, 100, 100);
    editSaveDirIcon->SetGeometry(550, 195, 100, 100);
    startConvertIcon->SetGeometry(850, 195, 100, 100);

    editSourceTextButton    = new Button(centralWidget, [this](){OpenSourceTextEditor();});
    editSaveDirButton       = new Button(centralWidget, [this](){OpenSaveDirEditor();});
    startConvertButton      = new Button(centralWidget, [this](){StartConvert();});
    settingsButton          = new Button(centralWidget, [this](){OpenSettingsWindow();});

    editSourceTextButton->setStyleSheet(ReadAllFile("../styles/button.css"));
    editSaveDirButton->setStyleSheet(ReadAllFile("../styles/button.css"));
    startConvertButton->setStyleSheet(ReadAllFile("../styles/button.css"));
    settingsButton->setStyleSheet(ReadAllFile("../styles/button.css"));

    editSourceTextButton->SetText("Sourse text");
    editSaveDirButton->SetText("Save as");
    startConvertButton->SetText("Convert");

    editSourceTextButton->SetGeometry(200, 295, 200, 50);
    editSaveDirButton->SetGeometry(500, 295, 200, 50);
    startConvertButton->SetGeometry(800, 295, 200, 50);
    settingsButton->SetGeometry(5, 600 - 40, 35, 35);

    settingsButton->SetIcon("../res/settings.png");
    settingsButton->SetIconSize(35, 35);

    textEditor              = new TextEditor();
    saveDirWindow           = new SaveDirWindow();
    settingsWindow          = new SettingsWindow(net);

    MainWindow::convertData.resize(3);

    ShowWindow();
}

MainWindow::~MainWindow()
{
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
    msgBox.setWindowTitle("Select format");
    msgBox.setText("What format would you like to create the document in?");
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