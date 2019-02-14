#include "querystring.hpp"

namespace qtreports {
    namespace detail {

        QueryString::QueryString() {}

        QueryString::~QueryString() {}

        void    QueryString::setText( const QString & text ) {
            m_text = text;
        }

        const QString   QueryString::getText() const {
            return m_text;
        }

    }
}
