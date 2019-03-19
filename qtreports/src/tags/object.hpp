#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <QString>
#include <QVariant>
#include <QSharedPointer>

namespace qtreports {
    namespace detail {
        bool    isEquals( const QString & string1, const QString & string2 );

        /*! @~russian
        @brief Базовый класс для любого тэга
        
        Базовый класс для любого тэга
        */
        class Object {

        public:
            Object();
            
            /*! @~russian
            Конструктор, создается обьект с именем
            @param[in] name Имя обьекта
            */
            Object( const QString & name );
            virtual ~Object();

            /*! @~russian
            Устанавливает значение атрибута name
            @param[in] name Значение атрибута name
            */
            void            setName( const QString & name );
            
            /*! @~russian
            Возвращает значение атрибута name
            */
            const QString   getName() const;
            
            /*! @~russian
            Устанавливает название тэга
            @param[in] name Название тэга
            */            
            void            setTagName( const QString & name );

            /*! @~russian
            Возвращает название тэга
            */
            const QString   getTagName() const;
            
            /*! @~russian
            Возвращает описание последней ошибки
            */
            const QString	getLastError() const;

        protected:
            QString     m_name;
            QString     m_tagName;
            QString     m_lastError;

        };
        typedef QSharedPointer< Object > ObjectPtr;

    }
}

#endif // OBJECT_HPP
