#pragma once
#ifndef CONVERTERTOPDF_HPP
#define CONVERTERTOPDF_HPP
#include <QString>
#include <QPdfWriter>
#include "../tags/report.hpp"
#include "../tags/section.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, используемый для конвертации документа в PDF формат.
        @note Все функции данного класса, возвращающие bool,
        возвращают true в случае успеха либо false, если во время
        выполнения произошли ошибки. При этом с помощью метода getLastError()
        можно получить описание последней произошедшей ошибки.

        Класс, используемый для конвертации документа в PDF формат.
        Поддерживает установку DPI.
        */
        class ConverterToPDF {

        public:
            /*!
             * @brief Конструктор по умолчанию.
             * @param report ссылка на объект ReportPtr.
             */
            explicit ConverterToPDF( const ReportPtr & report );
            ~ConverterToPDF();

            /*! @~russian
            Запускает процесс конвертации.
            Путь может быть полным или относительным, примеры: 
            "C:/example.pdf" "example.pdf"
            @param[in] path Путь, по которому будет создан PDF документ.
            @return @code{.cpp} true @endcode, если конвертация отчета в PDF прошла успешно, иначе @code{.cpp} false @endcode.
            */
            bool            convert( const QString & path );

            /*! @~russian
            Устанавливает DPI
            @param[in] dpi Новое значение DPI.
            */
            void            setDPI( int dpi );

            /*! @~russian
            Возвращает текущее значение DPI.
            */
            int             getDPI() const;

            /*! @~russian
            Возвращает строку, содержащую описание последней произошедшей ошибки.
            */
            const QString   getLastError() const;

        private:
            /*! @~russian
            Объект класса ReportPtr
            */
            ReportPtr   m_report;

            /*! @~russian
            Содержит информацию о последней ошибке, возникшей в процессе конвертации.
            */
            QString     m_lastError;

            /*! @~russian
            Значение текущего разрешения для PDF документа в DPI. По умолчанию установлено значение 75.
            */
            int         m_currentResolution;

            /*! @~russian
            * Значение текущей высоты кисти, рисующей на листе документа PDF.
            * Значение постоянно меняется в зависимости от высоты band. Например, если в отчете для band'а,
            * который отрисовывается в данный момент, значение параметра height равняется 35, то после
            * отрисовки данного band'а, кисть переместится вниз на 35 единиц.
            */
            int         m_currentHeight;

            /*! @~russian
             * Добавляет группу в репорт.
             * Если не удалось добавить группу, вернет false.
             * @param[in] writer Ссылка на объект QPdfWriter.
             * @param[in] painter Ссылка на объект QPainter.
             * @param[in] report Ссылка на объект ReportPtr.
             * @param[in] detail Ссылка на объект DetailPtr.
             * @return @code{.cpp} true @endcode, если добавление группы прошло успешно, иначе @code{.cpp} false @endcode.
            */
            bool        addGroupsIntoReport(QPdfWriter &writer, QPainter &painter, const ReportPtr & report, const DetailPtr & detail);

            /*! @~russian
             * Конвертирует отчет в PDF документ.
             * Если не удалось конвертировать в PDF, вернет false.
             * Информация об ошибке содержится в переменной m_lastError.
             * @param[in] path Путь к файлу PDF.
             * @return @code{.cpp} true @endcode, если конвертация прошла успешно, иначе @code{.cpp} false @endcode.
            */
            bool        create(const QString &path);

            /*! @~russian
             * Создает секцию.
             * Если не удалось создать секцию, вернет false.
             * Информация об ошибке содержится в переменной m_lastError.
             * @param[in] writer Ссылка на объект QPdfWriter.
             * @param[in] painter Ссылка на объект QPainter.
             * @param[in] section Ссылка на объект SectionPtr. SectionPtr может указывать на такие секции, как:
             * @code{.cpp} title, header, footer, detail @endcode.
             * @param[in] i Индекс текущей секции.
             * @return @code{.cpp} true @endcode, если создание секции прошло успешно, иначе @code{.cpp} false @endcode.
            */
            bool        createSection(QPdfWriter &writer, QPainter &painter, const SectionPtr & section, int i);

            /*! @~russian
             * Создает band.
             * @param[in] writer Ссылка на объект QPdfWriter.
             * @param[in] painter Ссылка на объект QPainter.
             * @param[in] section Ссылка на объект SectionPtr.
             * @return @code{.cpp} true @endcode, если создание bsnd'a прошло успешно, иначе @code{.cpp} false @endcode.
            */
            bool        createBands(QPdfWriter &writer, QPainter &painter, const SectionPtr & section);
        };

    }
}
#endif // CONVERTERTOPDF_HPP
