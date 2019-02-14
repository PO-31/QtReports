#pragma once
#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <QImage>
#include <QSharedPointer>
#include "textwidget.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <image>

        Класс, реализующий тэг <image>
        */
        class Image : public TextWidget {

        public:
            Image();
            ~Image();

            /*! @~russian
            Устанавливает изображение <image>
            @param[in] image Изображение
            */
            void            setImage( const QImage & image );

            /*! @~russian
            Возвращает изображение <image>
            */
            const QImage    getImage();

        private:
            QImage          m_image;

        };
        typedef QSharedPointer< Image > ImagePtr;

    }
}

#endif // IMAGE_HPP
