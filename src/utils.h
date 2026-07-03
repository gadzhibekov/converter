#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <QStandardPaths>
#include <QString>
#include <QDir>

static int      version             = 201;
static QString  converterDataDir    = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/LatexMarkdownConverterData";
static QString  aboutVersion        = "This version has been updated with improved interface elements";

bool CopyDirectoryToAppDir(const QString& sourceDirPath);
void CreateDir(const QString& directory);
bool IsDirExists(const QString& directory);
void RemoveDir(const QString& directory);
QString ReadAllFile(const QString& filePath);
int ConverQstrToInt(const QString& str);
void RemoveFile(const QString& path);
void ConvertLatexToPdf();
void ConvertMarkdownToPdf();
void ToClipboard(const QString& data);
QString FromClipboard();
QString ConvertToDecimal(int number);

#endif // UTILS_H