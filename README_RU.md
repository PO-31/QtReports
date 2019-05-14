# QtReports [![Стандарт языка](https://img.shields.io/badge/language-C++14-blue.svg)](https://github.com/PO-31/QtReports/search?l=cpp) [![Лицензия](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/PO-31/QtReports/blob/master/LICENSE) [![Требования](https://img.shields.io/badge/requirements-Qt5-red.svg)](https://github.com/PO-31/QtReports/blob/master/QtReports.pro)
Реализация JasperReports в Qt

[English](README.md) | [Русский](README_RU.md)

## Текущий статус проекта
[![Статус сборки](https://api.travis-ci.org/PO-31/QtReports.svg?branch=master)](https://travis-ci.org/PO-31/QtReports) [![Значок Coverage](https://po-31.github.io/QtReports/master/badge.svg)](http://po-31.github.io/QtReports/master/) [![Значок Codacy](https://api.codacy.com/project/badge/Grade/592ade065f16400586bd20717d7ac8ee)](https://www.codacy.com/app/drclaws/QtReports?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=PO-31/QtReports&amp;utm_campaign=Badge_Grade)

## Требования
  + Qt 5+
  + gcc-5+/clang-3.4+/msvc14+

## Сборка
Процесс сборки описан в файле [BUILD_RU.md](BUILD_RU.md).

## Структура репозитория
		.travis/			Скрипты для Travis CI
		qtreports/			Исходные файлы библиотеки QtReports
		qtreports/include/		Заголовочные файлы C++ общего пользования QtReports 
		qtreports-tests/		Исходные файлы комплекса тестирования
		qtreports-viewer/		Каталог проекта QtReports-View
		samples/			Образцы отчетов и базы данных к ним
		docs/				Документы, связанные с QtReports

## Дополнительные ссылки
  + [Документация](http://po-31.github.io/ru/html/)
  + [QtReports-View](./qtreports-viewer/) - средство для просмотра отчетов QtReports.
  + [Wiki](https://github.com/PO-31/QtReports/wiki)
