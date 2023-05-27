#include "vListWidget.h"
#include "vListWidgetPlugin.h"

#include <QtPlugin>

vListWidgetPlugin::vListWidgetPlugin(QObject *parent)
    : QObject(parent)
{
    m_initialized = false;
}

void vListWidgetPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (m_initialized)
        return;

    // Add extension registrations, etc. here

    m_initialized = true;
}

bool vListWidgetPlugin::isInitialized() const
{
    return m_initialized;
}

QWidget *vListWidgetPlugin::createWidget(QWidget *parent)
{
    return new vListWidget(parent);
}

QString vListWidgetPlugin::name() const
{
    return QLatin1String("vListWidget");
}

QString vListWidgetPlugin::group() const
{
    return QLatin1String("vrfEducation Widgets");
}

QIcon vListWidgetPlugin::icon() const
{
    return QIcon();
}

QString vListWidgetPlugin::toolTip() const
{
    return QLatin1String("");
}

QString vListWidgetPlugin::whatsThis() const
{
    return QLatin1String("");
}

bool vListWidgetPlugin::isContainer() const
{
    return false;
}

QString vListWidgetPlugin::domXml() const
{
    return QLatin1String("<widget class=\"vListWidget\" name=\"v_ListWidget\">\n</widget>\n");
}

QString vListWidgetPlugin::includeFile() const
{
    return QLatin1String("vListWidget.h");
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(vListWidgetPlugin, vListWidgetPlugin)
#endif // QT_VERSION < 0x050000
