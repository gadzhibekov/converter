#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <QStandardPaths>
#include <QString>
#include <QDir>

static int      version             = 200;
static QString  converterDataDir    = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/LatexMarkdownConverterData";
static QString  aboutVersion        = "This version had a settings menu and a new design";

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
double ConvertToDecimal(int number);

#endif // UTILS_H