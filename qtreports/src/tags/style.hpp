#pragma once
#ifndef STYLE_HPP
#define STYLE_HPP

#include <QString>
#include <QColor>
#include <QSharedPointer>

#include "object.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <style>
        
        Класс, реализующий тэг <style>
        */
        class Style : public Object {

        public:
            Style();
            ~Style();

            /*! @~russian
            Возвращает, является ли данный стиль стилем по умолчанию
            */
            bool	        isDefault() const;
            
            /*! @~russian
            Устанавливает, является ли текущий стиль стилем по умолчанию
            @param[in] flag Новое значение
            */            
            void	        setAsDefault( bool flag );

            /*! @~russian
            Возвращает название шрифта
            */
            const QString	getFontName() const;
            
            /*! @~russian
            Устанавливает название шрифта
            @param[in] name Название шрифта
            */            
            void	        setFontName( const QString & name );

            /*! @~russian
            Возвращает размер шрифта
            */
            int		        getFontSize() const;
            
            /*! @~russian
            Устанавливает размер шрифта
            @param[in] size Размер шрифта
            */  
            void	        setFontSize( int size );

            /*! @~russian
            Возвращает цвет шрифта
            */
            const QColor	getFontColor() const;
            
            /*! @~russian
            Устанавливает цвет шрифта
            @param[in] color Цвет шрифта
            */
            void	        setFontColor( const QColor & color );

            /*! @~russian
            Возвращает, является ли шрифт жирным или нет
            */
            bool	        isBold() const;
            
             /*! @~russian
            Устанавливает, является ли шрифт жирным или нет
            @param[in] flag Новое значение
            */
            void	        setBold( bool flag );

            /*! @~russian
            Возвращает, является ли шрифт курсивом или нет
            */
            bool	        isItalic() const; 
            
             /*! @~russian
            Устанавливает, является ли шрифт курсивом или нет
            @param[in] flag Новое значение
            */
            void	        setItalic( bool flag );

            /*! @~russian
            Возвращает, является ли шрифт подчеркнутым или нет
            */
            bool	        isUnderline() const;
            
             /*! @~russian
            Устанавливает, является ли шрифт подчеркнутым или нет
            @param[in] flag Новое значение
            */
            void	        setUnderline( bool flag );

            /*! @~russian
            Возвращает, является ли шрифт перечеркнутым или нет
            */
            bool	        isStrikeThrough() const;
            
             /*! @~russian
            Устанавливает, является ли шрифт перечеркнутым или нет
            @param[in] flag Новое значение
            */
            void	        setStrikeThrough( bool flag );

            /*! @~russian
            Возвращает название шрифта в PDF
            */
            const QString	getPDFFontName() const;
            
            /*! @~russian
            Устанавливает название шрифта в PDF
            @param[in] name Название шрифта
            */  
            void	        setPDFFontName( const QString & name );

            /*! @~russian
            Возвращает название кодировки в PDF
            */
            const QString	getPDFEncoding() const;
            
             /*! @~russian
            Устанавливает название кодировки в PDF
            @param[in] encoding Название кодировки
            */  
            void	        setPDFEncoding( const QString & encoding );

            /*! @~russian
            Возвращает ... в PDF
            */   
            bool	        isPDFEmbedded() const;
            
            /*! @~russian
            Устанавливает ... в PDF
            @param[in] isEmbedded Новое значение
            */              
            void	        setPDFEmbedded( bool isEmbedded );

        private:
            bool        m_isDefault;
            bool        m_isBold;
            bool        m_isItalic;
            bool        m_isUnderline;
            bool        m_isStrikeThrough;
            int         m_fontSize;
            bool        m_isPDFEmbedded;
            QColor      m_fontColor;
            QString     m_fontName;
            QString     m_pdfFontName;
            QString     m_pdfEncoding;

        };
        typedef QSharedPointer< Style > StylePtr;

    }
}

#endif // STYLE_HPP
