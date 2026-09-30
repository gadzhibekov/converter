#pragma once
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>

#include <vector>

class Button;
class MessageBox;
class TextEditor;
class SaveDirWindow;
class SettingsWindow;

#include "label.h"
#include "button.h"
#include "text_editor.h"
#include "save_dir_window.h"
#include "settings_window.h"
#include "message_box.h"

extern MessageBox* msgBox; 

// class Button;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent);
    ~MainWindow();

    void SetTitle(const QString& title);
    void ShowWindow();

public:
    static std::vector<QString> convertData;

private:
    void OpenSourceTextEditor();
    void OpenSaveDirEditor();
    void StartConvert();
    void OpenSettingsWindow();
    void Exit();

private:
    QWidget*                    centralWidget;
    Label*                      title;
    Label*                      editSourceTextIcon;
    Label*                      editSaveDirIcon;
    Label*                      startConvertIcon;
    Button*                     editSourceTextButton;
    Button*                     editSaveDirButton;
    Button*                     startConvertButton;
    Button*                     settingsButton;
    Button*                     exit;
    TextEditor*                 textEditor;
    SaveDirWindow*              saveDirWindow;
    SettingsWindow*             settingsWindow;
};

#endif // MAIN_WINDOW_H