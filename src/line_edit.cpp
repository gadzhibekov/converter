#include "line_edit.h"

#include <iostream>

LineEdit::LineEdit(QWidget* parent) : QLineEdit(parent) {}

void LineEdit::SetPlaceholderText(const QString& text)
{
    this->setPlaceholderText(text);
}

void LineEdit::Block()
{
    this->setReadOnly(true);
}

void LineEdit::SetGeometry(int x, int y, int w, int h)
{
    this->setGeometry(x, y, w, h);
}

void LineEdit::SetText(const QString& text)
{
    this->setText(text);
}

QString LineEdit::GetText() const
{
    return this->text();
}