#pragma once
#ifndef CONVERTERTOPDF_HPP
#define CONVERTERTOPDF_HPP
#include <QString>
#include "tags/report.hpp"

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

            bool        create( const QString & path );

        };

    }
}
#endif // CONVERTERTOPDF_HPP
