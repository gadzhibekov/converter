#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <QStandardPaths>
#include <QString>
#include <QDir>

static int version = 7;
static QString converterDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/LatexMarkdownConverterData";

bool CopyDirectoryToAppDir(const QString& sourceDirPath);
void CreateDir(const QString& directory);
bool IsDirExists(const QString& directory);
void RemoveDir(const QString& directory);
QString ReadAllFile(const QString& filePath);
int ConverQstrToInt(const QString& str);
void RemoveFile(const QString& path);
void ConvertLatexToPdf();
void ToClipboard(const QString& data);
QString FromClipboard();

#endif // UTILS_H