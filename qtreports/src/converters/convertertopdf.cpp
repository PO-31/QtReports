#include "convertertopdf.hpp"

#include <QPdfWriter>
#include <QPainter>
#include "utils/replacer.hpp"
#include "convertertoqwidget.hpp"

namespace qtreports {
    namespace detail {

        ConverterToPDF::ConverterToPDF(const ReportPtr & report) :
            m_report(report),
            m_currentResolution(75),
            m_currentHeight(0) {}


        ConverterToPDF::~ConverterToPDF() {}

        bool    ConverterToPDF::convert(const QString & path)
        {
            return create(path);
        }

        void    ConverterToPDF::setDPI(int dpi)
        {
            m_currentResolution = dpi;
        }

        int     ConverterToPDF::getDPI() const
        {
            return m_currentResolution;
        }

        bool    ConverterToPDF::create(const QString & path)
        {
            if(m_report.isNull()) {
                m_lastError = "Report is empty";
                return false;
            }

            QPdfWriter writer(path);
            writer.setCreator("QReports Library");
            writer.setTitle(m_report->getName());
            writer.setResolution(m_currentResolution);
            QPainter painter(&writer);
            QFont reportFont;
            QPen reportPen;

            // Настройка стилей. Стили считываются из отчета.
            auto &styles = m_report->getStyles();
            auto index = styles.begin();
            auto *style = (*index).data();
            reportFont.setFamily(style->getFontName());
            reportFont.setPointSize(style->getFontSize());
            style->isItalic() ? reportFont.setItalic(true) : reportFont.setItalic(false);
            style->isBold() ? reportFont.setBold(true) : reportFont.setBold(false);
            style->isUnderline() ? reportFont.setUnderline(true) : reportFont.setUnderline(false);
            style->isStrikeThrough() ? reportFont.setStrikeOut(true) : reportFont.setStrikeOut(false);
            reportPen.setColor(style->getFontColor());

            painter.setFont(reportFont);
            painter.setPen(reportPen);

            auto title = m_report->getTitle();
            if(!title.isNull())
            {
                if(!createSection(writer, painter, title, 0))
                {
                    m_lastError = "Report->Section is not created: title";
                    return false;
                }
            }

            auto detail = m_report->getDetail();
            if(detail.isNull())
            {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            if(!addGroupsIntoReport(writer, painter, m_report, detail))
                return false;

            auto summary = m_report->getSummary();
            if(!summary.isNull())
            {
                int lastField = m_report->getFieldsDataCount() - 1;
                if(!createSection(writer, painter, summary, lastField))
                {
                    m_lastError = "Report->Section is not created: summary";
                    return false;
                }
            }

            painter.end();
            return true;

        }

        bool ConverterToPDF::createSection(QPdfWriter &writer, QPainter &painter, const SectionPtr &section, int i)
        {
            detail::Replacer replacer;
            if(!replacer.replace(section, m_report, i))
            {
                m_lastError = "Error in replacing process: " + replacer.getLastError();
                return false;
            }

            if(!createBands(writer, painter, section))
            {
                m_lastError = "Error in creating bands process: " + replacer.getLastError();
                return false;
            }

            return true;
        }

        bool ConverterToPDF::createBands(QPdfWriter &writer, QPainter &painter, const SectionPtr &section)
        {
            for(auto && band: section->getBands())
            {
                if(m_currentHeight + band->getHeight() > m_report->getHeight())
                {
                    writer.newPage();
                    m_currentHeight = 0;
                }

                for(auto && textField : band->getTextFields()) {
                    if(textField->getText() != "") {
                        Qt::AlignmentFlag alignment = Qt::AlignCenter;
                        if ((textField->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                            alignment = Qt::AlignLeft;
                        if ((textField->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                            alignment = Qt::AlignRight;
                        if ((textField->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                            alignment = Qt::AlignCenter;
                        if ((textField->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                            alignment = Qt::AlignJustify;
                        int x = textField->getX();
                        int y = textField->getY();
                        int w = textField->getWidth();
                        int h = textField->getHeight();
                        painter.drawText(x, y + m_currentHeight, w, h, alignment, textField->getText());
                    }
                }

                for(auto && staticText : band->getStaticTexts()) {
                    if(staticText->getText() != "") {
                        Qt::AlignmentFlag alignment = Qt::AlignCenter;
                        if ((staticText->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                            alignment = Qt::AlignLeft;
                        if ((staticText->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                            alignment = Qt::AlignRight;
                        if ((staticText->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                            alignment = Qt::AlignCenter;
                        if ((staticText->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                            alignment = Qt::AlignJustify;

                        int x = staticText->getX();
                        int y = staticText->getY();
                        int w = staticText->getWidth();
                        int h = staticText->getHeight();
                        painter.drawText(x, y + m_currentHeight, w, h, alignment, staticText->getText());
                    }
                }

                for(auto && image : band->getImages()) {
                    QImage img = image->getImage();
                    QRect imageRect;
                    imageRect.setX(image->getX());
                    imageRect.setY(image->getY());
                    imageRect.setWidth(image->getWidth());
                    imageRect.setHeight(image->getHeight());
                    painter.drawImage(imageRect, img);
                }

                for(auto && line : band->getLines()) {
                    int x1 = line->getX();
                    int y1 = line->getY() + m_currentHeight;
                    int x2 = x1 + line->getWidth() - 1;
                    int y2 = y1 + line->getHeight();
                    QLine qline(x1, y1, x2, y2);
                    painter.drawLine(qline);
                }

                for(auto && rect : band->getRects()) {
                    QRect rectC;
                    rectC.setX(rect->getRect().x());
                    rectC.setY(rect->getRect().y() + m_currentHeight);
                    rectC.setHeight(rect->getRect().height());
                    rectC.setWidth(rect->getRect().width());
                    painter.drawRect(rectC);
                }

                for(auto && ellipse : band->getEllipses()) {
                    QRect rectE;
                    rectE.setX(ellipse->getRect().x());
                    rectE.setY(ellipse->getRect().y() + m_currentHeight);
                    rectE.setHeight(ellipse->getRect().height());
                    rectE.setWidth(ellipse->getRect().width());
                    painter.drawEllipse(rectE);
                }

                for(auto && crosstab : band->getCrosstabs())
                {
                    detail::Replacer replacer;

                    QList<QString> colGroups;
                    replacer.replaceColumnGroupsInCrosstab(crosstab, m_report, colGroups);

                    QList<QString> rowGroups;
                    replacer.replaceRowGroupsInCrosstab(crosstab, m_report, rowGroups);

                    QList<QString> cells;
                    replacer.replaceCellsInCrosstab(crosstab, m_report, cells);

                    QRect crosstabRect = crosstab->getRect();

                    auto rowGroup = crosstab->getRowGroup();
                    auto colGroup = crosstab->getColumnGroup();
                    auto cell     = crosstab->getCrosstabCell();

                    QRect emptyRect = QRect();
                    emptyRect.setX(crosstabRect.x());
                    emptyRect.setY(crosstabRect.y() + m_currentHeight);
                    emptyRect.setWidth(rowGroup->getWidth());
                    emptyRect.setHeight(cell->getHeight());
                    painter.drawRect(emptyRect);

                    int colX = crosstabRect.x() + rowGroup->getWidth();
                    for (int i = 0; i < colGroups.size(); i++)
                    {
                        Qt::AlignmentFlag alignment = Qt::AlignCenter;
                        if ((colGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                            alignment = Qt::AlignLeft;
                        if ((colGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                            alignment = Qt::AlignRight;
                        if ((colGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                            alignment = Qt::AlignCenter;
                        if ((colGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                            alignment = Qt::AlignJustify;

                        int x = colX + colGroup->getHeader()->getCellContents()->getTextField()->getX();
                        int y = crosstabRect.y() + colGroup->getHeader()->getCellContents()->getTextField()->getY();
                        int w = colGroup->getHeader()->getCellContents()->getTextField()->getWidth();
                        int h = colGroup->getHeader()->getCellContents()->getTextField()->getHeight();
                        painter.drawText(x, y + m_currentHeight, w, h, alignment, colGroups[i]);

                        QRect colRect = QRect();
                        colRect.setX(colX);
                        colRect.setY(crosstabRect.y() + m_currentHeight);
                        colRect.setWidth(cell->getWidth());
                        colRect.setHeight(colGroup->getHeight());
                        painter.drawRect(colRect);

                        colX += cell->getWidth();
                    }

                    int rowY = crosstabRect.y();
                    for (int i = 0; i < rowGroups.size(); i++)
                    {
                        rowY += cell->getHeight();

                        Qt::AlignmentFlag alignment = Qt::AlignCenter;
                        if ((rowGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                            alignment = Qt::AlignLeft;
                        if ((rowGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                            alignment = Qt::AlignRight;
                        if ((rowGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                            alignment = Qt::AlignCenter;
                        if ((rowGroup->getHeader()->getCellContents()->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                            alignment = Qt::AlignJustify;

                        int x = crosstabRect.x() + rowGroup->getHeader()->getCellContents()->getTextField()->getX();
                        int y = rowY + rowGroup->getHeader()->getCellContents()->getTextField()->getY();
                        int w = rowGroup->getHeader()->getCellContents()->getTextField()->getWidth();
                        int h = rowGroup->getHeader()->getCellContents()->getTextField()->getHeight();
                        painter.drawText(x, y + m_currentHeight, w, h, alignment, rowGroups[i]);

                        QRect rowRect = QRect();
                        rowRect.setX(crosstabRect.x());
                        rowRect.setY(rowY + m_currentHeight);
                        rowRect.setWidth(rowGroup->getWidth());
                        rowRect.setHeight(cell->getHeight());
                        painter.drawRect(rowRect);
                    }

                    int cellX = crosstabRect.x();
                    int cellY = crosstabRect.y();
                    int cellCount = 0;
                    for (int i = 0; i < rowGroups.size(); i++)
                    {
                        cellX += emptyRect.width();
                        cellY += emptyRect.height();
                        for(int j = 0; j < colGroups.size(); j++)
                        {
                            Qt::AlignmentFlag alignment = Qt::AlignCenter;
                            if ((cell->getCellContents()->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                                alignment = Qt::AlignLeft;
                            if ((cell->getCellContents()->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                                alignment = Qt::AlignRight;
                            if ((cell->getCellContents()->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                                alignment = Qt::AlignCenter;
                            if ((cell->getCellContents()->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                                alignment = Qt::AlignJustify;

                            int x = cellX + cell->getCellContents()->getTextField()->getX();
                            int y = cellY + cell->getCellContents()->getTextField()->getY();
                            int w = cell->getCellContents()->getTextField()->getWidth();
                            int h = cell->getCellContents()->getTextField()->getHeight();
                            painter.drawText(x, y + m_currentHeight, w, h, alignment, cells[cellCount]);

                            QRect cellRect = QRect();
                            cellRect.setX(cellX);
                            cellRect.setY(cellY + m_currentHeight);
                            cellRect.setWidth(cell->getWidth());
                            cellRect.setHeight(cell->getHeight());
                            painter.drawRect(cellRect);

                            cellCount++;
                            cellX += cell->getWidth();
                        }
                        cellX = crosstabRect.x();
                    }
                }

                m_currentHeight += band->getHeight();
            }

            return true;
        }

        const QString   ConverterToPDF::getLastError() const
        {
            return m_lastError;
        }

        bool ConverterToPDF::addGroupsIntoReport(QPdfWriter &writer, QPainter &painter, const ReportPtr &report, const DetailPtr &detail)
        {
            detail::Replacer replacer;
            QList<GroupPtr> groups = report->getGroups().values();
            QList<QString> groupNames;
            // Сюда помещаем конкретные имена по которым группируем
            QList<QString> particularNames;
            for(int i = 0; i < groups.length(); i++)
            {
                auto groupExpression = groups[i]->getExpression();
                if(groupExpression == "")
                {
                    return false;
                }
                groupNames.append(groupExpression);
                particularNames.append(replacer.replaceField(groupNames[i], report, 0));
            }

            // Открываем хедеры групп
            for(int i = 0; i < groups.length(); i++)
            {
                auto header = groups[i]->getHeader();
                if(!header.isNull())
                {
                    if(!createSection(writer, painter, header, 0))
                    {
                        return false;
                    }
                }
            }

            int rowCount = report->getRowCount();
            for(int i = 0; i < rowCount; i++)
            {
                // Закрываем футеры, если группа закончилась
                for(int j = groups.length() - 1; j >= 0; j--)
                {
                    // Сверяем поле в заголовке и текущее поле
                    if(particularNames[j] != replacer.replaceField(groupNames[j], report, i))
                    {
                        auto footer = report->getGroupByIndex(j)->getFooter();
                        if(!footer.isNull())
                        {
                            if(!createSection(writer, painter, footer, i - 1))
                            {
                                return false;
                            }
                        }
                    }
                }
                // Аналогично открываем хедеры
                for(int j = 0; j < groupNames.length(); j++)
                {
                    // Сверяем поле в заголовке и текущее поле
                    if(particularNames[j] != replacer.replaceField(groupNames[j], report, i))
                    {
                        auto header = report->getGroupByIndex(j)->getHeader();
                        if(!header.isNull())
                        {
                            if(!createSection(writer, painter, header, i))
                            {
                                return false;
                            }
                        }
                    }
                }
                // Переписываем имена для сравнения
                for(int j = 0; j < groupNames.length(); j++)
                {
                    particularNames[j] = replacer.replaceField(groupNames[j], report, i);
                }
                // Выводим поле
                if(!createSection(writer, painter, detail, i))
                {
                    return false;
                }
            }
            // Закрываем хедеры групп
            for(int i = groups.length() - 1; i >= 0; i--)
            {
                auto footer = groups[i]->getFooter();
                if(!footer.isNull())
                {
                    if(!createSection(writer, painter, footer, (rowCount - 1)))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

    }
}
