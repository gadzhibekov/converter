#include "text_editor.h"
#include "main_window.h"
#include "utils.h"

#include <QFont>
#include <QObject>

TextEditor::TextEditor()
{
    this->setFixedSize(800, 800);
    this->setWindowTitle("Text Editor");
    this->setStyleSheet(ReadAllFile("../styles/editor.css"));

    textEditor      = new QTextEdit(this);
    back            = new Button(this, [this](){Back();});
    decreaseText    = new Button(this, [this](){DecreaseText();});
    increaseText    = new Button(this, [this](){IncreaseText();});

    textEditor->setGeometry(0, 0, 800, 800);
    back->SetGeometry(5, 800 - 40, 35, 35);
    decreaseText->SetGeometry(800 - 40, 800 - 40, 35, 35);
    increaseText->SetGeometry(800 - 40 - 40, 800 - 40, 35, 35);

    back->SetIcon("../res/back.png");
    increaseText->SetIcon("../res/plus.png");
    decreaseText->SetIcon("../res/minus.png");

    back->SetIconSize(35, 35);
    increaseText->SetIconSize(35, 35);
    decreaseText->SetIconSize(35, 35);

    back->setStyleSheet(ReadAllFile("../styles/button.css"));
    decreaseText->setStyleSheet(ReadAllFile("../styles/button.css"));
    increaseText->setStyleSheet(ReadAllFile("../styles/button.css"));

    QObject::connect(textEditor, &QTextEdit::textChanged, this, &TextEditor::GetTextSlot);

    Hide();
}

void TextEditor::GetTextSlot()
{
    MainWindow::convertData[2] = GetText();
}

QString TextEditor::GetText() const
{
    return this->textEditor->toPlainText();
}

void TextEditor::IncreaseText()
{
    QFont font = textEditor->font();
    font.setPointSize(textEditor->font().pointSize() + 1);
    textEditor->setFont(font);
}

void TextEditor::DecreaseText()
{
    QFont font = textEditor->font();
    font.setPointSize(textEditor->font().pointSize() - 1);
    textEditor->setFont(font);
}

void TextEditor::Back()
{
    this->Hide();
}

void TextEditor::Show()
{
    this->show();
}

void TextEditor::Hide()
{
    this->hide();
}