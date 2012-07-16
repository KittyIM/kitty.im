#ifndef UTILS_H
#define UTILS_H

#include "utils_global.h"

#include <QtCore/QDir>

namespace Utils
{
	// function taken from http://john.nachtimwald.com/2010/06/08/qt-remove-directory-and-its-contents/
	bool UTILS_EXPORT rmPath(const QString &pathName)
	{
		bool result = true;
		QDir dir(pathName);

		if(dir.exists(pathName)) {
			foreach(const QFileInfo &info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
				if(info.isDir()) {
					result = rmPath(info.absoluteFilePath());
				} else {
					result = QFile::remove(info.absoluteFilePath());
				}

				if(!result) {
					return result;
				}
			}

			result = dir.rmdir(pathName);
		}

		return result;
	}
}

#endif // UTILS_H
