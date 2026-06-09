#include "label.h"

#include <QFont>
#include <QPixmap>

Label::Label(QWidget* parent) : QLabel(parent) {}

void Label::SetText(const QString& str)
{
    this->setText(str);
}

void Label::SetGeometry(int x, int y, int w, int h)
{
    this->setGeometry(x, y, w, h);
}

void Label::SetTextSize(int size)
{
    QFont font = this->font();
    font.setPointSize(size);
    this->setFont(font);
}

void Label::SetIcon(const QString& path)
{
    QPixmap pixmap(path);

    this->setPixmap(pixmap);
    this->setScaledContents(true);
    this->resize(pixmap.width(), pixmap.height());
    this->setFixedSize(50, 50);
}

void Label::SetIconSize(int width, int height)
{
    this->setFixedSize(width, height);
}

void Label::SetTextToCenter()
{
    this->setAlignment(Qt::AlignCenter);
}