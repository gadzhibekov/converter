#include "button.h"
#include "main_window.h"

#include <QPalette>
#include <QObject>
#include <QIcon>
#include <QSize>
#include <QColor>
#include <QFile>
#include <QFont>
#include <QRegularExpression>
#include <QString>

Button::Button(QWidget* parent)
    : QPushButton(parent)
{
    QObject::connect(this, &QPushButton::clicked, this, [this]() 
    {
        if (clickSlot) clickSlot();
    });
}

Button::Button(QWidget* parent, std::function<void()> slot)
    : QPushButton(parent), clickSlot(std::move(slot))
{
    QObject::connect(this, &QPushButton::clicked, this, [this]() 
    {
        if (clickSlot) clickSlot();
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

void Button::SetAction(std::function<void()> action)
{
    clickSlot = std::move(action); 
}

void Button::SetColor(std::initializer_list<float> rgba)
{
    if (rgba.size() != 4) return;

    auto it = rgba.begin();
    const int r = qBound(0, static_cast<int>(*it++), 255);
    const int g = qBound(0, static_cast<int>(*it++), 255);
    const int b = qBound(0, static_cast<int>(*it++), 255);
    const float a = qBound(0.0f, *it, 1.0f);

    const QString color = QString("rgba(%1, %2, %3, %4)")
        .arg(r)
        .arg(g)
        .arg(b)
        .arg(QString::number(a, 'f', 2));

    QString qss = this->styleSheet();

    static const QRegularExpression blockRe(
        R"(QPushButton\s*\{[^}]*\})",
        QRegularExpression::CaseInsensitiveOption
    );

    static const QRegularExpression bgRe(
        R"(background(?:-color)?\s*:\s*[^;]+;)",
        QRegularExpression::CaseInsensitiveOption
    );

    auto blockMatch = blockRe.match(qss);

    if (blockMatch.hasMatch())
    {
        QString block = blockMatch.captured(0);

        if (bgRe.match(block).hasMatch())
            block.replace(bgRe, QString("background: %1;").arg(color));
        else
        {
            int insertPos = block.indexOf('{') + 1;
            block.insert(insertPos, QString("\n    background: %1;").arg(color));
        }

        qss.replace(blockMatch.capturedStart(), blockMatch.capturedLength(), block);
    }
    else
    {
        qss += QString("\nQPushButton { background: %1; }").arg(color);
    }

    this->setStyleSheet(qss);
}