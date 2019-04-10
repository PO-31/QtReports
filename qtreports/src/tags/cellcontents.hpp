#pragma once
#ifndef CELLCONTENTS_HPP
#define CELLCONTENTS_HPP

#include "widget.hpp"
#include "textfield.hpp"

namespace qtreports
{
    namespace detail
    {
        class CellContents: public Widget {
        public:
            CellContents();
            ~CellContents();

            void                    setTextField(const TextFieldPtr & textField);
            const TextFieldPtr      getTextField() const;

        private:
            TextFieldPtr    m_textField;
        };
        typedef QSharedPointer<CellContents> CellContentsPtr;
    }
}
#endif // CELLCONTENTS_HPP
