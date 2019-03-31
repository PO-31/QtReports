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

static QMainWindow* mainWindow = nullptr;
static QMenuBar* menuBar = nullptr;
static QMenu* fileMenu = nullptr;
static QMenu* convertMenu = nullptr;

static QAction* printAction = nullptr;
static QAction* createPdfAction = nullptr;
static QAction* createHtmlAction = nullptr;
static QAction* selectDatabaseAction = nullptr;
static QAction* closeAction = nullptr;
static QAction* openAction = nullptr;
static QAction* exitAction = nullptr;

static QSharedPointer<QWidget> layout;

static qtreports::Engine* engine = nullptr;

void showError(const QString& text);
void closeReport();
void openReport(const QString& reportPath);
void openReport();
void openDatabase(const QString& dbPath);
void openDatabase();

void showError(const QString& text)
{
    QMessageBox::warning(nullptr, "Error: ", text);
}

void closeReport()
{
    engine->close();
    layout.clear();
    if (mainWindow->centralWidget() != nullptr) {
        delete mainWindow->centralWidget();
    }
    convertMenu->setEnabled(false);
    printAction->setEnabled(false);
    closeAction->setEnabled(false);
    selectDatabaseAction->setEnabled(false);
    mainWindow->setWindowTitle("QtReports viewer");
}

void openReport(const QString& reportPath)
{
    closeReport();

    bool result = engine->open(reportPath);
    closeAction->setEnabled(result);
    selectDatabaseAction->setEnabled(result);
    if (!result) {
        showError(engine->getLastError());
        return;
    }
    QFileInfo fileInfo(reportPath);
    mainWindow->setWindowTitle("QtReports viewer - " + fileInfo.fileName());
    layout = engine->createLayout();
    if (layout.isNull()) {
        showError("Widget is empty");
        engine->close();
        return;
    }
    mainWindow->setCentralWidget(layout.data());
    mainWindow->resize(layout->size());
}

void openReport()
{
    auto reportPath = QFileDialog::getOpenFileName(
        mainWindow,
        QObject::tr("Open QReport"),
        QString(),
        QObject::tr("QReport Files (*.qreport *.qrxml);;All Files (*.*)")
    );
    if (reportPath.isEmpty()) {
        return;
    }
    openReport(reportPath);
}

void openDatabase(const QString& dbPath)
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        showError("Can not open database. Database error: " + db.lastError().text());
        return;
    }
    bool result = engine->setConnection(db);
    convertMenu->setEnabled(result);
    printAction->setEnabled(result);
    if (!result) {
        showError(engine->getLastError());
        return;
    }

    //setting report parameters
    QMap <QString, QVariant> map;
    map["title"] = "GRISHA RULIT";
    map["idPlan"] = "2";
    map["summary"] = "FEDOS RULIT";

    if (!engine->setParameters(map)) {
        showError(engine->getLastError());
    }
}

void openDatabase()
{
    auto dbPath = QFileDialog::getOpenFileName(
        mainWindow,
        QObject::tr("Open DataBase"),
        QString(),
        QObject::tr("DataBase files (*.db);;All Files (*.*)")
    );
    if (dbPath.isEmpty()) {
        return;
    }
    openDatabase(dbPath);
}

int main(int argc, char *argv[]) {
    QApplication a(argc,argv);

    mainWindow = new QMainWindow();
    mainWindow->setWindowTitle("QtReports viewer");
    mainWindow->resize(800, 600);
    menuBar = new QMenuBar(mainWindow);
    fileMenu = new QMenu("File", menuBar);
    convertMenu = new QMenu("Convert", menuBar);

//For Debug in Windows
#ifdef WIN32
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    printAction = new QAction(QObject::tr("&Print..."), mainWindow);
    printAction->setShortcuts(QKeySequence::Print);
    printAction->setStatusTip(QObject::tr("Print current report"));
    QObject::connect(printAction, &QAction::triggered, [&]() {
        if (!engine->print()) {
            showError(engine->getLastError());
        }
    });

    createPdfAction = new QAction(QObject::tr("&Create PDF..."), mainWindow);
    createPdfAction->setStatusTip(QObject::tr("Create PDF from current report"));
    QObject::connect(createPdfAction, &QAction::triggered, [&]() {
        auto file = QFileDialog::getSaveFileName(
            mainWindow,
            QObject::tr("Save as PDF"),
            QString(),
            QObject::tr("PDF Files (*.pdf)")
        );
        if (file.isEmpty()) {
            return;
        }
        if (!engine->createPDF(file)) {
            showError(engine->getLastError());
            return;
        }
    });

    createHtmlAction = new QAction(QObject::tr("&Create HTML..."), mainWindow);
    createHtmlAction->setStatusTip( QObject::tr("Create HTML from current report"));
    QObject::connect(createHtmlAction, &QAction::triggered, [&]() {
        auto file = QFileDialog::getSaveFileName(
            mainWindow,
            QObject::tr("Save as HTML"),
            QString(),
            QObject::tr("HTML Files (*.html *.htm)")
        );
        if (file.isEmpty()) {
            return;
        }

        bool result = engine->createHTML(file);
        if (!result) {
            showError(engine->getLastError());
            return;
        }
    });

    selectDatabaseAction = new QAction(QObject::tr("&Select database..."), mainWindow);
    selectDatabaseAction->setStatusTip(QObject::tr("Select database file"));
    QObject::connect(selectDatabaseAction, &QAction::triggered, [&]() { openDatabase(); });

    closeAction = new QAction(QObject::tr("&Close report"), mainWindow);
    closeAction->setShortcuts(QKeySequence::Close);
    closeAction->setStatusTip(QObject::tr("Close current report"));
    QObject::connect(closeAction, &QAction::triggered, [&]() { closeReport(); });

    openAction = new QAction(QObject::tr("&Open report..."), mainWindow);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(QObject::tr( "Open an existing report file"));
    QObject::connect(openAction, &QAction::triggered, [ & ]() { openReport(); });

    exitAction = new QAction(QObject::tr("&Exit"), mainWindow);
    exitAction->setShortcuts( QKeySequence::Quit );
    QObject::connect(exitAction, &QAction::triggered, mainWindow, &QMainWindow::close);

    fileMenu->addActions({ openAction, selectDatabaseAction, printAction, closeAction, exitAction });
    convertMenu->addActions({ createPdfAction, createHtmlAction });
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(convertMenu);
    mainWindow->setMenuBar(menuBar);

    engine = new qtreports::Engine();
    closeReport();

    if (argc > 1) {
        openReport(argv[1]);
    }
    if (argc > 2) {
        openDatabase(argv[2]);
    }
    mainWindow->show();

    return a.exec();
}
