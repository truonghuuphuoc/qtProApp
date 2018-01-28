#include "phnexcel.h"


void phnExcel::phnAddHeaderFile(Book* book, Sheet *sheet)
{
    Font* font = book->addFont();
    font->setColor(COLOR_BLACK);
    font->setBold(true);
    font->setSize(11);
    Format* boldFormat = book->addFormat();
    boldFormat->setAlignH(ALIGNH_CENTER);
    boldFormat->setAlignV(ALIGNV_CENTER);
    boldFormat->setFont(font);
    boldFormat->setWrap(true);
    boldFormat->setBorder(BORDERSTYLE_THIN);


    Font* font_header = book->addFont();
    font_header->setColor(COLOR_BLACK);
    font_header->setBold(true);
    font_header->setSize(16);
    Format* boldHeader = book->addFormat();
    boldHeader->setAlignH(ALIGNH_LEFT);
    boldHeader->setAlignV(ALIGNV_CENTER);
    boldHeader->setFont(font_header);

    sheet->writeStr(1, 0, QString("BẢNG KẾT QUẢ").toStdWString().c_str(), boldHeader);

    sheet->writeStr(3, 0, QString("STT").toStdWString().c_str(), boldFormat);
    sheet->writeStr(3, 1, QString("Đồng chí").toStdWString().c_str(), boldFormat);
    sheet->writeStr(3, 2, QString("Bệ").toStdWString().c_str(), boldFormat);
    sheet->writeStr(3, 3, QString("Bia số 4").toStdWString().c_str(), boldFormat);
    sheet->writeStr(3, 7, QString("Bia số 7").toStdWString().c_str(), boldFormat);
    sheet->writeStr(3, 11,QString("Bia số 8").toStdWString().c_str(), boldFormat);
    sheet->writeStr(3, 15,QString("Tổng").toStdWString().c_str(), boldFormat);
    sheet->writeStr(3, 16,QString("Loại").toStdWString().c_str(), boldFormat);

    sheet->writeStr(4, 3, QString("Lần 1").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 4, QString("Lần 2").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 5, QString("Lần 3").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 6, QString("Tổng").toStdWString().c_str(), boldFormat);

    sheet->writeStr(4, 7, QString("Lần 1").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 8, QString("Lần 2").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 9, QString("Lần 3").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 10,QString("Tổng").toStdWString().c_str(), boldFormat);


    sheet->writeStr(4, 11, QString("Lần 1").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 12, QString("Lần 2").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 13, QString("Lần 3").toStdWString().c_str(), boldFormat);
    sheet->writeStr(4, 14, QString("Tổng").toStdWString().c_str(), boldFormat);

    sheet->setMerge(3,4, 0, 0);
    sheet->setMerge(3,4, 1, 1);
    sheet->setMerge(3,4, 2, 2);
    sheet->setMerge(3,3, 3, 6);
    sheet->setMerge(3,3, 7, 10);
    sheet->setMerge(3,3, 11, 14);
    sheet->setMerge(3,4, 15, 15);
    sheet->setMerge(3,4, 16, 16);
}

