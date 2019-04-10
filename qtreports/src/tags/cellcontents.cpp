#include "cellcontents.hpp"

namespace qtreports
{
    namespace detail
    {
        CellContents::CellContents() {}
        CellContents::~CellContents() {}

        void CellContents::setTextField(const TextFieldPtr &textField)
        {
            m_textField = textField;
        }

        const TextFieldPtr CellContents::getTextField() const
        {
            return m_textField;
        }
    }
}
