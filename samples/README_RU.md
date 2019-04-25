# Образцы
[English](README.md) | [Русский](README_RU.md)

## Структура каталога
		database	Базы данных, необходимые для отчетов
		reports		Файлы отчетов

## Примечание по структуре каталога отчетов
Имя родительской папки файла отчета обозначает имя базы данных, требуемой для него.

## Описание образцов
### image
		sample.imagefromdb.qreport		демонстрация загрузки изображений из базы данных в отчет

### main
		sample.graphics.qreport			демонстрация графических элементов
		sample.groupfooter.qreport		демонстрация работы тегов "group" и "groupfooter"
		sample.groupheader.qreport		демонстрация работы тегов "group" и "groupheader"
		sample.image.qreport			демонстрация загрузки изображений из ЛФС
		sample.list.qreport			простой вывод списка данных
		sample.listleftjoin.qreport		вывод списка данных с запросом, содержащим left outer join
		sample.manual.qreport			вывод списка данных в табличном формате
		sample.multigroup.qreport		демонстрация вложенной группировки
		sample.summary.qreport			демонстрация работы тега "summary"
		sample.variable.qreport			демонстрация работы тега variable
		sample.added_plus_row.qreport		для вычисления выражений в теге CDATA
		sample.students_onlyPM.qreport		запрос с оператором like

### test, test-images
Данные отчеты требуются для тестов покрытия Coverage.
