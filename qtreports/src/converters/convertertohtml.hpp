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
        */
        class ConverterToHTML {

        public:
            /*!
            * @brief Конструктор по умолчанию.
            * @param report ссылка на объект ReportPtr.
            */
            explicit ConverterToHTML(const ReportPtr & report);
            ~ConverterToHTML();

            /*! @~russian
            Запускает процесс конвертации репорта в HTML формат.

            @return @code{.cpp} true @endcode если конвертация прошла успешно.
            @return @code{.cpp} false @endcode если конвертация не удалась.
            */
            bool    convert();

            /*! @~russian
            Создает HTML документ при успешной конвертации репорта в HTML формат.
            Путь может быть полным или относительным, примеры:
            "C:/example.html" "example.html"

            @param[in] path Путь, по которому будет создан HTML документ.

            @return @code{.cpp} true @endcode если создание файла прошло успешно.
            @return @code{.cpp} false @endcode если создание файла не удалось.
            */
            bool    convert(const QString & path);

            /*! @~russian
            Получить описание последней произошедшей ошибки.

            @return Строка с описанием последней произошедшей ошибки.
            */
            const QString   getLastError() const;

            /*! @~russian
            Получить документ в HTML формате.

            @return Строка с документом в HTML формате.
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

            @return @code{.cpp} true @endcode если конвертация прошла успешно.
            @return @code{.cpp} false @endcode если конвертация не удалась.
            */
            bool        createHTML();

            /*! @~russian
            Добавление <group> в документ HTML.

            @param[in] detail Ссылка на объект Detail.

            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            bool        addGroupsIntoReport(DetailPtr detail);

            /*! @~russian
            Добавление <band> в документ HTML.

            @param[in] section Ссылка на объект Section, который содержит объект Band.
            Может указывать на такие секции, как:
            @code{.cpp} title, header, footer, detail @endcode
            @param[in] sectionIndex Индекс конкретной секции.

            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            bool        addBand(SectionPtr section, int sectionIndex);

            /*! @~russian
            Добавление объекта Shape в документ HTML.

            @param[in] band Ссылка на объект Band, который содержит объект Shape:
            @code{.cpp} image, line, rect, ellipse @endcode
            @param[out] elemenStr Строка с содержимым band.
            */
            void        addShapes(BandPtr band, QString &elementStr);

            /*! @~russian
            Добавление объектов Crosstab в документ HTML.
            @param[in] band Ссылка на объект Band, который содержит объекты Crosstab.
            @param[out] elemenStr Строка с содержимым band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            bool        addCrosstabsIntoReport(BandPtr band, QString &elementStr);
        };

    }
}
#endif // CONVERTERTOHTML_HPP
