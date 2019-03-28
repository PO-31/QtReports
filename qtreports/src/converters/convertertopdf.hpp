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
            ConverterToPDF( const ReportPtr & report );
            ~ConverterToPDF();

            /*! @~russian
            Запускает процесс конвертации.
            Путь может быть полным или относительным, примеры: 
            "C:/example.pdf" "example.pdf"
            @param[in] path Путь, по которому будет создан PDF документ.
            */
            bool            convert( const QString & path );

            /*! @~russian
            Устанавливает DPI
            @param[in] dpi Новое значение DPI
            */
            void            setDPI( int dpi );

            /*! @~russian
            Возвращает текущее значение DPI
            */
            int             getDPI() const;

            /*! @~russian
            Возвращает строку, содержащую описание последней произошедшей ошибки.
            */
            const QString   getLastError() const;

        private:
            ReportPtr   m_report;
            QString     m_lastError;
            int         m_dpi;
            int         m_currentResolution;
            int         m_currentHeight;
            bool        addGroupsIntoReport(QPdfWriter &writer, QPainter &painter, const ReportPtr & report, const DetailPtr & detail);
            bool        create(const QString &path);
            bool        createSection(QPdfWriter &writer, QPainter &painter, const SectionPtr & section, int i);
            bool        createBands(QPdfWriter &writer, QPainter &painter, const SectionPtr & section);
        };

    }
}
#endif // CONVERTERTOPDF_HPP
