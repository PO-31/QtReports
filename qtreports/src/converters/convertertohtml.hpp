#pragma once
#ifndef CONVERTERTOHTML_HPP
#define CONVERTERTOHTML_HPP
#include <QString>
#include <QBuffer>

#include "../tags/report.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, используемый для конвертации репорта в HTML формат.

        Класс, используемый для конвертации репорта в HTML формат.
        */
        class ConverterToHTML {

        public:
            /*!
            * @brief Конструктор по умолчанию
            * @param report ссылка на объект ReportPtr
            */
            explicit ConverterToHTML(const ReportPtr & report);
            ~ConverterToHTML();

            /*! @~russian
            Запускает процесс конвертации репорта в HTML формат.

            @return true в случае успешной конвертации, иначе false
            */
            bool    convert();

            /*! @~russian
            Создает HTML документ при успешной конвертации репорта в HTML формат.
            Путь может быть полным или относительным, примеры:
            "C:/example.html" "example.html"

            @param[in] path Путь, по которому будет создан HTML документ

            @return true в случае успешного создания файла, иначе false
            */
            bool    convert(const QString & path);

            /*! @~russian
            Получить описание последней произошедшей ошибки.

            @return Строка с описанием последней произошедшей ошибки
            */
            const QString   getLastError() const;

            /*! @~russian
            Получить документ в HTML формате.

            @return Строка с документом в HTML формате
            */
            const QString   getHTML() const;

        private:
            /*! @~russian
            Объект класса ReportPtr.
            */
            ReportPtr   m_report;

            /*! @~russian
            Содержит информацию о последней ошибке, возникшей в процессе конвертации.
            */
            QString     m_lastError;

            /*! @~russian
            Содержит текст документа в формате HTML.
            */
            QString     m_html;

            /*! @~russian
            Содержит название стиля по умолчанию.
            */
            QString     m_defaultStyleName;


            /*! @~russian
            Процесс конвертации репорта в HTML формат.

            @return true в случае успешной конвертации, иначе false
            */
            bool        createHTML();

            /*! @~russian
            Добавление group в документ HTML.

            @param[in] detail Ссылка на объект Detail

            @return true в случае успешного добавления, иначе false
            */
            bool        addGroupsIntoReport(QSharedPointer<Detail> detail);

            /*! @~russian
            Добавление band, принадлежащего конкретной section,  в документ HTML.

            @param[in] section Ссылка на объект Section. Может указывать на такие секции, как:
             * @code{.cpp} title, header, footer, detail @endcode
            @param[in] sectionIndex Индекс конкретной секции

            @return true в случае успешного добавления, иначе false
            */
            bool        addBands(QSharedPointer<Section> section, int sectionIndex);

            /*! @~russian
            Добавление shape, принадлежащего конретному band, в документ HTML.

            @param[in] band Ссылка на объект Band.
            @param[out] elemenStr Строка, содержащая содержимое band
            */
            void        addShapes(QSharedPointer<Band> band, QString &elementStr);
        };

    }
}
#endif // CONVERTERTOHTML_HPP
