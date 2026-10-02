#include "message_box.h"
#include "theme.h"

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QScreen>

#define MESSAGE_LIMIT_SYMBOLS   52
#define DIALOG_LIMIT_SYMBOLS    30

MessageBox* MessageBox::instance        = nullptr;
QWidget*    MessageBox::defaultParent   = nullptr;
bool        MessageBox::status          = false;
size_t      countOfStr;

MessageBox::MessageBox(QWidget* parent) : QWidget(parent)
{
    setObjectName("messageBox");
    this->setAttribute(Qt::WA_TranslucentBackground);

    icon        = new Label(this);
    data        = new Label(this);
    actionMain  = new Button(this);
    actionAdd   = new Button(this);

    actionMain->hide();
    actionAdd->hide();

    data->SetTextToCenter();

    objPtrs.push_back(std::make_pair("MessageBox", this));
    objPtrs.push_back(std::make_pair("MessageBoxLabel", icon));
    objPtrs.push_back(std::make_pair("MessageBoxLabel", data));
    objPtrs.push_back(std::make_pair("Button", actionMain));
    objPtrs.push_back(std::make_pair("Button", actionAdd));

    hideTimer = new QTimer(this);
    hideTimer->setSingleShot(true);

    QObject::connect(hideTimer, &QTimer::timeout, []
    {
        if (!status) Instance()->HideAnimation();
    });

    hide();
}

void MessageBox::SetDefaultParent(QWidget* parent)
{
    defaultParent = parent;
}

MessageBox* MessageBox::Instance()
{
    if (!instance) instance = new MessageBox();

    return instance;
}

QString MessageBox::Parser(const QString& data, const size_t limit)
{
    countOfStr      = 0;
    QString result  = "";

    for (size_t i = 0, j = 0; i < data.size(); ++i, ++j)
    {   
        if (data[i] == '\n')
        {
            countOfStr++;
            j = 0;
        }

        if (j == limit && i != 0)
        {
            result += "-\n";
            countOfStr++;
            j = 0;
        }

        result += data[i];
    }

    return result;
}

void MessageBox::ShowAnimation()
{
    setGraphicsEffect(nullptr);

    show();

    QTimer::singleShot(0, this, [this]
    {
        auto* effect = new QGraphicsOpacityEffect(this);
        effect->setOpacity(0.0);
        setGraphicsEffect(effect);

        auto* anim = new QPropertyAnimation(effect, "opacity", this);
        anim->setDuration(200);
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    });
}

void MessageBox::HideAnimation()
{
    auto* effect = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect());

    if (!effect) 
    {
        effect = new QGraphicsOpacityEffect(this);
        setGraphicsEffect(effect);
    }

    auto* anim = new QPropertyAnimation(effect, "opacity", this);
    anim->setDuration(200);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::InCubic);

    QObject::connect(anim, &QPropertyAnimation::finished, this, [this]
    {
        hide();
        setGraphicsEffect(nullptr);
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void MessageBox::Hide()
{
    Instance()->HideAnimation();
}

void MessageBox::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MessageBox::Message(const QString& pathToIcon,
                         const QString& data,
                         float          timeSeconds,
                         QWidget*       parent)
{
    QWidget* p = parent ? parent : defaultParent;
    Instance()->setParent(p);

    Instance()->status = false;
    Instance()->actionMain->hide();
    Instance()->actionAdd->hide();

    Instance()->data->SetTextSize(13);
    Instance()->data->SetText(Instance()->Parser(data, MESSAGE_LIMIT_SYMBOLS));
    Instance()->data->setGeometry(30, 1, 468, ((30 - 2) + (countOfStr * 25)));

    int y = p ? static_cast<int>(p->height() * 0.02) : 100;
    int x = p ? static_cast<int>((p->width() - 500) / 2) : 0;
    Instance()->setGeometry(x, y, 500, 30 + (countOfStr * 25));

    Instance()->icon->show();
    Instance()->icon->SetIcon(pathToIcon);
    Instance()->icon->SetIconSize(28, 28);
    Instance()->icon->setGeometry(2, ((30 + (countOfStr * 25)) - 28) / 2, 28, 28);

    Instance()->ShowAnimation();
    Instance()->hideTimer->start(static_cast<int>(timeSeconds * 1000.0f));
}

void MessageBox::Dialog(const QString&               data,
                        const QString&               mainActionTitle,
                        std::initializer_list<float> mainActionColor,
                        std::function<void()>        mainAction,
                        const QString&               addActionTitle,
                        std::initializer_list<float> addActionColor,
                        std::function<void()>        addAction,
                        QWidget*                     parent)
{
    QWidget* p = parent ? parent : defaultParent;
    Instance()->setParent(p);
    Instance()->hideTimer->stop();

    Instance()->status = true;
    Instance()->icon->hide();

    Instance()->data->SetTextSize(13);
    Instance()->data->SetText(Instance()->Parser(data, DIALOG_LIMIT_SYMBOLS));
    Instance()->data->setGeometry(25, 5, 310, (30 + (countOfStr * 25)) - 4);

    Instance()->actionMain->show();
    Instance()->actionMain->SetColor(mainActionColor);
    Instance()->actionMain->SetText(mainActionTitle);
    Instance()->actionMain->SetAction([mainAction = std::move(mainAction)]()
    {
        MessageBox::Hide();
        if (mainAction) mainAction();
    });
    Instance()->actionMain->setGeometry(5, (30 + (countOfStr * 25) + 10), 350, 50);

    int h = (30 + (countOfStr * 25)) + 65;

    if (addAction)
    {
        Instance()->actionAdd->show();
        Instance()->actionAdd->SetColor(addActionColor);
        Instance()->actionAdd->SetText(addActionTitle);
        Instance()->actionAdd->SetAction([addAction = std::move(addAction)]()
        {
            MessageBox::Hide();
            if (addAction) addAction();
        });

        Instance()->actionAdd->setGeometry(5, (30 + (countOfStr * 25) + 65), 350, 50);

        h = (30 + (countOfStr * 25)) + 120;
    }

    int y = p ? static_cast<int>((p->height() - h) / 2) : 0;
    int x = p ? static_cast<int>((p->width() - 360) / 2) : 0;

    Instance()->setGeometry(x, y, 360, h);

    Instance()->ShowAnimation();
}