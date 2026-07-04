#include "button.h"

#include <QPalette>
#include <QObject>
#include <QIcon>
#include <QSize>
#include <QColor>
#include <QFile>
#include <QFont>

Button::Button(QWidget* parent) : QPushButton(parent) {}

Button::Button(QWidget* parent, std::function<void()> slot) : QPushButton(parent), clickSlot(slot)
{
    QObject::connect(this, &QPushButton::clicked, this, [this]() 
    {
        if (clickSlot)
        {
            clickSlot();
        }
    });
}

void Button::SetIcon(const QString& path)
{
    this->setText("");
    this->setIcon(QIcon(path));
    this->setIconSize(QSize(15, 15));
}

void Button::SetIconSize(int width, int height)
{
    this->setIconSize(QSize(width, height));
}

void Button::SetText(const QString& text)
{
    this->setText(text);
}

void Button::SetGeometry(int x, int y, int w, int h)
{
    this->setGeometry(x, y, w, h);
}

void Button::SetTextSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size); 
    this->setFont(font);
}