 # Структура
 ### samples/database
В этой папке находятся базы данных.
### samples/reports 
В этой папке находятся примеры отчетов. Логика структуры папки reports следующая: отчеты располагаются в папках с названием базы данных, для которых они написаны.

# Описание работы примеров
### samples/reports/image
+ sample.imagefromdb.qreport - демонстрация загрузки изображений из базы данных в отчет.
### samples/reports/main
+ sample.graphics.qreport - демонстрация графических элементов;
+ sample.groupfooter.qreport - демонстрация работы тегов group и groupfooter;
+ sample.groupheader.qreport - демонстрация работы тегов group и groupheader;
+ sample.image.qreport - демонстрация загрузки изображений из ЛФС;
+ sample.list.qreport - простой вывод списка данных;
+ sample.listleftjoin.qreport - вывод списка данных с запросом, содержащим leftjoin;
+ sample.manual.qreport - вывод списка данных в табличном формате;
+ sample.multigroup.qreport - демонстрация вложенной группировки;
+ sample.summary.qreport - вывод списка данных с подведением итогов;
+ sample.variable.qreport - демонстрация работы тега variable.
+ sample.added_plus_row.qreport - для вычисления выражений в теге CDATA;
+ sample.students_onlyPM.qreport - запрос с оператором like;
### samples/reports/test, samples/reports/test-images
+ файлы, расположенные в этих директориях, нужны для coverage.
