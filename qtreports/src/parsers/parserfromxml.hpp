#pragma once
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP
#include <functional>
#include <QString>
#include <QXmlStreamReader>
#include <QMap>
#include <QTextStream>

#include "../tags/report.hpp"
#include "../tags/style.hpp"
#include "../tags/field.hpp"
#include "../tags/group.hpp"
#include "../tags/title.hpp"
#include "../tags/detail.hpp"
#include "../tags/summary.hpp"
#include "../tags/band.hpp"
#include "../tags/statictext.hpp"
#include "../tags/textfield.hpp"
#include "../tags/line.hpp"
#include "../tags/rect.hpp"
#include "../tags/ellipse.hpp"
#include "../tags/image.hpp"
#include "../tags/crosstab.hpp"
#include "../tags/variable.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, используемый для парсинга исходного отчета.
        @warning Все функции данного класса, возвращающие bool,
        возвращают true в случае успеха либо false, если во время 
        выполнения произошли ошибки. При этом с помощью метода getLastError()
        можно получить описание последней произошедшей ошибки.

        Класс, который отвечает за парсинг отчета и 
        создание из него внутренней структуры данных Report.
        */
        class ParserFromXML {

        public:
            ParserFromXML();
            ~ParserFromXML();

            /*! @~russian
            Парсит отчет и создает из него внутреннюю структуру данных Report.
            @param[in] path Путь к отчету формата .qreport
            */
            bool                parse( const QString & path );

            /*! @~russian
            Возвращает указатель на внутреннюю структуру отчета.
            Указатель может быть пустым, перед использованием необходимо
            проверить с помощью
            @code
            if ( !report.isNull() ) {
            @endcode
            */
            const ReportPtr     getReport() const;

            /*! @~russian
            Возвращает описание последней произошедшей ошибки.
            */
            const QString      getLastError() const;

            /*! @~russian
            Возвращает лог процесса парсинга. Используется для отладки при добавлении новый тэгов.
            */
            const QString      getLog() const;

            using ParseFuncPtr = bool( QXmlStreamReader &, const ObjectPtr & );
            using ParseMethodPtr = bool( ParserFromXML::* )( QXmlStreamReader &, const ObjectPtr & );
            using ParseFunc = std::function< ParseFuncPtr >;

        private:
            ReportPtr	                m_report;
            QString		                m_lastError;
            QTextStream                 m_log;
            QMap< QString, ParseFunc >  m_functions;

            /*! @~russian
            Опции при получении аттрибута с помощью вызова getAttribute().
            */
            enum class AttributeOption {
                Required = 0, ///< При отсутствии аттрибута будет выдана ошибка.
                Optional ///< При отсутствии аттрибута будет использовано значение по умолчанию.
            };

            /*! @~russian
            Считывает xml элемент в data
            @param[in] reader QXmlStreamReader
            @parem[out] data считанные данные
            */
            bool    getValue( QXmlStreamReader & reader, QString & data );
            /*! @~russian
            Записывает в data значение аттрибута с именем name текущего тэга
            @param[in] reader QXmlStreamReader
            @param[in] name имя аттрибута
            @param[in] option указывает обязателен ли атрибут
            @parem[out] data считанные данные
            */
            bool    getAttribute( QXmlStreamReader & reader, const QString & name, QString & data, AttributeOption option );
            /*! @~russian
            Вызывает функцию getAttribute с переданными параметрами и с параметром option - "обязательный аттрибут"
            */
            bool    getRequiredAttribute( QXmlStreamReader & reader, const QString & name, QString & data );
            /*! @~russian
            Вызывает функцию getAttribute с переданными параметрами и с параметром option - "опциональный аттрибут"
            */
            bool    getOptionalAttribute( QXmlStreamReader & reader, const QString & name, QString & data );
            /*! @~russian
            Устанавлиает курсор reader(а) к к началу следующего тэга или к концу документа
            */
            bool    goToElementEnd( QXmlStreamReader & reader );
            /*! @~russian
            Парсит дочерние тэги объекта object
            @param[in] object родительский объект отчета
            */
            bool    parseChilds( QXmlStreamReader & reader, const ObjectPtr & object );
            
            /*! @~russian
            Начинает парсинг документа
            @param[in] text имя xml файла
            */
            bool    parseDocument( const QString & text );
            /*! @~russian
            Парсит тэг report
            @param[in] report указатель на объект отчета
            */
            bool    parseReport( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит тэг style
            @param[in] report указатель на объект отчета
            */
            bool    parseStyle( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит запросы
            @param[in] report указатель на объект отчета
            */
            bool    parseQueryString( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит тэг Field
            @param[in] report указатель на объект отчета
            */
            bool    parseField( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит тэг group
            @param[in] report указатель на объект отчета
            */
            bool    parseGroup( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит тэг groupExpression
            @param[in] group указатель на группу, которой принадлежит groupExpression
            */
            bool    parseGroupExpression( QXmlStreamReader & reader, const GroupPtr & group );
            /*! @~russian
            Парсит тэг groupHeader
            @param[in] group указатель на группу, которой принадлежит groupHeader
            */
            bool    parseGroupHeader( QXmlStreamReader & reader, const GroupPtr & group );
            /*! @~russian
            Парсит тэг groupFooter
            @param[in] group указатель на группу, которой принадлежит groupFooter
            */
            bool    parseGroupFooter( QXmlStreamReader & reader, const GroupPtr & group );
            /*! @~russian
            Парсит тэг Title
            @param[in] report указатель на объект отчета
            */
            bool    parseTitle( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит тэг Detail
            @param[in] report указатель на объект отчета
            */
            bool    parseDetail( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит тэг Summary
            @param[in] report указатель на объект отчета
            */
            bool    parseSummary( QXmlStreamReader & reader, const ReportPtr & report );
            /*! @~russian
            Парсит тэг Band
            @param[in] section секция (объект, содержащий Band(ы), Detail, Title, groupHeader и т.д.), которой принадлежит Band
            */
            bool    parseBand( QXmlStreamReader & reader, const SectionPtr & section );
            /*! @~russian
            Парсит тэг Crosstab
            @param[in] band Строка, которой принадлежит объект
            */
            bool parseCrosstab(QXmlStreamReader & reader, const BandPtr & band);
            /*! @~russian
            Парсит тэг rowGroup
            @param[in] crosstab Кросстаб, которому принадлежит объект
            */
            bool parseRowGroup(QXmlStreamReader & reader, const CrosstabPtr & crosstab);
            /*! @~russian
            Парсит тэг columnGroup
            @param[in] crosstab Кросстаб, которому принадлежит объект
            */
            bool parseColumnGroup(QXmlStreamReader & reader, const CrosstabPtr & crosstab);
            /*! @~russian
            Парсит тэг crosstabCell
            @param[in] crosstab Кросстаб, которому принадлежит объект
            */
            bool parseCrosstabCell(QXmlStreamReader & reader, const CrosstabPtr & crosstab);
            /*! @~russian
            Парсит тэг crosstabRowHeader
            @param[in] rowGroup Группа кросстаба, которому принадлежит объект
            */
            bool parseCrosstabRowHeader(QXmlStreamReader & reader, const CrosstabGroupPtr &rowGroup);
            /*! @~russian
            Парсит тэг crosstabColumnHeader
            @param[in] columnGroup Группа кросстаба, которому принадлежит объект
            */
            bool parseCrosstabColumnHeader(QXmlStreamReader & reader, const CrosstabGroupPtr & columnGroup);
            /*! @~russian
            Парсит тэг cellContents
            @param[in] crosstabSection Секция кросстаба, которому принадлежит объект
            */
            bool parseCrosstabCellContents(QXmlStreamReader & reader, const CrosstabCellPtr &crosstabSection);
            /*! @~russian
            Парсит тэг StaticText
            @param[in] band Строка, которой принадлежит объект
            */
            bool    parseStaticText( QXmlStreamReader & reader, const BandPtr & band );
            /*! @~russian
            Парсит тэг TextField
            @param[in] band Строка, которой принадлежит объектVariablePtr
            */
            bool    parseTextField( QXmlStreamReader & reader, const WidgetPtr & widget );
            /*! @~russian
            Парсит тэг Line
            @param[in] band Строка, которой принадлежит объект
            */
            bool    parseLine( QXmlStreamReader & reader, const BandPtr & band );
            /*! @~russian
            Парсит тэг Rect
            @param[in] band Строка, которой принадлежит объект
            */
            bool    parseRect( QXmlStreamReader & reader, const BandPtr & band );
            /*! @~russian
            Парсит тэг Ellipse
            @param[in] band Строка, которой принадлежит объект
            */
            bool    parseEllipse( QXmlStreamReader & reader, const BandPtr & band );
            /*! @~russian
            Парсит тэг Image
            @param[in] band Строка, которой принадлежит объект
            */
            bool    parseImage( QXmlStreamReader & reader, const BandPtr & band );
            /*! @~russian
            Парсит тэг ReportElement - общие данные о элементе отчета (положение, размеры и пр.)
            @param[in] widget общий класс для объектов, подлежащих отображению. Для него загружается текущий reportElement
            */
            bool    parseReportElement( QXmlStreamReader & reader, const WidgetPtr & widget );
            /*! @~russian
            Парсит тэг TextElement - общие данные о текстовом элементе (выравнивание текста и пр.)
            @param[in] widget общий класс для объектов, подлежащих отображению. Для него загружается текущий textElement
            */
            bool	parseTextElement( QXmlStreamReader & reader, const WidgetPtr & widget );
            /*! @~russian
            Парсит font - данные о шрифте текста
            @param[in] widget общий класс для объектов, подлежащих отображению. Для него загружается текущий font
            */
            bool	parseFont( QXmlStreamReader & reader, const WidgetPtr & widget );
            /*! @~russian
            Парсит текст для staticText
            @param[in] text staticText, текущий объект
            */
            bool    parseText( QXmlStreamReader & reader, const StaticTextPtr & text );
            /*! @~russian
            Парсит текст для textField
            @param[in] text textField, текущий объект
            */
            bool    parseTextFieldExpression( QXmlStreamReader & reader, const TextFieldPtr & text );
            /*! @~russian
            Парсит текст (imageExpression) для image
            @param[in] image тэг image, текущий объект
            */
            bool    parseImageExpression( QXmlStreamReader & reader, const ImagePtr & image );

            bool    parseVariable( QXmlStreamReader & reader, const ReportPtr & report );

            bool    parseVariableExpression(QXmlStreamReader & reader, const VariablePtr &variable );

            bool    parseInitialValueExpression( QXmlStreamReader & reader, const VariablePtr & variable );

        };

    }
}
#endif // TRANSLATOR_HPP
