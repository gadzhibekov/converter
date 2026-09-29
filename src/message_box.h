#pragma once
#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#define CRITICAL_ICON       "../res/message_box_critical.png"
#define WARNING_ICON        "../res/message_box_warning.png"
#define INFORMATION_ICON    "../res/message_box_information.png"
#define DONE_ICON           "../res/message_box_done.png"

#include <QWidget>
#include <QString>
#include <QTimer>

#include "label.h"

class MessageBox : public QWidget
{
public:
    static MessageBox* Instance();

    static void Message(const QString& pathToIcon, const QString& data, float timeSeconds = 5.0f);

protected:
    void        paintEvent(QPaintEvent* event) override;

private:
    explicit    MessageBox(QWidget* parent = nullptr);
    QString     Parser(const QString& data);
    void        ShowAnimated();
    void        HideAnimated();

    QTimer*     hideTimer;

    Label*      icon;
    Label*      data;

    static MessageBox* instance;
};

#endif // MESSAGE_BOX_H