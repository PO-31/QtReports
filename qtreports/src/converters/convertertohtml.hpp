#pragma once
#ifndef CONVERTERTOHTML_HPP
#define CONVERTERTOHTML_HPP
#include <QString>
#include <QBuffer>

#include "../tags/report.hpp"

namespace qtreports {
    namespace detail {

        class ConverterToHTML {

        public:
            ConverterToHTML( const ReportPtr & report );
            ~ConverterToHTML();

            bool    convert();
            bool    convert( const QString & path );

            const QString   getLastError() const;
            const QString   getHTML() const;

        private:
            ReportPtr   m_report;
            QString     m_lastError;
            QString     m_html;

            QString     m_defaultStyleName;

            bool        createHTML();
            bool        addGroups(QSharedPointer<Detail> detail);
            bool        addSection(QSharedPointer<Section> detail, int detailIndex);
            void        drawShapes(QSharedPointer< Band > band, QString &elementStr);
        };

    }
}
#endif // CONVERTERTOHTML_HPP
