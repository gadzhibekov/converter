#pragma once
#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QLineEdit>
#include <QWidget>
#include <QString>

class LineEdit : public QLineEdit
{
public:
    LineEdit(QWidget* parent);

    void    SetGeometry(int x, int y, int w, int h);
    void    SetPlaceholderText(const QString& text);
    void    Block();
    void    SetText(const QString& text);
    QString GetText() const;

private:
};

#endif // LINE_EDIT_H