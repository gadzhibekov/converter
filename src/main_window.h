#pragma once
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>

#include <vector>

#include "label.h"
#include "button.h"
#include "net.h"
#include "text_editor.h"
#include "save_dir_window.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent, Net& net);
    ~MainWindow();

    void SetSized(int w, int h);
    void SetTitle(const QString& title);
    void ShowWindow();

public:
    static std::vector<QString> convertData;

private:
    void Update();
    void OpenSourceTextEditor();
    void OpenSaveDirEditor();
    void StartConvert();

private:
    QWidget*                    centralWidget;
    Label*                      title;
    Label*                      editSourceTextIcon;
    Label*                      editSaveDirIcon;
    Label*                      startConvertIcon;
    Label*                      versionLabel;
    Button*                     editSourceTextButton;
    Button*                     editSaveDirButton;
    Button*                     startConvertButton;
    Button*                     updateButton;
    Net&                        net;
    TextEditor*                 textEditor;
    SaveDirWindow*              saveDirWindow;
};

#endif // MAIN_WINDOW_H