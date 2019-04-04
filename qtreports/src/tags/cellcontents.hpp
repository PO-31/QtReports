#pragma once
#ifndef CELLCONTENTS_HPP
#define CELLCONTENTS_HPP


#include <QString>
#include <QSharedPointer>

#include "box.hpp"
#include "textfield.hpp"

namespace qtreports
{
    namespace detail
    {
        class CellContents: public Object {
        public:
            CellContents();
            ~CellContents();

            void setBox(const BoxPtr & box);
            void setTextField(const TextFieldPtr & textField);
            const BoxPtr getBox() const;
            const TextFieldPtr getTextField() const;

        private:
            BoxPtr m_boxPtr;
            TextFieldPtr m_textFieldPtr;
        };
        typedef QSharedPointer<CellContents> CellContentsPtr;
    }
}
#endif // CELLCONTENTS_HPP
