#include "textwidget.hpp"

namespace qtreports
{
    namespace detail
    {

        TextWidget::TextWidget() {}

        TextWidget::~TextWidget() {}

        void    TextWidget::setText( const QString & text )
        {
            m_text = text;
        }

        const QString   TextWidget::getText() const
        {
            return m_text.isEmpty() ? m_originalText : m_text;
        }

        void    TextWidget::setOriginalText( const QString & text )
        {
            m_originalText = text;
        }

        const QString   TextWidget::getOriginalText() const
        {
            return m_originalText;
        }

    }
}
