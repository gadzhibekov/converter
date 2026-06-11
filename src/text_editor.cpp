#include "text_editor.h"
#include "main_window.h"

#include <QFont>
#include <QObject>

TextEditor::TextEditor()
{
    this->setFixedSize(800, 800);
    this->setWindowTitle("Source Text Editor");

    textEditor      = new QTextEdit(this);
    back            = new Button(this, [this](){Back();});
    decreaseText    = new Button(this, [this](){DecreaseText();});
    increaseText    = new Button(this, [this](){IncreaseText();});

    textEditor->setGeometry(0, 0, 800, 800);
    back->SetGeometry(800 - 35, 800 - 35, 30, 30);
    decreaseText->SetGeometry(800 - 35 - 35, 800 - 35, 30, 30);
    increaseText->SetGeometry(800 - 35 - 35 - 35, 800 - 35, 30, 30);

    back->SetText("B");
    decreaseText->SetText("-");
    increaseText->SetText("+");

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