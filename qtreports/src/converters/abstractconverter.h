#pragma once
#ifndef ABSTRACTCONVERTER_H
#define ABSTRACTCONVERTER_H
#include <QString>

#include "../tags/report.hpp"
#include "utils/replacer.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Абстрактный класс, используемый для конвертации отчета в какой-либо формат.
        Конкретный формат определяется в классе-наследнике.
        */
        class AbstractConverter
        {
        public:
            /*!
            * @brief Конструктор по умолчанию.
            * @param report ссылка на объект ReportPtr.
            */
            AbstractConverter(const ReportPtr& report);

            /*!
            * @brief Виртуальный деструктор.
            */
            virtual ~AbstractConverter() = default;

            /*! @~russian
            Запускает процесс конвертации.
            @param[in] path Путь, по которому будет создан документ.
            @return @code{.cpp} true @endcode, если конвертация отчета прошла успешно, иначе @code{.cpp} false @endcode.
            */
            virtual bool convert(const QString & path) = 0;

            /*! @~russian
            Получить описание последней произошедшей ошибки.
            @return Строка с описанием последней произошедшей ошибки.
            */
            const QString getLastError() const;

        protected:

            /*! @~russian
            Объект класса ReportPtr
            */
            ReportPtr m_report;

            /*! @~russian
            Содержит информацию о последней ошибке, возникшей в процессе конвертации.
            */
            QString m_lastError;

            /*! @~russian
             * Добавляет группу в репорт.
             * Если не удалось добавить группу, вернет false.
             * @param[in] detail Ссылка на объект DetailPtr.
             * @return @code{.cpp} true @endcode, если добавление группы прошло успешно, иначе @code{.cpp} false @endcode.
            */
            bool addGroups(DetailPtr detail);

            /*! @~russian
            Добавление <band> в документ.

            @param[in] section Ссылка на объект Section, который содержит объект Band.
            Может указывать на такие секции, как:
            @code{.cpp} title, header, footer, detail @endcode
            @param[in] sectionIndex Индекс конкретной секции.

            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addBand(SectionPtr section, int sectionIndex) = 0;

            /*! @~russian
            Добавление текстовых полей в <band>.
            @param[in] band Ссылка на объект Band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addTextFields(BandPtr band) = 0;

            /*! @~russian
            Добавление статического текста в <band>.
            @param[in] band Ссылка на объект Band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addStaticTexts(BandPtr band) = 0;

            /*! @~russian
            Добавление изображений в <band>.
            @param[in] band Ссылка на объект Band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addImages(BandPtr band) = 0;

            /*! @~russian
            Добавление линий в <band>.
            @param[in] band Ссылка на объект Band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addLines(BandPtr band) = 0;

            /*! @~russian
            Добавление прямоугольников в <band>.
            @param[in] band Ссылка на объект Band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addRects(BandPtr band) = 0;

            /*! @~russian
            Добавление эллипсов в <band>.
            @param[in] band Ссылка на объект Band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addEllipses(BandPtr band) = 0;

            /*! @~russian
            Добавление объектов Crosstab в <band>.
            @param[in] band Ссылка на объект Band.
            @return @code{.cpp} true @endcode если добавление прошло успешно.
            @return @code{.cpp} false @endcode если добавление не удалось.
            */
            virtual bool addCrosstabs(BandPtr band) = 0;

        };

    }
}

#endif // ABSTRACTCONVERTER_H
