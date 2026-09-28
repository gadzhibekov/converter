#include "layout.h"
#include "label.h"
#include "button.h"
#include "line_edit.h"

#include <QMainWindow>

QString                                  currentLayout      = "russian";
std::vector<std::pair<QString, void *>>  layoutObjPtrs;

std::vector<QString> lezgiLanguagePackDynamic = {
    "Выберите формат",
    "В каком формате вы хотите создать документ?",
    "Полученный файл ",
    ".pdf\nбудет сохранён в директорию \n",
    "Выберите папку",
    "Команда\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\nскопирована в буфер обмена",
    "Ошибка при замене файлов",
    "Работа с обновлениями",
    "Программа обновлена ​​до версии ",
    ". Измения вступят в силу после перезагрузки.",
    "Перезагрузить",
    "Ошибка при скачивании обновления",
    "У вас актуальная версия программы",
    "Не удалось установить соединение с сервером.",
    "Вы переключились на светлую тему",
    "Вы переключились на тёмную тему",
    "Не удалось создать временный файл для записи.",
    "Что-то пошло не так:\nПосмотрите на содержимое файла",
    ".log, Если у вас нет такого файла, убедитесь, что у вас установлена ​​утилита pandoc.",
    "Успешно. Созданы файлы:\n-",
    "Если в полученном PDF-файле обнаружены ошибки, полный журнал преобразования можно просмотреть в этом файле.log.",
    "Не удалось создать временный файл для записи.",
    "Что-то пошло не так:\nУбедитесь, что у вас установлена ​​утилита pandoc.\n\nУстановить:\n",
    "Успешно. Созданы файлы:\n-",
    "Распакуйте скачанные файлы и замените текущий файл Converter.Appimage новым.\n\nЕсли вы получите ошибку 404, это означает, что у вас уже установлена ​​последняя версия программы."
};

std::vector<QString> russianLanguagePackDynamic = {
    "Выберите формат",
    "В каком формате вы хотите создать документ?",
    "Полученный файл ",
    ".pdf\nбудет сохранён в директорию \n",
    "Выберите папку",
    "Команда\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\nскопирована в буфер обмена",
    "Ошибка при замене файлов",
    "Работа с обновлениями",
    "Программа обновлена ​​до версии ",
    ". Измения вступят в силу после перезагрузки.",
    "Перезагрузить",
    "Ошибка при скачивании обновления",
    "У вас актуальная версия программы",
    "Не удалось установить соединение с сервером.",
    "Вы переключились на светлую тему",
    "Вы переключились на тёмную тему",
    "Не удалось создать временный файл для записи.",
    "Что-то пошло не так:\nПосмотрите на содержимое файла",
    ".log, Если у вас нет такого файла, убедитесь, что у вас установлена ​​утилита pandoc.",
    "Успешно. Созданы файлы:\n-",
    "Если в полученном PDF-файле обнаружены ошибки, полный журнал преобразования можно просмотреть в этом файле.log.",
    "Не удалось создать временный файл для записи.",
    "Что-то пошло не так:\nУбедитесь, что у вас установлена ​​утилита pandoc.\n\nУстановить:\n",
    "Успешно. Созданы файлы:\n-",
    "Распакуйте скачанные файлы и замените текущий файл Converter.Appimage новым.\n\nЕсли вы получите ошибку 404, это означает, что у вас уже установлена ​​последняя версия программы."
};

std::vector<QString> englishLanguagePackDynamic = {
    "Select format",
    "What format would you like to create the document in?",
    "The resulting file ",
    ".pdf\nwill be saved in the directory \n",
    "Select a folder",
    "The command\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\nis copied to clipboard",
    "Failed to replace files",
    "Working with updates",
    "The program has been updated to version ",
    ". The changes will take effect after a reboot.",
    "Reboot",
    "Failed to download update",
    "You have the current version of the program",
    "Failed to establish connection to the server",
    "Switched to light theme",
    "Switched to dark theme",
    "Failed to create temporary file for writing",
    "Something went wrong:\nLook at the contents of the file",
    ".log, If you don't have such a file, make sure you have the pandoc utility installed.",
    "Success. Files created:\n-",
    "If there is something wrong with the resulting .pdf file, the entire conversion log can be viewed in the .log file.",
    "Failed to create temporary file for writing",
    "Something went wrong:\nMake sure you have the pandoc utility installed\n\nInstalling:\n",
    "Success. File is created:\n-",
    "Extract the downloaded files and replace your current Converter.Appimage with the new one.\n\nIf you get a 404 error, it means you already have the latest version of the program."
};

