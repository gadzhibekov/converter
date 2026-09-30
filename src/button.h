#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>

#include <functional>
#include <initializer_list>

#include "message_box.h"

class MessageBox;

class Button : public QPushButton
{
public:
    Button(QWidget* parent);
    Button(QWidget* parent, std::function<void()> slot);
    
    void                        SetIcon(const QString& path);
    void                        SetText(const QString& text);
    void                        SetGeometry(int x, int y, int w, int h);
    void                        SetIconSize(int width, int height);
    void                        SetTextSize(int size);
    void                        SetAction(std::function<void()> action);
    void                        SetColor(std::initializer_list<float> rgba);

private:
    std::function<void()>       clickSlot;
};

#endif // BUTTON_H