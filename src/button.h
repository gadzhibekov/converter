#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QEvent>

#include <functional>

struct Button : QPushButton
{
    Button(QWidget* parent);
    Button(QWidget* parent, std::function<void()> slot);
    
    void                        SetIcon(const QString& path);
    void                        SetText(const QString& text);
    void                        SetColor(int red, int green, int blue);
    void                        SetGeometry(int x, int y, int w, int h);
    void                        SetIconSize(int width, int height);
    void                        SetTextSize(int size);

private:

    std::function<void()>       ClickSlot;
};

#endif // BUTTON_H