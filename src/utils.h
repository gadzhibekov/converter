#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <QStandardPaths>
#include <QString>
#include <QDir>

static int version = 6;
static QString UpdatedDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/LatexMarkdownConverterData";

bool CopyDirectoryToAppDir(const QString& sourceDirPath);
void CreateUpdatedDataDir();
bool IsUpdatedDataDirExists();
void RemoveUpdatedDataDir();
QString ReadAllFile(const QString& filePath);
int ConverQstrToInt(const QString& str);

#endif // UTILS_H