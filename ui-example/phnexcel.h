#ifndef PHNEXCEL_H
#define PHNEXCEL_H

#include <QtWidgets/QTableWidget>

#ifdef _WIN32
  #include <windows.h>
#endif

#include "libxl.h"

#include <QString>

using namespace libxl;

class phnExcel
{
public:

    static void phnAddHeaderFile(Book* book, Sheet *sheet);

    static void phnAddDetailFile(QTableWidget *tableWidget, Book* book, Sheet *sheet);

};

#endif // PHNEXCEL_H
