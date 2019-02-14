#pragma once
#ifndef REPLACER_HPP
#define REPLACER_HPP
#include <QString>
#include "tags/textwidget.hpp"
#include "tags/report.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, заменяющий параметры на реальные значения.

        Класс, заменяющий параметры на реальные значения в тэгах,
        производных от TextWidget
        */
        class Replacer {

        public:
            Replacer();
            ~Replacer();

            /*! @~russian
            Возвращает текст с подставленными значениями параметров.
            @param[in] text Исходный текст
            @param[in] report Указатель на отчет
            */
            QString  replaceParameters( const QString & text, const ReportPtr & report );

            /*! @~russian
            Заменяет текст виджета текстом с подставленными значениями параметров.
            Перегружанная функция, предоставленная для удобства.
            @param[in] widget Указатель на виджет
            @param[in] report Указатель на отчет
            */
            bool     replaceParametersInTextWidget( const TextWidgetPtr & widget, const ReportPtr & report );

            /*! @~russian
            Заменяет текст всех виджетов секции текстом с подставленными значениями параметров.
            Перегружанная функция, предоставленная для удобства.
            @param[in] section Указатель на секцию
            @param[in] report Указатель на отчет
            */
            bool    replaceParametersInSection( const SectionPtr & section, const ReportPtr & report );

            /*! @~russian
            Заменяет текст всех виджетов с текстом в отчете
            текстом с подставленными значениями параметров.
            Перегружанная функция, предоставленная для удобства.
            @param[in] report Указатель на отчет
            */
            bool     replaceParameters( const ReportPtr & report );

            /*! @~russian
            Возвращает текст с подставленными значениями полей из источника данных.
            @param[in] text Исходный текст
            @param[in] report Указатель на отчет
            @param[in] i Текущая строка
            */
            QString  replaceField( const QString & text, const ReportPtr & report, int i );

            /*! @~russian
            Возвращает изображение на основе первого найденного выражения.
            @param[in] text Исходный текст
            @param[in] report Указатель на отчет
            @param[in] i Текущая строка
            */
            QImage  replaceFieldImage( const QString & text, const ReportPtr & report, int i );

            /*! @~russian
            Заменяет текст виджета текстом с подставленными значениями полей из источника данных.
            Перегружанная функция, предоставленная для удобства.
            @param[in] widget Указатель на виджет
            @param[in] report Указатель на отчет
            @param[in] i Текущая строка
            */
            bool    replaceFieldInTextWidget( const TextWidgetPtr & widget, const ReportPtr & report, int i );

            /*! @~russian
            На основе текста виджета вставляет в него изображение из источника данных.
            Перегружанная функция, предоставленная для удобства.
            @param[in] widget Указатель на виджет
            @param[in] report Указатель на отчет
            @param[in] i Текущая строка
            */
            bool    replaceFieldInImageWidget( const ImagePtr & widget, const ReportPtr & report, int i );

            /*! @~russian
            Заменяет текст всех виджетов секции
            текстом с подставленными значениями полей из источника данных.
            Перегружанная функция, предоставленная для удобства.
            @param[in] section Указатель на секцию
            @param[in] report Указатель на отчет
            @param[in] i Текущая строка
            */
            bool    replaceFieldInSection( const SectionPtr & section, const ReportPtr & report, int i );

            /*! @~russian
            Заменяет текст всех виджетов секции
            текстом с подставленными значениями.
            Перегружанная функция, предоставленная для удобства.
            @param[in] section Указатель на секцию
            @param[in] report Указатель на отчет
            @param[in] i Текущая строка
            */
            bool    replace( const SectionPtr & section, const ReportPtr & report, int i );

            /*! @~russian
            Возвращает описание последней произошедшей ошибки.
            */
            const QString   getLastError() const;

        private:
            QString     m_lastError;

        };

    }
}

#endif // REPLACER_HPP
