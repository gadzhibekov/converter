#pragma once
#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include <QString>
#include <QWidget>

class Label : public QLabel
{
public:
    Label(QWidget* parent);
    
    void SetText(const QString& str);
    void SetGeometry(int x, int y, int w, int h);
    void SetTextSize(int size);
    void SetIcon(const QString& path);
    void SetIconSize(int width, int height);
    void SetTextToCenter();

private:

};

#endif // LABEL_H