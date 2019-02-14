#include "report.hpp"

namespace qtreports
{
    namespace detail
    {

        Report::Report() :
            m_orientation( QPrinter::Orientation::Portrait ),
            m_size( 595, 842 ),
            m_margins( 30, 30, 30, 30 )
        {}

        Report::~Report() {}

        void    Report::setDefaultStyle( const StylePtr & style )
        {
            m_defaultStyle = style;
        }

        const StylePtr  Report::getDefaultStyle() const
        {
            return m_defaultStyle;
        }

        void    Report::addStyle( const QString & name, const StylePtr & style )
        {
            m_styles[ name ] = style;
        }

        const StylePtr  Report::getStyle( const QString & name ) const
        {
            return m_styles.value( name );
        }

        const QMap< QString, StylePtr >     Report::getStyles() const
        {
            return m_styles;
        }

        void    Report::addGroup( const QString & name, const GroupPtr & group )
        {
            m_groups[ name ] = group;
        }

        const GroupPtr  Report::getGroup( const QString & name ) const
        {
            return m_groups.value( name );
        }

        const QMap< QString, GroupPtr >     Report::getGroups() const
        {
            return m_groups;
        }

        void    Report::setQuery( const QString & query )
        {
            m_query = query;
        }

        const QString   Report::getQuery() const
        {
            return m_query;
        }

        void    Report::setField( const QString & name, const FieldPtr & field )
        {
            m_fields[ name ] = field;
        }

        const FieldPtr  Report::getField( const QString & name ) const
        {
            return m_fields.value( name );
        }

        const QMap< QString, FieldPtr >   Report::getFields() const
        {
            return m_fields;
        }

        void    Report::setFieldData( const QString & name, const QVector< QVariant > & data )
        {
            auto field = getField( name );
            if( !field.isNull() )
            {
                field->setData( data );
            }
        }

        void    Report::setTitle( const TitlePtr & title )
        {
            m_title = title;
        }

        const TitlePtr     Report::getTitle() const
        {
            return m_title;
        }

        void    Report::setDetail( const DetailPtr & detail )
        {
            m_detail = detail;
        }

        const DetailPtr     Report::getDetail() const
        {
            return m_detail;
        }

        void    Report::setParameter( const QString & name, const QVariant & value )
        {
            m_parameters[ name ] = value;
        }

        void    Report::setParameters( const QMap< QString, QVariant > & parameters )
        {
            m_parameters = parameters;
        }

        const QVariant  Report::getParameter( const QString & name ) const
        {
            return m_parameters.value( name );
        }

        const QMap< QString, QVariant >   Report::getParameters() const
        {
            return m_parameters;
        }

        int     Report::getRowCount() const
        {
            int max = 0;
            for( auto && field : getFields() )
            {
                max = std::max( max, field->getRowCount() );
            }

            return max;
            //return m_rowCount;
        }

        void    Report::setOrientation( QPrinter::Orientation orientation )
        {
            m_orientation = orientation;
        }

        QPrinter::Orientation     Report::getOrientation() const
        {
            return m_orientation;
        }

        void    Report::setSize( const QSize & size )
        {
            //m_size = QPrinter::Orientation::Portrait ? size : size.transposed();
            m_size = size;
        }

        const QSize     Report::getSize() const
        {
            return m_orientation == QPrinter::Orientation::Portrait ? m_size : m_size.transposed();
        }

        void Report::setWidth( int width )
        {
            //if( m_orientation == QPrinter::Orientation::Portrait )
            //{
                m_size.setWidth( width );
            //}
            //else
            //{
            //    m_size.setHeight( width );
            //}
        }

        int     Report::getWidth() const
        {
            return getSize().width();
        }

        void Report::setHeight( int height )
        {
            //if( m_orientation == QPrinter::Orientation::Portrait )
            //{
                m_size.setHeight( height );
            //}
            //else
            //{
            //    m_size.setWidth( height );
            //}
        }

        int     Report::getHeight() const
        {
            return getSize().height();
        }

        void    Report::setLeftMargin( int left )
        {
            m_margins.setLeft( left );
        }

        int     Report::getLeftMargin() const
        {
            return m_margins.left();
        }

        void    Report::setTopMargin( int top )
        {
            m_margins.setTop( top );
        }

        int     Report::getTopMargin() const
        {
            return m_margins.top();
        }

        void    Report::setRightMargin( int right )
        {
            m_margins.setRight( right );
        }

        int     Report::getRightMargin() const
        {
            return m_margins.right();
        }

        void    Report::setBottomMargin( int bottom )
        {
            m_margins.setBottom( bottom );
        }

