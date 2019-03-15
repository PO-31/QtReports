#include "section.hpp"

namespace qtreports
{
    namespace detail
    {

        Section::Section() :
            m_width( 0 ),
            m_height( 0 )
        {}

        Section::~Section() {}

        void    Section::setWidth( int width )
        {
            m_width = width;
        }

        int     Section::getWidth() const
        {
            return m_width;
        }

        int     Section::getHeight() const
        {
            return m_height;
        }

        void    Section::addBand( const BandPtr & band )
        {
            m_bands.append( band );
            m_height += band->getHeight();
        }

        const BandPtr  Section::getBand( int index ) const
        {
            return m_bands.value( index );
        }

        int     Section::getBandsSize() const
        {
            return m_bands.size();
        }

        const QVector< BandPtr >    Section::getBands() const
        {
            return m_bands;
        }

    }
}
