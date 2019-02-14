#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <QObject>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QVector>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlField>
#include <QPrinter>
#include <QAbstractItemModel>
//#include "processeddb.hpp"
#include "tags/report.hpp"
#include "converters/convertertoqwidget.hpp"

/*! @~russian
@mainpage QtReports
Добро пожаловать в документацию проекта QtReports.

@section intro_sec Введение
Эта документация предназначена для того, чтобы помочь в использовании проекта. 

@section install_sec Установка с помощью CMAKE

@subsection step1 Шаг 1: Распаковка проекта.

Скачать проект по ссылке https://github.com/PO-31/QtReports/archive/master.zip.

Распаковать архив в папку QtReports. 

(Полный путь к папке QtReports не должен содержать кириллицы) 

@subsection step2 Шаг 2: Генерация CMakeLists.

В корневой папке QtReports, где расположен CMakeLists.txt в командной строке запустить команду: 

Для Windows:

cmake [CMAKE_PREFIX_PATH="путь к qt"]  -G "MinGW Makefiles" -B./bin -H./

Примечание:

При возникновении ошибки "By not providing "FindQt5Widgets.cmake" in CMAKE_MODULE_PATH this project

has asked CMake to find a package configuration file provided by

"Qt5Widgets", but CMake did not find one." необходимо добавить в команду блок [CMAKE_PREFIX_PATH="путь к qt"].

Пример для Windows:
cmake [CMAKE_PREFIX_PATH="C:/Qt/5.5/mingw492_32"]  -G "MinGW Makefiles" -B./bin -H./

@subsection step3 Шаг 3: Компиляция проекта.

Windows:

Запустить команду: mingw32-make -C./bin

Exe-файл будет расположен в папке qtreportsviewer

@section use_sec Использование
Подключите библиотеку к проекту с помощью
-lqtreportslib -I/usr/include/qtreportslib
*/

namespace qtreports {
    class Engine : public QObject {
        Q_OBJECT

    public:
        Engine( QObject * parent = Q_NULLPTR );
        Engine( const QString & path, QObject * parent = Q_NULLPTR );
        ~Engine();

        /*! @~russian
        Загружает макет отчета из файла path
        @param[in] path полное имя макета отчета
        */
        bool    open( const QString & path );

        /*! @~russian
        Выгружает из оперативной памяти данные об отчете
        */
        void    close();

        /*! @~russian
        Передает карту параметров в отчет, для успешной передачи параметров не обязатеьно загружать их описание с макетом отчета
        @param[in] map карта параметров в формате (<имя параметра>, <значение параметра>)
        */
        bool    setParameters( const QMap< QString, QVariant > & map );

        /*! @~russian
        Устанавливает источник данных для отчета из БД
        @param[in] connection соединение с БД
        */
        bool    setConnection( const QSqlDatabase & connection );

        /*! @~russian
        Устанавливает источник данных для отчета из таблицы полей
        @param[in] columnsSet набор данных в формате (<имя столбца>, <вектор значений столбца>)
        */
        bool    setDataSource( const QMap <QString, QVector <QVariant> > & columnsSet);

        /*! @~russian
        Устанавливает запрос, по которому будут заполнятся поля отчета
        @param[in] query запрос
        */
        bool    setQuery( const QString & query );

        /*! @~russian
        Добавить скрипт для отчета
        @param[in] script скрипт
        */
        bool    addScript( const QString & script );
        bool    setDataModel( const QAbstractItemModel & model );

        /*! @~russian
        Создает PDF документ отчета по указанному пути
        @param[in] path полное имя выходного документа
        */
        bool                createPDF( const QString & path );
        
        /*! @~russian
        Создает HTML документ отчета по указанному пути
        @param[in] path полное имя выходного документа
        */
        bool                createHTML( const QString & path );//etc.

        /*! @~russian
        Создает виджет отчета для вывода на экран.
        */
        QWidgetPtr          createWidget();
        QWidgetPtr          createLayout();
        bool                print();

        /*! @~russian
        Возвращает true в случае учпешной загрузки отчета, иначе - false
        */
        bool        	    isOpened() const;
        detail::ReportPtr   getReport() const;
        const QString       getLastError() const;

    public:
        bool                                m_isOpened;
        QString                             m_lastError, m_compiledPath;
        detail::ReportPtr                   m_report;
        QVector< QString >                  m_scripts;
        QSqlDatabase                        m_dbConnection;
        //detail::ProcessedDB                 m_processedDB;

        void                                drawPreview( QPrinter * printer );
        bool                                prepareDB();
        bool                                prepareDataSource( const QMap< QString, QVector< QVariant > > & source );
        //void                                fillColumnsFromReport();
        bool                                executeQueries( const QStringList & queries );
    };
}
#endif // ENGINE_HPP
