#pragma once
#ifndef SAVE_DIR_WINDOW_H
#define SAVE_DIR_WINDOW_H

#include <QWidget>
#include <QString>

#include "line_edit.h"
#include "button.h"
#include "label.h"

class SaveDirWindow : public QWidget
{
public:
    SaveDirWindow();

    void    Show();
    void    Hide();

private:
    void    UpdateSaveInfoText();
    void    ChooseDir();
    void    Back();

private:
    LineEdit*       saveDir;
    LineEdit*       fileName;
    Label*          saveInfoText;
    Button*         chooseDir;
    Button*         back;
};

#endif // SAVE_DIR_WINDOW_H