#include "settings_window_items.h"

SettingsWindowItemInformation::SettingsWindowItemInformation(QWidget* parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 1000, 500);

    title               = new Label(this);
    information         = new Label(this);

    title->SetText("LaTeX & MarkDown Конвертер");
    information->SetText(
          (QString)"Данная программа использует утилиту pandoc для конвертации LaTeX и MarkDown кодов в читаемый pdf формат.\n"
        + (QString)"Исходники программы защищены лицензией MIT более подробно с этим можно ознакомиться на третьей вкладе.\n"
        + (QString)"Перед началом убедитесь, что у вас скачана утилита pandoc и его модули.\nСкачать их можно введя соответствующую команду в bash для дистрибутивов основанных на Ubuntu.\n\n"
        + (QString)"sudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y"
        + (QString)"\n\nКоманду можно скопировать в буфер обмена нажав на кнопку 'Скопировать' ниже."
    );

    title->SetTextToCenter();
    information->SetTextToCenter();

    title->SetGeometry(0, 60, 1000, 50);
    information->SetGeometry(0, 120, 1000, 200);

    title->SetTextSize(30);
    information->SetTextSize(13);

    copyCommandButton   = new Button(this, [this](){CopyCommand();});
    copyCommandButton->setText("Скопировать");
    copyCommandButton->setGeometry(400, 330, 200, 30);
}

void SettingsWindowItemInformation::CopyCommand()
{
    ToClipboard("sudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y");
}


SettingsWindowItemUpdate::SettingsWindowItemUpdate(QWidget* parent) : QWidget(parent)
{
    
}

SettingsWindowItemLicense::SettingsWindowItemLicense(QWidget* parent) : QWidget(parent)
{
    
}