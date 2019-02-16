#pragma once
#ifndef FIELD_HPP
#define FIELD_HPP
#include <QSharedPointer>

#include <QVariant>
#include <QString>
#include <QVector>
#include <QImage>

#include <qtreports/tags/object.hpp>

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <field>

        Класс, реализующий тэг <field>
        */
        class Field : public Object {

        public:
            Field();
            ~Field();

            /*! @~russian
            Устанавливает атрибут className
            @param[in] name Название класса
            */
            void            setClassName( const QString & name );

            /*! @~russian
            Возвращает атрибут className.
            */
            const QString   getClassName() const;

            /*! @~russian
            Устанавливает содержимое <field>
            @param[in] data Вектор, содержащие данные <field>
            */
            void            setData( const QVector< QVariant > & data );

            /*! @~russian
            Возвращает содержимое <field>
            @param[in] row Номер строки
            */
            QString         getData( int row );

            /*! @~russian
            Возвращает содержимое <field>. Шаблонный вариант.
            @param[in] row Номер строки
            */
            template< typename T1 >
            const T1        getData( int row );

            const QVariant getDataVar(int row);

            void setDataVar(int row, const QVariant & value);

            /*! @~russian
            Получить количество строк в <field>
            */
            int             getRowCount();

        private:
            QString                 m_className;
            QVector< QVariant >     m_data;

        };

        typedef QSharedPointer< Field > FieldPtr;
    }
}

#endif // FIELD_HPP
