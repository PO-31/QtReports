#include "cellcontents.hpp"

namespace qtreports
{
    namespace detail
    {
        CellContents::CellContents() {}
        CellContents::~CellContents() {}

        void CellContents::setBox(const BoxPtr &box)
        {
            m_boxPtr = box;
        }

        void CellContents::setTextField(const TextFieldPtr &textField)
        {
            m_textFieldPtr = textField;
        }

        const BoxPtr CellContents::getBox() const
        {
            return m_boxPtr;
        }

        const TextFieldPtr CellContents::getTextField() const
        {
            return m_textFieldPtr;
        }
    }
}
