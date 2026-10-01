#include "layout.h"
#include "label.h"
#include "button.h"
#include "line_edit.h"

#include <QMainWindow>

QString                                  currentLayout  = "lezgian";
std::vector<std::pair<QString, void *>>  layoutObjPtrs;

std::vector<QString> lezgianLanguagePackDynamic = {
    "Формат хкягъун",
    "Гиьхьтин форматда документ туькlуьриз кlанзава?",
    "Туькlуьр хьайи файл ",
    ".pdf\nжеда директорияда \n",
    "Гьиниз вегьедатlа къалура",
    "Команда\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex fonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\nкопия авуна буфер обменадиз",
    "Гъалатl хьана файл дегишардайла",
    "Цlийивилерихъ галаз кlвалахун",
    "Программа цlийи хьана ",
    ". Дегишвилер жеда программа хкудна кутур хъувуйла.",
    "Хкуда кутур хъувун",
    "Гъалатl хьана цlийивилер эцигдайла",
    "Квез цlийивилер эцигун герек туш",
    "Сервердик экежиз хьанач.",
    "Экуь дегишвилер эциг хьана",
    "Мичlи дегишвилер эциг хьана",
    "Вахтунин файл туькlуьриз хьанач.",
    "Са вуч ятlани чlурукl хьана:\nИ файлдин къене вуч аватlа килига:\n",
    ".log, эгер гьахьтин тlвар алай файл квез аваштlа, pandoc лугьудай утилита эцигун лазим я.",
    "Агалкьунралди. Файлар рас хьана:\n-",
    "Эгер акъатай PDF-файлда гъалатlар аваз хьаитlа квегай вири логдиз килиг жеда .log файлда.",
    "Вахтунин файл туькlуьриз хьанач.",
    "Са вуч ятlани чlурукl хьана:\nКилига квез pandoc лугьудай утилита аватlта.\nЭцигун: ",
    "Агалкьунралди. Файлар рас хьана:\n-",
    "Цlийи эциг хьайи папка ахъайна ва гьана авай Converter.Appimage лугьудай файл къачуна, куь куьгьне гьахьтин тlвар алай файлдихъ галаз дегиш авун лазим я.\nЭгер квез куь ахъа хьайи браузерда 404 галатl акъатзватlа им лагьай гаф я хьи квез эхиримжи программадин цlийивилер ава",
    "Къавкьаздин Алпандин Лезги чlалал гьелелиг дегиш айиз жезвач",
    "Программа Лезги чlалал дегиш хьана",
    "Программа Урус чlалал дегиш хьана",
    "Программа Английский чlалал дегиш хьана"
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
    "Что-то пошло не так:\nУбедитесь, что у вас установлена ​​утилита pandoc.\nУстановить: ",
    "Успешно. Созданы файлы:\n-",
    "Распакуйте скачанные файлы и замените текущий файл Converter.Appimage новым.\nЕсли вы получите ошибку 404, это означает, что у вас уже установлена ​​последняя версия программы.",
    "Перевод на \"Лезгинский (Кавказская Албания)\" временно недоступен",
    "Вы переключились на Лезгинский язык",
    "Вы переключились на Русский язык",
    "Вы переключились на Английский язык"
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
    "Something went wrong:\nMake sure you have the pandoc utility installed\nInstalling: ",
    "Success. File is created:\n-",
    "Extract the downloaded files and replace your current Converter.Appimage with the new one.\nIf you get a 404 error, it means you already have the latest version of the program.",
    "Translation into \"Lezgian (Caucasian Albania)\" is temporarily unavailable.",
    "Switched to Lezgian language",
    "Switched to Russian language",
    "Switched to English"
};

std::vector<QString> lezgianLanguagePack = {
    "LaTeX ва MarkDown форматриз\nдегишарзавай программа",
    "LaTeX ва MarkDown форматриз\nдегишарзавай программа",
    "Сифте текст",
    "Гьиниз вегьеда",
    "Дегиш авун",
    "Сифте текст дегишарун",
    "Файл вегьедай чка хкягъун",
    "Гьиниз вегьедатlада къалур",
    "Файлдин тlвар кхихь",
    "Сазламишунар",
    "LaTeX ва MarkDown форматриз дегишарзавай программа",
    "Программади ислемишзава pandoc лугьудай утилита LaTeX ва MarkDown форматар PDF лугьудай, регьятдиз кlелиз жедай,\nформатдиз элкъуьруьн патал. Программа ибарат авур кхьинар MIT лугьдай эхтиярдик акатхава. Гзаф гьа эхтиярдикая\nквегай пуд лагьай чарчел кlелиз жеда. Ислемишиз башламишталди pandoc, ва гьакlни адахъ галай шейэр, аватlа килигун\nлазим я. Авачиз хьаитlа квегай абур эцигиз жеда герек команда bash-да кхьена, тек са Ubuntu-дилай хьаи дистрибутивриз.\n\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\n\nКоманда квегай копия айиз жеда кlаник квай \"Копия авун\" кнопкадал элисна",
    "Копия авун",
    "Цlйий вилер эцигун",
    "И сефер программа цlийи чlаларал давамар авуна:\nЛезги, Урус ва Инглис чlалар.",
    "MIT Эхтияр",
    "MIT Эхтияр",
    "<a href=\"https://github.com/ueberdosis/pandoc/blob/main/LICENSE.md\"> Pandoc эхтияр</a>",
    "<a href=\"https://github.com/gadzhibekov/converter/blob/main/LICENSE\"> LaTeX & MarkDown эхтияр</a>",
    "Экуь дегишвилер",
    "Мичlи дегишвилер",
    "Вилериз тади гун тавур патал программада ава мичlи ва гакlни\nэкуь дегишвилер. Йифен вахтунда мичlи дегишвилер ислемишун лазим я,\nюкъуз - экуь дегишвилер",
    "Къавкьаздин Алпандин\nЛезги чlал",
    "Лезги чlал",
    "Урус чlал",
    "Инглис чlал",
    "Квегай квез кlандай чlал эцигизжеда жеда.\nИсягьта прогрммада авайди тек са пуд чlал я.\nАмма\"Къавкьаздин Алпандин Лезги чlал\" са арадилай давамар жеда."
};

