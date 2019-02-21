#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <qtreports/engine.hpp>

#ifdef WIN32
#include <Windows.h>
#endif

void    showError( const QString & text )
{
    QMessageBox::warning( 0, "Error: ", text );
}

int main( int argc, char *argv[] ) {
    QApplication a( argc, argv );
    //Need initialize before of engine widget( for not stack memory problem );
    QMainWindow window;
    QMenuBar bar( &window );
    QMenu file( "File", &bar );
    QMenu convert( "Convert", &bar );

//For Debug in Windows
#ifdef WIN32
    AllocConsole();
    freopen( "CONOUT$", "w", stdout );
    freopen( "CONOUT$", "w", stderr );
#endif

	QString path = argc > 1 ? argv[ 1 ] : QFileDialog::getOpenFileName( &window,
																		QObject::tr( "Open QReport" ),
																		QString(),
																		QObject::tr( "QReport Files (*.qreport);;QReport Files (*.qrxml);;All Files (*.*)" ) );
    qtreports::Engine engine( path );
    if( !engine.isOpened() ) {
        showError( engine.getLastError() );
		return -1;
    }

    QMap < QString, QVariant > map;
    map[ "title" ] = "GRISHA RULIT";
    map[ "idPlan" ] = "2";
	
    bool result = engine.setParameters( map );//{ { "title", "Best Title in World" } }
    if( !result ) {
        showError( engine.getLastError() );
		return -1;
    }

    auto db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName(QFileDialog::getOpenFileName( &window,
													 QObject::tr( "Open QReport" ),
													 QString(),
                                                     QObject::tr( "DataBase files (*.db);;All Files (*.*)" ) ));
    if( !db.open() ) {
        showError( "Can not open database. Database error: " + db.lastError().text() );
		return -1;
    }

    result = engine.setConnection( db );
    if( !result ) {
        showError( engine.getLastError() );
		return -1;
    }

    auto layout = engine.createLayout();
    if( layout.isNull() ) {
        showError( "Layout is empty. Error: " + engine.getLastError() );
        return -1;
    }

    window.setCentralWidget( layout.data() );
    window.resize( layout->size() );
    window.show();

    QAction print( QObject::tr( "&Print..." ), &window );
    print.setShortcuts( QKeySequence::Print );
    print.setStatusTip( QObject::tr( "Print current report" ) );
    QObject::connect( &print, &QAction::triggered, [ & ]() {
		bool result = engine.print();
        if( !result ) {
            showError( engine.getLastError() );
            return;
        }
    } );

    QAction createPDF( QObject::tr( "&Create PDF..." ), &window );
    createPDF.setStatusTip( QObject::tr( "Create PDF from current report" ) );
    QObject::connect( &createPDF, &QAction::triggered, [ & ]() {
        auto file = QFileDialog::getSaveFileName( &window,
            QObject::tr( "Save as PDF" ),
            QString(),
            QObject::tr( "PDF Files (*.pdf)" ) );
        if( file.isEmpty() ) {
            return;
        }

        bool result = engine.createPDF( file );
        if( !result ) {
            showError( engine.getLastError() );
            return;
        }
    } );

    QAction createHTML( QObject::tr( "&Create HTML..." ), &window );
    createHTML.setStatusTip( QObject::tr( "Create HTML from current report" ) );
    QObject::connect( &createHTML, &QAction::triggered, [ & ]() {
        auto file = QFileDialog::getSaveFileName( &window,
            QObject::tr( "Save as HTML" ),
            QString(),
            QObject::tr( "HTML Files (*.html *.htm)" ) );
        if( file.isEmpty() ) {
            return;
        }

        bool result = engine.createHTML( file );
        if( !result ) {
            showError( engine.getLastError() );
            return;
        }
    } );

    QAction selectDB( QObject::tr( "&Select DB..." ), &window );
    selectDB.setStatusTip( QObject::tr( "Select database file" ) );
    QObject::connect( &selectDB, &QAction::triggered, [ & ]() {
        auto file = QFileDialog::getOpenFileName( &window,
            QObject::tr( "Open DB" ),
            QString(),
            QObject::tr( "All Files (*.*)" ) );
        if( file.isEmpty() )
        {
            return;
        }

        auto db = QSqlDatabase::addDatabase( "QSQLITE" );
        db.setDatabaseName( file );
        if( !db.open() )
        {
            showError( "Can not open database. Database error: " + db.lastError().text() );
            return;
        }

        if( !engine.setConnection( db ) )
        {
            showError( engine.getLastError() );
            return;
        }
    } );

    QAction close( QObject::tr( "&Close..." ), &window );
    close.setShortcuts( QKeySequence::Close );
    close.setStatusTip( QObject::tr( "Close current report" ) );
    QObject::connect( &close, &QAction::triggered, [ & ]() {
        if( window.centralWidget() != nullptr ) {
#if ( QT_VERSION >= QT_VERSION_CHECK( 5, 2, 0 ) )
            window.takeCentralWidget();
#endif
        }

        print.setEnabled( false );
        convert.setEnabled( false );
        close.setEnabled( false );
        selectDB.setEnabled( false );
    } );

    QAction open( QObject::tr( "&Open..." ), &window );
    open.setShortcuts( QKeySequence::Open );
    open.setStatusTip( QObject::tr( "Open an existing file" ) );
    QObject::connect( &open, &QAction::triggered, [ & ]() {
        auto file = QFileDialog::getOpenFileName( &window,
            QObject::tr( "Open QReport" ),
            QString(),
            QObject::tr( "QReport Files (*.qreport);;QReport Files (*.qrxml);;All Files (*.*)" ) );
        if( file.isEmpty() ) {
            return;
        }
        
        if( window.centralWidget() != nullptr ) {
        #if ( QT_VERSION >= QT_VERSION_CHECK( 5, 2, 0 ) )
            window.takeCentralWidget();
        #endif
        }

        bool result = engine.open( file );
        print.setEnabled( result );
        convert.setEnabled( result );
        close.setEnabled( result );
        selectDB.setEnabled( result );
        if( !result ) {
            showError( engine.getLastError() );
            return;
        }

        layout = engine.createLayout();
        if( layout.isNull() ) {
            showError( "Widget is empty" );
            return;
        }

		//new code
		file = QFileDialog::getOpenFileName(&window,
			QObject::tr("Open DB"),
			QString(),
			QObject::tr("All Files (*.*)"));
		if (file.isEmpty())
		{
			return;
		}

		auto db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName(file);
		if (!db.open())
		{
			showError("Can not open database. Database error: " + db.lastError().text());
			return;
		}

		if (!engine.setConnection(db))
		{
			showError(engine.getLastError());
			return;
		}

        window.setCentralWidget( layout.data() );
        window.resize( layout->size() );
    } );

    QAction exit( QObject::tr( "&Exit..." ), &window );
    exit.setShortcuts( QKeySequence::Quit );
    QObject::connect( &exit, &QAction::triggered, &window, &QMainWindow::close );

    print.setEnabled( engine.isOpened() );
    convert.setEnabled( engine.isOpened() );

    file.addAction( &open );
    file.addAction( &selectDB );
    file.addAction( &print );
    file.addAction( &close );
    file.addAction( &exit );
    convert.addAction( &createPDF );
    convert.addAction( &createHTML );
    bar.addMenu( &file );
    bar.addMenu( &convert );
    window.setMenuBar( &bar );
    //engine.createPDF( "test.pdf" );
    //engine.createHTML( "C:/Users/haven/Desktop/test.html" );

    return a.exec();
}