std::vector<QString> lezgiLanguagePack = {
    "Конвертер для LaTeX и MarkDown",
    "Конвертер для LaTeX и MarkDown",
    "Исходный текст",
    "Сохранить как",
    "Сконвертировать",
    "Настройки для сохранения файла",
    "Укажите директорию",
    "Укажите название файла",
    "Настройки",
    "Конвертер для LaTeX и MarkDown",
    "Эта программа использует утилиту pandoc для преобразования кодов LaTeX и MarkDown в читаемый формат PDF.\nИсходный код программы защищен лицензией MIT; более подробную информацию можно найти на третьей вкладке.\nПрежде чем начать, убедитесь, что вы загрузили утилиту pandoc и её модули.\nВы можете загрузить их, введя соответствующую команду в bash для дистрибутивов на основе Ubuntu.\n\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\n\nКоманду можно скопировать, нажав на кнопку \"Скопировать\" снизу",
    "Скопировать",
    "Обновить",
    "В этой версии были внесены небольшие измения, связанные с оптимизацией.",
    "Лицензия MIT",
    "Лицензия  MIT",
    "<a href=\"https://github.com/ueberdosis/pandoc/blob/main/LICENSE.md\"> Лицензия на Pandoc от Хенса Пегеля</a>",
    "<a href=\"https://github.com/gadzhibekov/converter/blob/main/LICENSE\"> Лицензия на LaTeX & MarkDown конвертер от Бейбалы Гаджибекова</a>",
    "Светлая тема",
    "Тёмная тема",
    "Для снижения нагрузки на глаза программа теперь поддерживает как темную, так и светлую темы оформления.\nВечером рекомендуется использовать темную тему, а днем ​​— светлую."
};

std::vector<QString> russianLanguagePack = {
    "Конвертер для LaTeX и MarkDown",
    "Конвертер для LaTeX и MarkDown",
    "Исходный текст",
    "Сохранить как",
    "Сконвертировать",
    "Настройки для сохранения файла",
    "Укажите директорию",
    "Укажите название файла",
    "Настройки",
    "Конвертер для LaTeX и MarkDown",
    "Эта программа использует утилиту pandoc для преобразования кодов LaTeX и MarkDown в читаемый формат PDF.\nИсходный код программы защищен лицензией MIT; более подробную информацию можно найти на третьей вкладке.\nПрежде чем начать, убедитесь, что вы загрузили утилиту pandoc и её модули.\nВы можете загрузить их, введя соответствующую команду в bash для дистрибутивов на основе Ubuntu.\n\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\n\nКоманду можно скопировать, нажав на кнопку \"Скопировать\" снизу.",
    "Скопировать",
    "Обновить",
    "В этой версии были внесены небольшие измения, связанные с оптимизацией.",
    "Лицензия MIT",
    "Лицензия  MIT",
    "<a href=\"https://github.com/ueberdosis/pandoc/blob/main/LICENSE.md\"> Лицензия на Pandoc от Хенса Пегеля</a>",
    "<a href=\"https://github.com/gadzhibekov/converter/blob/main/LICENSE\"> Лицензия на LaTeX & MarkDown конвертер от Бейбалы Гаджибекова</a>",
    "Светлая тема",
    "Тёмная тема",
    "Для снижения нагрузки на глаза программа теперь поддерживает как темную, так и светлую темы оформления.\nВечером рекомендуется использовать темную тему, а днем ​​— светлую."
};

