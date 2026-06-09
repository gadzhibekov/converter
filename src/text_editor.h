#pragma once
#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#include <QTextEdit>
#include <QWidget>
#include <QString>

#include "button.h"

class TextEditor : public QWidget
{
public:
    TextEditor();

    void    Show();
    void    Hide();
    QString GetText() const;

private:
    void    Back();
    void    IncreaseText();
    void    DecreaseText();
    void    GetTextSlot();

private:
    QTextEdit*  textEditor;
    Button*     back;
    Button*     increaseText;
    Button*     decreaseText;
};

#endif // SRC_TEXT_EDITOR_H