        int     Report::getBottomMargin() const
        {
            return m_margins.bottom();
        }

        void    Report::setMargins( int left, int top, int right, int bottom )
        {
            setLeftMargin( left );
            setTopMargin( top );
            setRightMargin( right );
            setBottomMargin( bottom );
        }

        void    Report::setMargins( const QMargins & margins )
        {
            m_margins = margins;
        }

        const QMargins  Report::getMargins() const
        {
            return m_margins;
        }

        bool Report::isDetailHasGroupHeader(int detailNum, const QString &groupField)
        {
            int groupIndex = getGroupIndexFromField(groupField);

            if(groupIndex == 0) {
                if(detailNum == 0)
                    return true;
                else {
                    if(m_fields[groupField].data()->getData(detailNum) !=
                            m_fields[groupField].data()->getData(detailNum - 1)) {
                        return true;
                    }
                    else
                        return false;
                }
            }
            else {
                for(int ind = 0; ind <= groupIndex; ind++) {
                    QString parentGroupField = getFieldFromGroupExpression(getGroupByIndex(ind).data()->getExpression());
                    if(detailNum == 0)
                        return true;
                    else {
                        if(m_fields[parentGroupField].data()->getData(detailNum) !=
                                m_fields[parentGroupField].data()->getData(detailNum - 1))
                            return true;
                    }
                }
                return false;
            }
        }

        bool Report::isDetailHasGroupFooter(int detailNum, const QString &groupField)
        {
            int groupIndex = getGroupIndexFromField(groupField);

            if(groupIndex == 0) {
                if(detailNum == getRowCount() - 1)
                    return true;
                else {
                    if(m_fields[groupField].data()->getData(detailNum) !=
                            m_fields[groupField].data()->getData(detailNum + 1)) {
                        return true;
                    }
                    else
                        return false;
                }
            }
            else {
                for(int ind = 0; ind <= groupIndex; ind++) {
                    QString parentGroupField = getFieldFromGroupExpression(getGroupByIndex(ind).data()->getExpression());
                    if(detailNum == getRowCount() - 1)
                        return true;
                    else {
                        if(m_fields[parentGroupField].data()->getData(detailNum) !=
                                m_fields[parentGroupField].data()->getData(detailNum + 1))
                            return true;
                    }
                }
                return false;
            }
        }

        void Report::reorderByGroups()
        {
            int rowCount = getRowCount();
            m_group_vec = QVector<bool>(rowCount);
            QMapIterator<QString, GroupPtr> groupIterator(getGroups());
            while(groupIterator.hasNext()) {
                groupIterator.next();
                QString fieldName = getFieldFromGroupExpression(groupIterator.value().data()->getExpression());
                FieldPtr field = getField(fieldName);
                int currentIndex = 0;
                while(currentIndex != field.data()->getRowCount() - 1) {
                    if(m_group_vec[currentIndex] == true) {
                        currentIndex++;
                        continue;
                    }
                    for(int i = currentIndex + 1; i < rowCount; i++) {
                        QString currentData = field.data()->getData(currentIndex);
                        if(field.data()->getData(i) == currentData) {
                            swapRows(i - 1, currentIndex + 1, m_group_vec);
                            currentIndex++;
                            m_group_vec[currentIndex] = true;
                        }
                    }
                    if(currentIndex != field.data()->getRowCount() - 1) currentIndex++;
                }
            }
        }

        const QString Report::getFieldFromGroupExpression(const QString &expression)
        {
            QRegularExpression regExpression(".*\\$F\\{(.*)\\}.*");
            QRegularExpressionMatch match = regExpression.match(expression);
            if(match.hasMatch()) {
                return match.captured(1);
            }
            else
                return "";
        }

        int Report::getGroupIndexFromField(const QString &field)
        {
            QMapIterator<QString, GroupPtr> groupIt(m_groups);
            int index = 0;
            while(groupIt.hasNext()) {
                groupIt.next();
                if(QString::compare(getFieldFromGroupExpression(groupIt.value().data()->getExpression()), field) == 0) {
                    return index;
                }
                index++;
            }
            return -1;
        }

        GroupPtr  Report::getGroupByIndex( int index )
        {
            return m_groups.value( m_groups.keys().value( index ) );
        }

        void Report::swapRows(int row1, int row2, QVector<bool> &vec)
        {
            for(auto && field : m_fields) {
                QVariant temp = field.data()->getDataVar(row1);
                field.data()->setDataVar(row1, field.data()->getDataVar(row2));
                field.data()->setDataVar(row2, temp);
            }

            bool tempVec = vec[row1];
            vec[row2] = vec[row1];
            vec[row1] = tempVec;
        }
    }
}
