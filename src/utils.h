#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <QStandardPaths>
#include <QString>
#include <QDir>

static int      version             = 210;
static QString  converterDataDir    = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/LatexMarkdownConverterData";

void OpenUrl(const QString &url);
bool CopyDirectoryToAppDir(const QString& sourceDirPath);
void CreateDir(const QString& directory);
bool IsDirExists(const QString& directory);
void RemoveDir(const QString& directory);
QString ReadAllFile(const QString& filePath);
int ConverQstrToInt(const QString& str);
void RemoveFile(const QString& path);
void LatexToPdf();
void MarkdownToPdf();
void ToClipboard(const QString& data);
QString FromClipboard();
QString ConvertToDecimal(int number);

#endif // UTILS_H