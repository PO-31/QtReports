#pragma once
#ifndef GROUP_HPP
#define GROUP_HPP
#include <QString>
#include <QSharedPointer>
#include "section.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <group>

        Класс, реализующий тэг <group>
        */
        class Group : public Section {

        public:
            Group();
            ~Group();

            /*! @~russian
            Устанавливает <groupExpression>
            @param[in] text Значение <groupExpression>
            */
            void                                setExpression( const QString & text );

            /*! @~russian
            Возвращает значение <groupExpression>
            */
            const QString                       getExpression() const;

            /*! @~russian
            Устанавливает <groupHeader>
            @param[in] header Указатель на <groupHeader>
            */
            void                                setHeader( const SectionPtr & header );

            /*! @~russian
            Возвращает указатель на <groupHeader>
            */
            const SectionPtr                    getHeader() const;

            /*! @~russian
            Устанавливает <groupFooter>
            @param[in] footer Указатель на <groupFooter>
            */
            void                                setFooter( const SectionPtr & footer );

            /*! @~russian
            Возвращает указатель на <groupFooter>
            */
            const SectionPtr                    getFooter() const;

        private:
            QString     m_expression;
            SectionPtr  m_header;
            SectionPtr  m_footer;

        };
        typedef QSharedPointer< Group > GroupPtr;

    }
}

#endif // GROUP_HPP
