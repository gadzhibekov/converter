#include "utils.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QTextStream>

void CreateUpdatedDataDir()
{
    QDir dir;
    dir.mkpath(UpdatedDataDir); 
}

bool IsUpdatedDataDirExists()
{
    QDir dir;
    return dir.exists(UpdatedDataDir);
}

void RemoveUpdatedDataDir()
{
    QDir dir(UpdatedDataDir);
    
    if (dir.exists())
    {
        dir.removeRecursively();
    }
}

QString ReadAllFile(const QString& filePath)
{
    QFile file(filePath);
    
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file:" << filePath;
        return QString();
    }
    
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    
    return content;
}

int ConverQstrToInt(const QString& str)
{
    return str.toInt();
}

bool CopyDirectoryToAppDir(const QString& sourceDirPath)
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString appImagePath = qEnvironmentVariable("APPIMAGE");
    
    if (!appImagePath.isEmpty())
    {
        QFileInfo appImageInfo(appImagePath);
        appDirPath = appImageInfo.absolutePath();
        qDebug() << "Running from AppImage, using path:" << appDirPath;
    }
    
    qDebug() << "Target directory:" << appDirPath;
    
    QString newAppImage = sourceDirPath + "/Converter.AppImage";
    if (!QFile::exists(newAppImage))
    {
        qDebug() << "Source AppImage does not exist:" << newAppImage;
        return false;
    }
    
    QString oldAppImage = appDirPath + "/Converter.AppImage";
    if (QFile::exists(oldAppImage))
    {
        if (!QFile::remove(oldAppImage))
        {
            qDebug() << "Failed to remove old AppImage:" << oldAppImage;
            return false;
        }
        qDebug() << "Removed old AppImage:" << oldAppImage;
    }
    
    if (!QFile::copy(newAppImage, oldAppImage))
    {
        qDebug() << "Failed to copy new AppImage";
        return false;
    }
    
    qDebug() << "Copied Converter.AppImage to:" << oldAppImage;
    
    return true;
}