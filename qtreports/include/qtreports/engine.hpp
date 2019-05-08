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
#include <QPrintPreviewDialog>

#include <QDebug>

/*!
@~english
@mainpage QtReports
Welcome to QtReports documentation page.
@section intro_sec Introduction
The documentation helps you with using QtReports.

The project repo is located on <a href="https://github.com/PO-31/QtReports">Github</a>. There you can find instructions of building and using QtReports with your project.

@section warning_sec Warning
The translation is in progress.

@~russian
@mainpage QtReports
Добро пожаловать в документацию проекта QtReports.

@section intro_sec Введение
Эта документация предназначена для того, чтобы помочь в использовании проекта.

Репозиторий проекта располагается на <a href="https://github.com/PO-31/QtReports">Github</a>. Описание сборки и подключения QtReports к вашему проекту вы можете найти там.
*/

namespace qtreports {

    typedef QSharedPointer< QWidget > QWidgetPtr;
    typedef QSharedPointer< QPrintPreviewDialog> QPrintPreviewDialogPtr;
    namespace detail {
        class Report;
        typedef QSharedPointer< Report > ReportPtr;
    }

    class Engine : public QObject {
        Q_OBJECT

    public:
        explicit Engine( QObject * parent = Q_NULLPTR );
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
        QPrintPreviewDialogPtr getPrintPreviewDialog();

        /*! @~russian
        Возвращает true в случае учпешной загрузки отчета, иначе - false
        */
        bool        	    isOpened() const;
        detail::ReportPtr   getReport() const;
        const QString       getLastError() const;

    private:
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
