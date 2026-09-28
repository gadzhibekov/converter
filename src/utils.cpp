#include "utils.h"
#include "main_window.h"
#include "message_box.h"
#include "layout.h"

#include <QCoreApplication>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>

#include <string>

void OpenUrl(const QString &url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void CreateDir(const QString& directory)
{
    QDir dir;
    dir.mkpath(directory); 
}

bool IsDirExists(const QString& directory)
{
    QDir dir;
    return dir.exists(directory);
}

void RemoveDir(const QString& directory)
{
    QDir dir(directory);
    
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
    }
    
    
    QString newAppImage = sourceDirPath + "/Converter.AppImage";
    if (!QFile::exists(newAppImage))
    {
        return false;
    }
    
    QString oldAppImage = appDirPath + "/Converter.AppImage";
    if (QFile::exists(oldAppImage))
    {
        if (!QFile::remove(oldAppImage))
        {
            return false;
        }
    }
    
    if (!QFile::copy(newAppImage, oldAppImage))
    {
        return false;
    }
    
    return true;
}

void RemoveFile(const QString& path)
{
    QFile::remove(path);
}

void ConvertLatexToPdf()
{
    CreateDir(converterDataDir);

    QFile file(converterDataDir + "/" + MainWindow::convertData[0] + ".tex");

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(MainWindow::convertData[2].toUtf8());
        file.close();
    }
    else
    {
        MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[16]);
        RemoveDir(converterDataDir);
        return;
    }

    QString inputFile = converterDataDir + "/" + MainWindow::convertData[0] + ".tex";
    QString outputDir = MainWindow::convertData[1] + "/";
    QString command = QString("xelatex -output-directory=\"%1\" -interaction=nonstopmode \"%2\"")
                     .arg(outputDir)
                     .arg(inputFile);

    int converResult = std::system(command.toUtf8().constData());

    RemoveFile(MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + ".aux");
    RemoveDir(converterDataDir);

    if(converResult)
    {
        MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[17] 
                                        + MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + 
                                        GetCurrentLayout()[18]);
    }
    else
    {
        MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[19]
                                        + MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + ".pdf\n-"
                                        + MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + ".log\n\n"
                                        + GetCurrentLayout()[20]);
    }
}

void ConvertMarkdownToPdf()
{
    CreateDir(converterDataDir);

    QFile file(converterDataDir + "/" + MainWindow::convertData[0] + ".md");

    if (file.open(QIODevice::WriteOnly))
    {
        file.write(MainWindow::convertData[2].toUtf8());
        file.close();
    }
    else
    {
        MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[21]);
        RemoveDir(converterDataDir);
        return;
    }

    QString inputFile = converterDataDir + "/" + MainWindow::convertData[0] + ".md";
    QString outputFile = MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + ".pdf";
    
    QString command = QString("pandoc \"%1\" -o \"%2\" --pdf-engine=xelatex -V mainfont=\"DejaVu Serif\"")
                     .arg(inputFile)
                     .arg(outputFile);

    int convertResult = std::system(command.toUtf8().constData());

    RemoveDir(converterDataDir);

    if(convertResult)
    {
        MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[22] + "sudo apt install pandoc -y");
    }
    else
    {
        MessageBox::Message(CRITICAL_ICON, GetCurrentLayout()[23] + outputFile);
    }
}

void ToClipboard(const QString& data)
{
    QApplication::clipboard()->setText(data);
}

QString FromClipboard()
{
    return QApplication::clipboard()->text();
}

QString ConvertToDecimal(int number)
{
    std::string numStr = std::to_string(number);
    std::string result;
    
    for (size_t i = 0; i < numStr.length(); i++)
    {
        result += numStr[i];
        if (i < numStr.length() - 1)
        {
            result += '.';
        }
    }
    
    return QString::fromStdString(result);
}