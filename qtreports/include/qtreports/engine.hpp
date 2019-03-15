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
//#include <qtreports/tags/report.hpp>
//#include <qtreports/converters/convertertoqwidget.hpp>

/*! @~russian
@mainpage QtReports
Добро пожаловать в документацию проекта QtReports.

@section intro_sec Введение
Эта документация предназначена для того, чтобы помочь в использовании проекта. 

@section install_sec Инструкция по сборке проекта

@subsection step1 Шаг 1: Распаковка.

Клонировать проект или скачать релиз из репозитория https://github.com/PO-31/QtReports/.

Распаковать архив в папку QtReports. 

(Рекомендуется, чтобы полный путь к папке QtReports содержал только латиницу)

@subsection step2 Шаг 2: Сборка.

Собрать проект можно несколькими способами, но если необходимо указать версию собираемой библиотеки, то необходимо задать переменную среды QTREPORTS_VERSION

@subsubsection step2_1 Способ 1. При помощи QtCreator:

Используя программу, в корневой папке QtReports необходимо открыть файл проекта "QtReports.pro".

Для сборки со статистикой для Coverage установить значение переменной среды BUILD_COVERAGE на "TRUE".

Далее нажать кнопку "Собрать" (кнопка Молоток) для сборки всего проекта.

Если необходимо собрать только определенный компонент, то нужно нажать ПКМ по проекту компонента в обозревателе проектов и выбрать "Собрать Название_Модуля"

@subsubsection step2_2 Способ 2. При помощи Qmake:

Запускаем консоль/терминал и переходим в каталог необходимого нам модуля

Набираем
qmake [-spec "Используемый_Компилятор"] "CONFIG += Необходимые_Типы_Сборки_(release,debug,coverage,etc.)" Имя_Проекта_Модуля.pro

После генерации Makefile вызываем
make [-jКоличествоПотоков]

@section use_sec Использование

После сборки файл библиотеки можно будет найти в папке "build/lib", а заголовочные файлы - "qtreports/include"

Для подключения собранной библиотеки к Qmake проекту необходимо в файле проекта указать "LIB += -lqtreports" и, если необходимо, "LIB += Путь_До_Библиотеки", "INCLUDEPATH += Путь_До_Заголовочных_Файлов"
*/

namespace qtreports {

    typedef QSharedPointer< QWidget > QWidgetPtr;

    namespace detail {
        class Report;
        typedef QSharedPointer< Report > ReportPtr;
    }

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
