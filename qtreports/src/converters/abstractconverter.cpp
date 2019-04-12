#include "abstractconverter.h"
using namespace qtreports;
using namespace detail;

AbstractConverter::AbstractConverter(const ReportPtr& report) :
     m_report(report)
{

}

const QString AbstractConverter::getLastError() const
{
    return m_lastError;
}


bool qtreports::detail::AbstractConverter::addGroups(DetailPtr detail)
{
    detail::Replacer replacer;

    QList<GroupPtr> groups = m_report->getGroups().values();
    QList<QString> groupNames;
    //Сюда помещаем конкретные имена по которым группируем
    QList<QString> particularNames;
    for (int i = 0; i<groups.length(); i++)
    {
        auto groupExpression = groups[i]->getExpression();
        if(groupExpression == "")
        {
            return false;
        }
        groupNames.append(groupExpression);
        particularNames.append(replacer.replaceField(groupNames[i], m_report, 0));
    }
    //Открываем хедеры групп
    for (int i = 0; i<groups.length(); i++)
    {
        auto header = groups[i]->getHeader();
        if (!header.isNull())
        {
            if(!addBand(header, 0))
            {
                return false;
            }
        }
    }

    int rowCount = m_report->getRowCount();
    for(int i = 0; i < rowCount; i++)
    {
        //QWidget * sectionWidget = isLayout() ? sectionWidget = addSectionLayout(layout, report->getMargins(), detail->getHeight()) : nullptr;

        //Закрываем футеры, если группа закончилась
        for(int j = groups.length() - 1; j >= 0; j--)
        {
            //сверяем поле в заголовке и текущее поле
            if(particularNames[j] != replacer.replaceField(groupNames[j], m_report, i))
            {
                auto footer = m_report->getGroupByIndex(j)->getFooter();
                if (!footer.isNull())
                {
                    if(!addBand(footer, i - 1))
                    {
                        return false;
                    }
                }
            }
        }
        //Аналогично открываем хедеры
        for(int j = 0; j < groupNames.length(); j++)
        {
            //сверяем поле в заголовке и текущее поле
            if(particularNames[j] != replacer.replaceField(groupNames[j], m_report, i))
            {
                auto header = m_report->getGroupByIndex(j)->getHeader();
                if (!header.isNull())
                {
                    if(!addBand(header, i))
                    {
                        return false;
                    }
                }
            }
        }
        //Переписываем имена для сравнения
        for(int j = 0; j < groupNames.length(); j++)
        {
            particularNames[j] = replacer.replaceField(groupNames[j], m_report, i);
        }
        //Выводим поле
        if(!addBand(detail, i))
        {
            return false;
        }
    }
    //Закрываем хедеры групп
    for(int i = groups.length() - 1; i >= 0; i--)
    {
        auto footer = groups[i]->getFooter();
        if (!footer.isNull())
        {
            if(!addBand(footer, (rowCount - 1)))
            {
                return false;
            }
        }
    }
    return true;
}
