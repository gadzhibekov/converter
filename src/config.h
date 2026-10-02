#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#define STANDART_TEMP_DIR   QStandardPaths::writableLocation(QStandardPaths::TempLocation)
#define CONFIG_FILE_NAME    "/lmc_configuration.json"

#include <QStandardPaths>
#include <QString>

class ConfigData
{
public:
    ConfigData() = default;
    ConfigData( const QString& theme, 
                const QString& language, 
                const QString& sourceText, 
                const QString& showAgain);

    QString                     theme;
    QString                     language;
    QString                     sourceText;
    QString                     showAgain;
};

class Config
{
public:
    static  void                Write(ConfigData config_data);
    static  ConfigData          Read();
};

#endif // CONFIG_H