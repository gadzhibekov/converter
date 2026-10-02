#include "config.h"

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>

#include <iostream>
#include <cstdlib>

ConfigData::ConfigData( const QString& theme, 
                        const QString& language, 
                        const QString& sourceText, 
                        const QString& showAgain)
                    :   theme(theme), language(language), sourceText(sourceText), showAgain(showAgain)
                    {}


ConfigData Config::Read()
{
    if (!(QFile(STANDART_TEMP_DIR + static_cast<QString>(CONFIG_FILE_NAME)).exists()))
    {
        QString command = static_cast<QString>("touch ") + STANDART_TEMP_DIR + static_cast<QString>(CONFIG_FILE_NAME);

        std::system(command.toStdString().c_str());

        return ConfigData("dark", "lezgian", "", "yes");
    }

    QString file_path = STANDART_TEMP_DIR + static_cast<QString>(CONFIG_FILE_NAME);
    QFile file(file_path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QByteArray      data = file.readAll();
        QJsonDocument   doc  = QJsonDocument::fromJson(data);

        if (doc.isObject()) 
        {
            QJsonObject obj         = doc.object();
            QString     theme       = obj["theme"].toString();
            QString     language    = obj["language"].toString();
            QString     sourceText  = obj["sourceText"].toString();
            QString     showAgain   = obj["showAgain"].toString();

            if (!(theme     == "light"   || theme     == "dark"))                             theme = "dark";
            if (!(language  == "lezgian" || language  == "russian" || language == "english")) language = "lezgian";
            if (!(showAgain == "yes"     || showAgain == "no"))                               showAgain = "yes";

            return ConfigData(theme, language, sourceText, showAgain);
        }

        file.close();
    }

    return ConfigData("dark", "lezgian", "", "yes");
}

void Config::Write(ConfigData config_data)
{
    QJsonObject obj;
    
    obj["theme"]        = config_data.theme;
    obj["language"]     = config_data.language;
    obj["sourceText"]   = config_data.sourceText;
    obj["showAgain"]    = config_data.showAgain;

    QJsonDocument doc(obj);
    QFile file(STANDART_TEMP_DIR + static_cast<QString>(CONFIG_FILE_NAME));

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
    {
        file.write(doc.toJson());
        file.close();
    }
}