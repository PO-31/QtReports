#pragma once
#ifndef CONVERTERTOQWIDGET_HPP
#define CONVERTERTOQWIDGET_HPP
#include <QString>
#include <QWidget>
#include <QFrame>
#include <QBoxLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../tags/report.hpp"

namespace qtreports {
    typedef QSharedPointer< QWidget > QWidgetPtr;

    namespace detail {
	/*! @~russian
    * @brief Класс ConverterToQWidget
    * Класс Для преобразования отчета в объект типа QWidget.
	*/
    class ConverterToQWidget {

        public:
            /*!
            * @brief Конструктор по умолчанию.
            * @param report ссылка на объект ReportPtr.
            */
            explicit ConverterToQWidget(const ReportPtr & report);
            ~ConverterToQWidget();

            /*! @~russian
            Тип создаваемого виджета.
            */
            enum class WidgetType {
                Report = 0, ///< Отчет
                Layout ///< Макет
            };

            /*! @~russian
            Конвертирует отчет в виджет. По умолчанию тип виджета WidgetType::Report.
            @return @code{.cpp} true @endcode, если конвертация отчета в виджет прошла успешно,
            иначе @code{.cpp} false @endcode.
            @see ConverterToQWidget::WidgetType
            */
            bool                convert(WidgetType type = WidgetType::Report);

            /*! @~russian
            Проверяет, является ли виджет типа WidgetType::Report.
            @return @code{.cpp} true @endcode, если виджет типа WidgetType::Report,
            иначе @code{.cpp} false @endcode.
            @see ConverterToQWidget::WidgetType
            */
            bool                            isReport() const;

            /*! @~russian
            Проверяет, является ли виджет типа WidgetType::Layout.
            @return @code{.cpp} true @endcode, если виджет типа WidgetType::Layout,
            иначе @code{.cpp} false @endcode.
            @see ConverterToQWidget::WidgetType
            */
            bool                            isLayout() const;

            /*! @~russian
            Возвращает текущий тип виджета.
            */
            WidgetType                      getType() const;

            /*! @~russian
            Возвращает указатель на объект QWidget. Если объект QWidget не был создан,
            то возвращается @code{.cpp} nullptr @endcode.
            */
            const QWidgetPtr                getQWidget() const;

            /*! @~russian
            Возвращает указатель страницы виджета по индексу.
            */
            const QWidgetPtr                getPage(int i) const;

            /*! @~russian
            Возвращает список всех страниц виджета.
            */
            const QVector< QWidgetPtr >     getPages() const;

            /*! @~russian
            Возвращает информацию о последней ошибке, возникшей в процессе конвертации.
            */
            const QString                   getLastError() const;

        private:
            /*! @~russian
            Указатель на отчет, который будет конвертироваться.
            */
            ReportPtr               m_report;

            /*! @~russian
            Содержит информацию о последней ошибке, возникшей в процессе конвертации.
            */
            QString                 m_lastError;

            /*! @~russian
            Указатель на создаваемый QWidget.
            */
            QWidgetPtr              m_qwidget;

            /*! @~russian
            Содержит информацию о типе виждета.
            @see ConverterToQWidget::WidgetType
            */
            WidgetType              m_type;

            /*! @~russian
            Содержит список страниц создаваемого виждета.
            */
            QVector< QWidgetPtr >   m_pages;

            /*! @~russian
            Содержит текущую высоту виджета.
            @see ConverterToQWidget::WidgetType
            */
            int                     m_currentHeight;

            /*! @~russian
            Добавляет вертикальную границу.
            @param parent Указатель на QBoxLayout, на который добавляется вертикальная граница.
            @param margins Содержит информацию об отступах для данного QBoxLayout.
            @param height Значение высоты секции.
            */
            void        addVerticalBorder(QBoxLayout * parent, const QMargins & margins, int height);

            /*! @~russian
            Добавляет пустую секцию.
            @param parent Указатель на QBoxLayout, на который пустая секция.
            @param margins Содержит информацию об отступах для данного QBoxLayout.
            */
            void        addEmptySection(QBoxLayout * parent, const QMargins & margins);

            /*! @~russian
            Добавляет секцию.
            @param parent Указатель на QBoxLayout, на который добавляется секция.
            @param margins Содержит информацию об отступах для данного QBoxLayout.
            @param height Значение высоты секции.
            */
            QFrame *    addSectionLayout(QBoxLayout * parent, const QMargins & margins, int height);
            
            /*! @~russian
            Добавляет новую страницу на виджет.
            */
            void        addPage();


			/*! @~russian
            @brief Функция добавления группировок в отчет.
            @param report Указатель на отчет, с которым ведется работа.
            @param detail Указатель на блок detail, в котором будут отображаться данные.
            @param layout Указатель на layout, который является непосредственным контейнером данных.
            @return true, если добавление группы произошло успешно, иначе false.
			*/
			bool        addGroupsIntoReport(const ReportPtr & report, const DetailPtr & detail, QVBoxLayout* layout);

            /*! @~russian
            @brief Конвертирует отчет в QWidget.
            @param report Указатель на отчет, с которым ведется работа.
            @return true, если добавление группы произошло успешно, иначе false.
            */
            bool        createQWidget(const ReportPtr & report);

            /*! @~russian
             * Создает секцию.
             * Если не удалось создать секцию, вернет false.
             * Информация об ошибке содержится в переменной m_lastError.
             * @param parent указатель на объект QWidget, на котором создается секция.
             * @param section Ссылка на объект SectionPtr. SectionPtr может указывать на такие секции, как:
             * @code{.cpp} title, header, footer, detail @endcode.
             * @param i Индекс текущей секции.
             * @return @code{.cpp} true @endcode, если создание секции прошло успешно, иначе @code{.cpp} false @endcode.
            */
            bool        createSection(QWidget * parent, const SectionPtr & section, int i);

            /*! @~russian
             * Создает band.
             * @param parent указатель на объект QWidget, на котором создается band.
             * @param[in] section Ссылка на объект SectionPtr.
             * @return @code{.cpp} true @endcode, если создание bsnd'a прошло успешно, иначе @code{.cpp} false @endcode.
            */
            bool        createBands(QWidget * parent, const SectionPtr & section);

        };

    }
}
#endif // CONVERTERTOQWIDGET_HPP
