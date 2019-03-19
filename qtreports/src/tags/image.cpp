#include "image.hpp"

namespace qtreports
{
    namespace detail
    {

        Image::Image() {}

        Image::~Image() {}

        const QImage    Image::getImage()
        {
            return m_image;
        }

        void    Image::setImage( const QImage & image )
        {
            m_image = image;
        }

    }
}
