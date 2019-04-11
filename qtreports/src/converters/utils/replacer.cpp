#include "replacer.hpp"

#include <QRegularExpression>
#include <QImage>
#include <QByteArray>
#include <QDebug>
#include <QList>
#include <QSet>

namespace qtreports
{
    namespace detail
    {

        Replacer::Replacer() {}

        Replacer::~Replacer() {}

        QString     Replacer::replaceParameters(const QString & text, const ReportPtr & report)
        {
            auto newText = text;
            QRegularExpression expr("(\\$P\\{\\w+\\})", QRegularExpression::CaseInsensitiveOption);
            auto iterator = expr.globalMatch(newText);
            while(iterator.hasNext())
            {
                auto match = iterator.next();
                auto name = match.captured(1).remove(0, 3).remove(-1, 1);
                auto parameter = report->getParameter(name);
                newText.replace(match.captured(1), parameter.toString()); //need fix for classname
            }

            return newText;
        }

        bool    Replacer::replaceParametersInTextWidget(const TextWidgetPtr & widget, const ReportPtr & report)
        {
            auto text = widget->getText();
            auto replacedText = replaceParameters(text, report);
            widget->setText(replacedText);

            return true;
        }

        bool    Replacer::replaceParametersInSection(const SectionPtr & section, const ReportPtr & report)
        {
            if(section.isNull())
            {
                m_lastError = "Section is empty.";
                return false;
            }

            for(auto && band : section->getBands())
            {
                for(auto && textWidget : band->getTextWidgets())
                {
                    if(!replaceParametersInTextWidget(textWidget, report))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool    Replacer::replaceParameters(const ReportPtr & report)
        {
            if(report.isNull())
            {
                m_lastError = "Report is empty.";
                return false;
            }

            auto detail = report->getDetail();
            if(detail.isNull())
            {
                m_lastError = "Report->Detail is empty.";
                return false;
            }

            if(!replaceParametersInSection(detail, report))
            {
                return false;
            }

            auto title = report->getTitle();
            if(!title.isNull() && !replaceParametersInSection(title, report))
            {
                return false;
            }

            auto summary = report->getSummary();
            if(!summary.isNull() && !replaceParametersInSection(summary, report))
            {
                return false;
            }

            return true;
        }

        QString     Replacer::replaceField(const QString & text, const ReportPtr & report, int i)
        {
            auto newText = text;
            QRegularExpression expr("(\\$F\\{\\w+\\})", QRegularExpression::CaseInsensitiveOption);
            auto iterator = expr.globalMatch(newText);
            while(iterator.hasNext())
            {
                auto match = iterator.next();
                auto name = match.captured(1).remove(0, 3).remove(-1, 1);
                auto parameter = report->getField(name)->getData(i);
                newText.replace(match.captured(1), parameter);
            }

            return newText;
        }

        QImage  Replacer::replaceFieldImage(const QString & text, const ReportPtr & report, int i)
        {
            QRegularExpression expr("(\\$F\\{\\w+\\})", QRegularExpression::CaseInsensitiveOption);
            auto iterator = expr.globalMatch(text);
            while(iterator.hasNext())
            {
                auto match = iterator.next();
                auto name = match.captured(1).remove(0, 3).remove(-1, 1);
                auto byteArray = report->getField(name)->getData< QByteArray >(i);
                auto image = QImage::fromData(byteArray);
                return image;
            }

            return QImage();
        }

        bool Replacer::replaceRowGroupsInCrosstab(const CrosstabPtr & crosstab, const ReportPtr & report, QList<QString> & rowGroups)
        {
            replaceRowGroupInCrosstab(crosstab, report, 0);
            QList<QString> oldValues;
            QString value = crosstab->getRowGroup()->getHeader()->getCellContents()->getTextField()->getText();
            rowGroups.append(value);
            oldValues.append(value);
            for(int i = 0; i < report->getFieldsDataCount(); i++)
            {
                replaceRowGroupInCrosstab(crosstab, report, i);
                value = crosstab->getRowGroup()->getHeader()->getCellContents()->getTextField()->getText();
                if(!oldValues.contains(value))
                {
                    oldValues.append(value);
                    rowGroups.append(value);
                }
            }
            return true;
        }

        bool Replacer::replaceColumnGroupsInCrosstab(const CrosstabPtr & crosstab, const ReportPtr & report, QList<QString> & columnGroups)
        {
            replaceColumnGroupInCrosstab(crosstab, report, 0);
            QList<QString> oldValues;
            QString value = crosstab->getColumnGroup()->getHeader()->getCellContents()->getTextField()->getText();
            columnGroups.append(value);
            oldValues.append(value);
            for(int i = 0; i < report->getFieldsDataCount(); i++)
            {
                replaceColumnGroupInCrosstab(crosstab, report, i);
                value = crosstab->getColumnGroup()->getHeader()->getCellContents()->getTextField()->getText();
                if(!oldValues.contains(value))
                {
                    oldValues.append(value);
                    columnGroups.append(value);
                }
            }
            return true;
        }

        bool Replacer::replaceCellsInCrosstab(const CrosstabPtr & crosstab, const ReportPtr & report, QList<QString> & cells)
        {
            QList<QString> uniqueRowValues;
            replaceRowGroupsInCrosstab(crosstab, report, uniqueRowValues);

            QList<QString> uniqueColValues;
            replaceColumnGroupsInCrosstab(crosstab, report, uniqueColValues);

            auto mapField = report->getFields();

            auto colGroup = crosstab->getColumnGroup();
            QString colName = colGroup->getHeader()->getCellContents()->getTextField()->getOriginalText();
            colName = colName.replace("$", "").replace("F", "").replace("{", "").replace("}", "");

            QString cellName = crosstab->getCrosstabCell()->getCellContents()->getTextField()->getOriginalText();
            cellName = cellName.replace("$", "").replace("F", "").replace("{", "").replace("}", "");

            int mapCount = 0;
            for (int i = 0; i < uniqueRowValues.size(); i++)
            {
                auto row = uniqueRowValues[i];
                for(int j = 0; j < uniqueColValues.size(); j++)
                {
                    auto columnValue = mapField.value(colName)->getData(mapCount);

                    if(columnValue != uniqueColValues[j])
                        cells.append("");
                    else
                    {
                        replaceCellInCrosstab(crosstab, report, mapCount);
                        auto text = mapField.value(cellName)->getData(mapCount);
                        cells.append(text);
                        mapCount++;
                    }
                }
            }

            return true;
        }

        bool Replacer::replaceRowGroupInCrosstab(const CrosstabPtr & crosstab, const ReportPtr & report, int i)
        {
            auto rowGroupText = crosstab->getRowGroup()->getHeader()->getCellContents()->getTextField()->getOriginalText();
            auto rowGroupReplacedText = replaceField(rowGroupText, report, i);
            crosstab->getRowGroup()->getHeader()->getCellContents()->getTextField()->setText(rowGroupReplacedText);

            return true;
        }

        bool Replacer::replaceColumnGroupInCrosstab(const CrosstabPtr & crosstab, const ReportPtr & report, int i)
        {
            auto colGroupText = crosstab->getColumnGroup()->getHeader()->getCellContents()->getTextField()->getOriginalText();
            auto colGroupReplacedText = replaceField(colGroupText, report, i);
            crosstab->getColumnGroup()->getHeader()->getCellContents()->getTextField()->setText(colGroupReplacedText);

            return true;
        }

        bool Replacer::replaceCellInCrosstab(const CrosstabPtr & crosstab, const ReportPtr & report, int i)
        {
            auto cellText = crosstab->getCrosstabCell()->getCellContents()->getTextField()->getOriginalText();
            auto cellReplacedText = replaceField(cellText, report, i);
            crosstab->getCrosstabCell()->getCellContents()->getTextField()->setText(cellReplacedText);

            return true;
        }

        bool    Replacer::replaceFieldInTextWidget(const TextWidgetPtr & widget, const ReportPtr & report, int i)
        {
            auto text = widget->getOriginalText();
            auto replacedText = replaceField(text, report, i);
            widget->setText(replacedText);

            return true;
        }

        bool    Replacer::replaceFieldInImageWidget(const ImagePtr & widget, const ReportPtr & report, int i)
        {
            auto text = widget->getOriginalText();
            auto image = replaceFieldImage(text, report, i);
            auto size = widget->getSize();
            widget->setImage(image.scaled(size));

            return true;
        }

        bool    Replacer::replaceFieldInSection(const SectionPtr & section, const ReportPtr & report, int i)
        {
            if(section.isNull())
            {
                m_lastError = "Section is empty.";
                return false;
            }

            for(auto && band : section->getBands())
            {   
                for(auto && textWidget : band->getTextWidgets())
                {
                    if(!replaceFieldInTextWidget(textWidget, report, i))
                    {
                        return false;
                    }
                }

                for(auto && imageWidget : band->getImages())
                {
                    if(!replaceFieldInImageWidget(imageWidget, report, i))
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool    Replacer::replace(const SectionPtr & section, const ReportPtr & report, int i)
        {
            if(!replaceFieldInSection(section, report, i))
            {
                return false;
            }
            if(!replaceParameters(report))
            {
                return false;
            }

            return true;
        }

        const QString   Replacer::getLastError() const
        {
            return m_lastError;
        }

    }
}
