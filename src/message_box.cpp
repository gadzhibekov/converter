#include "message_box.h"
#include "theme.h"

#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QStyleOption>
#include <QPainter>


MessageBox* MessageBox::instance = nullptr;

size_t countOfStr;

MessageBox::MessageBox(QWidget* parent) : QWidget(parent)
{
    setObjectName("messageBox");

    icon = new Label(this);
    data = new Label(this);

    data->SetTextToCenter();

    objPtrs.push_back(std::make_pair("MessageBox", this));
    objPtrs.push_back(std::make_pair("MessageBoxLabel", icon));
    objPtrs.push_back(std::make_pair("MessageBoxLabel", data));

    hideTimer = new QTimer(this);
    hideTimer->setSingleShot(true);

    QObject::connect(hideTimer, &QTimer::timeout, []
    {
        Instance()->HideAnimated();
    });

    hide();
}

MessageBox* MessageBox::Instance()
{
    if (!instance)
        instance = new MessageBox();
    return instance;
}

QString MessageBox::Parser(const QString& data)
{
    const size_t limit = 52;
    countOfStr = 0;
    QString result = "";

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

void MessageBox::ShowAnimated()
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

void MessageBox::HideAnimated()
{
    auto* effect = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect());
    if (!effect) {
        effect = new QGraphicsOpacityEffect(this);
        setGraphicsEffect(effect);
    }

    auto* anim = new QPropertyAnimation(effect, "opacity", this);
    anim->setDuration(200);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::InCubic);

    QObject::connect(anim, &QPropertyAnimation::finished, this, [this]{
        hide();
        setGraphicsEffect(nullptr);
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void MessageBox::paintEvent(QPaintEvent*)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MessageBox::Message(const QString& pathToIcon, const QString& data, float timeSeconds)
{
    Instance()->data->SetTextSize(13);
    Instance()->data->SetText(Instance()->Parser(data));
    Instance()->data->setGeometry(30, 1, 468, ((30 - 2) + (countOfStr * 21)));

    Instance()->setGeometry(350, 10, 500, 30 + (countOfStr * 21));


    Instance()->icon->SetIcon(pathToIcon);
    Instance()->icon->SetIconSize(28, 28);
    Instance()->icon->setGeometry(2, ((30 + (countOfStr * 23)) - 28) / 2, 28, 28);

    Instance()->ShowAnimated();
    Instance()->hideTimer->start(static_cast<int>(timeSeconds * 1000.0f));  
}