std::vector<QString> russianLanguagePack = {
    "Конвертер для LaTeX и MarkDown",
    "Конвертер для LaTeX и MarkDown",
    "Исходный текст",
    "Сохранить как",
    "Сконвертировать",
    "Редактор текста",
    "Настройки для сохранения файла",
    "Укажите директорию",
    "Укажите название файла",
    "Настройки",
    "Конвертер для LaTeX и MarkDown",
    "Эта программа использует утилиту pandoc для преобразования кодов LaTeX и MarkDown в читаемый формат PDF.\nИсходный код программы защищен лицензией MIT. Более подробную информацию можно найти на третьей вкладке.\nПрежде чем начать, убедитесь, что вы загрузили утилиту pandoc и её модули.\nВы можете загрузить их, введя соответствующую команду в bash для дистрибутивов на основе Ubuntu.\n\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\n\nКоманду можно скопировать, нажав на кнопку \"Скопировать\" снизу.",
    "Скопировать",
    "Загрузить обновление",
    "В этой версии была добавлена поддержка разных языков:\nЛезгинский, Русский и Анлийский языки.",
    "Лицензия MIT",
    "Лицензия MIT",
    "<a href=\"https://github.com/ueberdosis/pandoc/blob/main/LICENSE.md\"> Лицензия на Pandoc</a>",
    "<a href=\"https://github.com/gadzhibekov/converter/blob/main/LICENSE\"> Лицензия на LaTeX & MarkDown</a>",
    "Светлая тема",
    "Тёмная тема",
    "Для снижения нагрузки на глаза программа теперь поддерживает как темную, так и светлую темы оформления.\nВечером рекомендуется использовать темную тему, а днем ​​— светлую.",
    "Лезгинский\nКавказская Албания",
    "Лезгинский",
    "Русский",
    "Английский",
    "Можете переключиться на удобную вам раскладку языка.\nВ данный момент программа поддерижвает только три языка.\n\"Лезгинский язык (Кавказская Албания)\" будет добавлена позже."
};

std::vector<QString> englishLanguagePack = {
    "LaTeX & MarkDown Converter",
    "LaTeX & MarkDown Converter",
    "Sourse text",
    "Save as",
    "Convert",
    "Text Editor",
    "Options for file saving",
    "Specify the directory",
    "Specify the file name",
    "Settings",
    "LaTeX & MarkDown Converter",
    "This program uses the pandoc utility to convert LaTeX and MarkDown codes into readable PDF format.\nThe program's source code is protected by the MIT license; more details can be found in the third tab.\nBefore you begin, make sure that you have downloaded the pandoc utility and its modules.\nYou can download them by entering the appropriate command in bash for Ubuntu-based distributions.\n\nsudo apt install pandoc texlive-latex-base texlive-latex-extra texlive-fonts-recommended texlive-xetex \nfonts-dejavu fonts-dejavu-core fonts-liberation texlive-lang-cyrillic texlive-full -y\n\nThe command can be copied to the clipboard by clicking the \"Copy\" button below.",
    "Copy",
    "Load update",
    "Support for multiple languages ​​has been added to this version:\nLezgian, Russian, and English.",
    "MIT License",
    "MIT License",
    "<a href=\"https://github.com/ueberdosis/pandoc/blob/main/LICENSE.md\"> Pandoc License</a>",
    "<a href=\"https://github.com/gadzhibekov/converter/blob/main/LICENSE\"> LaTeX & MarkDown Converter License</a>",
    "Light Theme",
    "Dark Theme",
    "To reduce eye strain, the program now supports both dark and light themes.\nIt's recommended to use the dark theme in the evening\nand the light theme during the day.",
    "Lezgian\nCaucasian Albania",
    "Lezgian",
    "Russian",
    "English",
    "You can switch to your preferred language layout.\nCurrently, the program supports only three languages.\n\"Lezgian (Caucasian Albania)\" will be added later."
};

std::vector<QString> GetCurrentLayout()
{
    if (currentLayout == "lezgian") return lezgianLanguagePackDynamic;
    if (currentLayout == "russian") return russianLanguagePackDynamic;
    if (currentLayout == "english") return englishLanguagePackDynamic;

    return englishLanguagePackDynamic;
}

void Translate2Lezgian()
{
    currentLayout = "lezgian";

    for (size_t i = 0; i < layoutObjPtrs.size(); ++i)
    {
        if (layoutObjPtrs[i].first == "MainWindow")             static_cast<QMainWindow *>(layoutObjPtrs[i].second)->setWindowTitle(lezgianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Widget")                 static_cast<QWidget *>(layoutObjPtrs[i].second)->setWindowTitle(lezgianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Label")                  static_cast<Label *>(layoutObjPtrs[i].second)->SetText(lezgianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "Button")                 static_cast<Button *>(layoutObjPtrs[i].second)->SetText(lezgianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEdit")               static_cast<LineEdit *>(layoutObjPtrs[i].second)->SetText(lezgianLanguagePack[i]);
        if (layoutObjPtrs[i].first == "LineEditPlaceHolder")    static_cast<LineEdit *>(layoutObjPtrs[i].second)->setPlaceholderText(lezgianLanguagePack[i]);
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