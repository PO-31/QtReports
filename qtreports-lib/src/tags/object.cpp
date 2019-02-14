#include "object.hpp"

namespace qtreports {
    namespace detail {
        bool    isEquals( const QString & string1, const QString & string2 ) {
            return string1.compare( string2, Qt::CaseInsensitive ) == 0;
        }

        Object::Object() {}

        Object::Object( const QString & name ) :
            m_name( name ) {}

        Object::~Object() {}

        void    Object::setName( const QString & name ) {
            m_name = name;
        }

        void    Object::setTagName( const QString & name ) {
            m_tagName = name;
        }
        /*
        bool    Object::setParameter( const QString & name, const QVariant & value ) {
            QString _name( "name" );

            if( !value.isValid() ) {
                m_lastError = "Invalid parameter value";
                return false;
            }

            if( isEquals( _name, name ) ) {
                if( value.type() != QVariant::String ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_name = value.toString();
                return true;
            }

            m_lastError = "Unknown argument";
            return false;
        }
        */
        const QString   Object::getName() const {
            return m_name;
        }

        const QString   Object::getTagName() const {
            return m_tagName;
        }

        const QString	Object::getLastError() const {
            return m_lastError;
        }

    }
}
