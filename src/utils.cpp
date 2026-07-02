#include "utils.h"
#include "main_window.h"

#include <QCoreApplication>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QClipboard>

#include <iostream>
#include <string>

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
        QMessageBox::critical(nullptr, "Error", "Failed to create temporary file for writing");
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
        QMessageBox::critical(nullptr, "Conversion result", "something went wrong:\nLook at the contents of the file" 
                                        + MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + 
                                        ".log, If you don't have such a file, make sure you have the pandoc utility installed.");
    }
    else
    {
        QMessageBox::information(nullptr, "Conversion result", "Success. Files created:\n-" 
                                        + MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + ".pdf\n-"
                                        + MainWindow::convertData[1] + "/" + MainWindow::convertData[0] + ".log\n\n"
                                        + "If there is something wrong with the resulting .pdf file, the entire conversion log can be viewed in the .log file.");
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
        QMessageBox::critical(nullptr, "Error", "Failed to create temporary file for writing");
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
        QMessageBox::critical(nullptr, "Conversion result", "Something went wrong:\n"
                                        "Make sure you have the pandoc utility installed\n\n"
                                        "Installing:\n"
                                        "sudo apt install pandoc -y");
    }
    else
    {
        QMessageBox::information(nullptr, "Conversion result", "Success. File is created:\n-" 
                                        + outputFile);
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

double ConvertToDecimal(int number)
{
    int digits = 0;
    int temp = number;
    while (temp > 0)
    {
        temp /= 10;
        digits++;
    }
    
    return number / std::pow(10.0, digits - 1);
}