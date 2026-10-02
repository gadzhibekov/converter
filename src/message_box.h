#pragma once
#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include <QWidget>
#include <QString>
#include <QTimer>

#include <functional>
#include <initializer_list>

#include "button.h"
#include "label.h"
#include "main_window.h"

#define CRITICAL_ICON           "../res/message_box_critical.png"
#define WARNING_ICON            "../res/message_box_warning.png"
#define INFORMATION_ICON        "../res/message_box_information.png"
#define DONE_ICON               "../res/message_box_done.png"

#define BLUE_BUTTON_COLOR       {0, 122, 255, 0.8f}
#define RED_BUTTON_COLOR        {255, 59, 48, 0.8f}
#define GREEN_BUTTON_COLOR      {52, 199, 89, 0.8f}
#define DEFAULT_BUTTON_COLOR    {255, 255, 255, 0.08f}

#define NO_ACTION               {}

class DialogWindowButton;
class Button;

class MessageBox : public QWidget
{
public:
    static MessageBox*      Instance();


    static void             SetDefaultParent(QWidget* parent);
    static void             Hide();
    static void             Message(const QString&              pathToIcon      = INFORMATION_ICON, 
                                    const QString&              data            = "", 
                                    float                       timeSeconds     = 5.0f,
                                    QWidget*                    parent          = nullptr);
    static void             Dialog(const QString&               data            = "", 
                                   const QString&               mainActionTitle = "OK",
                                   std::initializer_list<float> mainActionColor = BLUE_BUTTON_COLOR,
                                   std::function<void()>        mainAction      = NO_ACTION,
                                   const QString&               addActionTitle  = "",
                                   std::initializer_list<float> addActionColor  = DEFAULT_BUTTON_COLOR,
                                   std::function<void()>        addAction       = NO_ACTION,
                                   QWidget*                     parent          = nullptr);

protected:
    void                    paintEvent(QPaintEvent* event) override;

private:
    explicit                MessageBox(QWidget* parent = nullptr);
    QString                 Parser(const QString& data, const size_t limit);
    void                    ShowAnimation();
    void                    HideAnimation();

    static QWidget*         defaultParent;
    QTimer*                 hideTimer;
    Label*                  icon;
    Label*                  data;
    Button*                 actionMain;
    Button*                 actionAdd;

    static bool             status;
    static MessageBox*      instance;
};

#endif // MESSAGE_BOX_H