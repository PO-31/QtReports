#pragma once
#ifndef CROSSTAB_HPP
#define CROSSTAB_HPP

#include "widget.hpp"
#include "crosstabgroup.hpp"
#include "crosstabcell.hpp"

namespace qtreports
{
    namespace detail
    {
        class Crosstab : public Widget
        {
        private:
            bool isRepeatColumnHeaders;//отображение заголовков колонок и строк
            bool isRepeatRowHeaders;   //при переносе на следующую строку

            //указывает вертикальное пространство между разделами кросстаблицы, когд
            // кросстаблица превышает гирину таблицы и два раздела отображаются на одной сранице
            int columnBreakOffset;
            //Направление заполнения таблицы. По умолчанию слева направо
            bool runDirectionLeftToRight;
            //Ограничение таблицы на расширение по горизонтали.
            bool ignoreWidth;
            // подтэги
            CrosstabGroupPtr    m_rowGroup;
            CrosstabGroupPtr    m_columnGroup;
            CrosstabCellPtr     m_crosstabCell;
        public:
            Crosstab();
            ~Crosstab();
            void                    setRowGroup(const CrosstabGroupPtr &rowGroup);
            const CrosstabGroupPtr  getRowGroup();
            void                    setColumnGroup(const CrosstabGroupPtr &columnGroup);
            const CrosstabGroupPtr  getColumnGroup();
            void                    setCrosstabCell(const CrosstabCellPtr &crosstabCell);
            const CrosstabCellPtr   getCrosstabCell();

            void setColumnHeadersRepeating(bool value);
            void setRowHeadersRepeating(bool value);
            void setWidthIgnoring(bool value);
            void setRunDirectionLeftToRight(bool value);
            void setColumnBreakOffset(int value);

            bool getColumnHeadersRepeating();
            bool getRowHeadersRepeating();
            bool getWidthIgnoring();
            bool getRunDirectionLeftToRight();
            int getColumnBreakOffset();
        };
        typedef QSharedPointer<Crosstab> CrosstabPtr;
    }
}

#endif // CROSSTAB_HPP