void phnExcel::phnAddDetailFile(QTableWidget *tableWidget, Book* book, Sheet *sheet)
{
    QTableWidgetItem *item;
    QString sum, str_index;
    int startIndex = 5;
    int nameMaxLength = 0;

    Font* font = book->addFont();
    font->setColor(COLOR_BLACK);
    font->setSize(11);
    Format* boldFormat = book->addFormat();
    boldFormat->setAlignH(ALIGNH_CENTER);
    boldFormat->setAlignV(ALIGNV_CENTER);
    boldFormat->setFont(font);
    boldFormat->setWrap(true);
    boldFormat->setBorder(BORDERSTYLE_THIN);

    Format* boldHeader = book->addFormat();
    boldHeader->setAlignH(ALIGNH_LEFT);
    boldHeader->setAlignV(ALIGNV_CENTER);
    boldHeader->setFont(font);
    boldHeader->setBorder(BORDERSTYLE_THIN);


    for(int index = 0; index < tableWidget->rowCount(); index ++)
    {
        str_index = QString("%1").arg(startIndex + 1, 0, 10, QChar('0'));

        //STT
        sheet->writeNum(startIndex, 0, index + 1, boldFormat);

        //Ten
        item = tableWidget->item(index, 0);
        if(item->text().length() > nameMaxLength)
        {
            nameMaxLength = item->text().length();
        }
        sheet->writeStr(startIndex, 1, item->text().toStdWString().c_str(), boldHeader);

        //Be
        item = tableWidget->item(index, 1);
        sheet->writeNum(startIndex, 2, item->text().toInt(), boldFormat);

        //BS4 - Lan 1
        item = tableWidget->item(index, 2);
        sheet->writeNum(startIndex, 3, item->text().toInt(), boldFormat);

        //BS4 - Lan 2
        item = tableWidget->item(index, 3);
        sheet->writeNum(startIndex, 4, item->text().toInt(), boldFormat);

        //BS4 - Lan 3
        item = tableWidget->item(index, 4);
        sheet->writeNum(startIndex, 5, item->text().toInt(), boldFormat);

        //BS4 - Tong
        sum = "SUM(D" + str_index + ":F" + str_index +")";
        sheet->writeFormula(startIndex, 6, sum.toStdWString().c_str(), boldFormat);


        //BS7 - Lan 1
        item = tableWidget->item(index, 5);
        sheet->writeNum(startIndex, 7, item->text().toInt(), boldFormat);

        //BS7 - Lan 2
        item = tableWidget->item(index, 6);
        sheet->writeNum(startIndex, 8, item->text().toInt(), boldFormat);

        //BS7 - Lan 3
        item = tableWidget->item(index, 7);
        sheet->writeNum(startIndex, 9, item->text().toInt(), boldFormat);


        //BS7 - Tong
        sum = "SUM(H" + str_index + ":J" + str_index +")";
        sheet->writeFormula(startIndex, 10, sum.toStdWString().c_str(), boldFormat);

        //BS8 - Lan 1
        item = tableWidget->item(index, 8);
        sheet->writeNum(startIndex, 11, item->text().toInt(), boldFormat);

        //BS8 - Lan 2
        item = tableWidget->item(index, 9);
        sheet->writeNum(startIndex, 12, item->text().toInt(), boldFormat);

        //BS8 - Lan 3
        item = tableWidget->item(index, 10);
        sheet->writeNum(startIndex, 13, item->text().toInt(), boldFormat);

        //BS8 - Tong
        sum = "SUM(L" + str_index + ":N" + str_index +")";
        sheet->writeFormula(startIndex, 14, sum.toStdWString().c_str(), boldFormat);

        //Tong
        sum = "SUM(G" + str_index + ",K" + str_index + ",O" + str_index +")";
        sheet->writeFormula(startIndex, 15, sum.toStdWString().c_str(), boldFormat);

        //Loai
        sum = "IF(P" + str_index + ">= 72, \"Giỏi\", IF(P" + str_index + " >= 59, \"Khá\",IF(P" + str_index + " >= 45, \"Đạt\", \"Không đạt\")))";
        sheet->writeFormula(startIndex, 16, sum.toStdWString().c_str(), boldFormat);

        startIndex += 1;
    }

    Font* fontResult = book->addFont();
    fontResult->setColor(COLOR_BLACK);
    fontResult->setSize(11);
    fontResult->setBold(true);

    Format* boldResult = book->addFormat();
    boldResult->setAlignH(ALIGNH_LEFT);
    boldResult->setAlignV(ALIGNV_CENTER);
    boldResult->setFont(fontResult);
    boldResult->setBorder(BORDERSTYLE_THIN);

    Format* boldValue = book->addFormat();
    boldValue->setAlignH(ALIGNH_CENTER);
    boldValue->setAlignV(ALIGNV_CENTER);
    boldValue->setFont(fontResult);
    boldValue->setBorder(BORDERSTYLE_THIN);
    boldValue->setNumFormat(NUMFORMAT_PERCENT_D2);;

    str_index = QString("%1").arg(startIndex, 0, 10, QChar('0'));;

    sum= "Giỏi";
    sheet->writeStr(startIndex + 1, 1, sum.toStdWString().c_str(), boldResult);
    sum = "COUNTIFS(P6:P" + str_index + ", \">= 72\",P6:P" + str_index +", \"<= 90\") / COUNTIF(P6:P" +str_index+", \">= 0\")";
    sheet->writeFormula(startIndex + 1, 2, sum.toStdWString().c_str(), boldValue);
    startIndex += 1;


    sum= "Khá";
    sheet->writeStr(startIndex + 1, 1, sum.toStdWString().c_str(), boldResult);
    sum = "COUNTIFS(P6:P" + str_index + ", \">= 59\",P6:P" + str_index +", \"<= 71\") / COUNTIF(P6:P" +str_index+", \">= 0\")";
    sheet->writeFormula(startIndex + 1, 2, sum.toStdWString().c_str(), boldValue);
    startIndex += 1;

    sum= "Đạt";
    sheet->writeStr(startIndex + 1, 1, sum.toStdWString().c_str(), boldResult);
    sum = "COUNTIFS(P6:P" + str_index + ", \">= 45\",P6:P" + str_index +", \"<= 58\") / COUNTIF(P6:P" +str_index+", \">= 0\")";
    sheet->writeFormula(startIndex + 1, 2, sum.toStdWString().c_str(), boldValue);
    startIndex += 1;


    sum= "Không đạt";
    sheet->writeStr(startIndex + 1, 1, sum.toStdWString().c_str(), boldResult);
    sum = "COUNTIFS(P6:P" + str_index + ", \">= 0\",P6:P" + str_index +", \"<= 44\") / COUNTIF(P6:P" +str_index+", \">= 0\")";
    sheet->writeFormula(startIndex + 1, 2, sum.toStdWString().c_str(), boldValue);
    startIndex += 1;

    sheet->setCol(1, 1, nameMaxLength + 5);
    sheet->setCol(16, 16, 20);
}