std::vector<QString> englishLanguagePack = {
    "LaTeX & MarkDown Converter by Beibala Gadzhibekov",
    "LaTeX & MarkDown Converter",
    "Sourse text",
    "Save as",
    "Convert",
    "Options for file saving",
    "Specify the directory",
    "Specify the file name",
    "Settings",
    "LaTeX & MarkDown Converter",
    "This program uses the pandoc utility to convert LaTeX and MarkDown codes into readable PDF format.\nThe program's source code is protected by the MIT license; more details can be found in the third tab.\nBefore you begin, make sure that you have downloaded the pandoc utility and its modules.\nYou can download them by entering the appropriate command in bash for Ubuntu-based distributions.\n\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\n\nThe command can be copied to the clipboard by clicking the \"Copy\" button below.",
    "Copy",
    "Update",
    "Minor changes related to optimization were made in this version.",
    "MIT License",
    "MIT License",
    "<a href=\"https://github.com/ueberdosis/pandoc/blob/main/LICENSE.md\"> Pandoc License by Hans Pagel</a>",
    "<a href=\"https://github.com/gadzhibekov/converter/blob/main/LICENSE\"> LaTeX & MarkDown Converter License by Beibala Gadzhibekov</a>",
    "Light Theme",
    "Dark Theme",
    "To reduce eye strain, the program now supports both dark and light themes.\nIt's recommended to use the dark theme in the evening\nand the light theme during the day."
};

std::vector<QString> GetCurrentLayout()
{
    if (currentLayout == "lezgi")   return lezgiLanguagePackDynamic;
    if (currentLayout == "russian") return russianLanguagePackDynamic;
    if (currentLayout == "english") return englishLanguagePackDynamic;
}

void Translate2Lezgi()
{
    currentLayout = "lezgi";

    for (size_t i = 0; i < layoutObjPtrs.size(); ++i)
    {
        if (layoutObjPtrs[i].first == "MainWindow")             static_cast<QMainWindow *>(layoutObjPtrs[i].second)->setWindowTitle(lezgiLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Widget")                 static_cast<QWidget *>(layoutObjPtrs[i].second)->setWindowTitle(lezgiLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Label")                  static_cast<Label *>(layoutObjPtrs[i].second)->SetText(lezgiLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Button")                 static_cast<Button *>(layoutObjPtrs[i].second)->SetText(lezgiLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEdit")               static_cast<LineEdit *>(layoutObjPtrs[i].second)->SetText(lezgiLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEditPlaceHolder")    static_cast<LineEdit *>(layoutObjPtrs[i].second)->setPlaceholderText(lezgiLanguagePack[i]);
    }  
}

void Translate2Russian()
{
    currentLayout = "russian";

    for (size_t i = 0; i < layoutObjPtrs.size(); ++i)
    {
        if (layoutObjPtrs[i].first == "MainWindow")             static_cast<QMainWindow *>(layoutObjPtrs[i].second)->setWindowTitle(russianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Widget")                 static_cast<QWidget *>(layoutObjPtrs[i].second)->setWindowTitle(russianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Label")                  static_cast<Label *>(layoutObjPtrs[i].second)->SetText(russianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Button")                 static_cast<Button *>(layoutObjPtrs[i].second)->SetText(russianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEdit")               static_cast<LineEdit *>(layoutObjPtrs[i].second)->SetText(russianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEditPlaceHolder")    static_cast<LineEdit *>(layoutObjPtrs[i].second)->setPlaceholderText(russianLanguagePack[i]);
    }  
}

void Translate2English()
{
    currentLayout = "english";

    for (size_t i = 0; i < layoutObjPtrs.size(); ++i)
    {
        if (layoutObjPtrs[i].first == "MainWindow")             static_cast<QMainWindow *>(layoutObjPtrs[i].second)->setWindowTitle(englishLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Widget")                 static_cast<QWidget *>(layoutObjPtrs[i].second)->setWindowTitle(englishLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Label")                  static_cast<Label *>(layoutObjPtrs[i].second)->SetText(englishLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Button")                 static_cast<Button *>(layoutObjPtrs[i].second)->SetText(englishLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEdit")               static_cast<LineEdit *>(layoutObjPtrs[i].second)->SetText(englishLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEditPlaceHolder")    static_cast<LineEdit *>(layoutObjPtrs[i].second)->setPlaceholderText(englishLanguagePack[i]);
    }  
}