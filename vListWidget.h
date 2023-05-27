#ifndef VLISTWIDGET_H
#define VLISTWIDGET_H

#include <QWidget>

namespace Ui {
class vListWidget;
}

class vListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit vListWidget(QWidget *parent = nullptr);
    ~vListWidget();

    bool filtering() const;
    void setFiltering(bool newFiltering);

    bool manipulation() const;
    void setManipulation(bool newManipulation);

    const QStringList &values() const;
    void setValues(const QStringList &newValues);

    void setValues(const QVariantList &newValues);

signals:
    void filteringChanged();

    void manipulationChanged();

    void valuesChanged();

private slots:
    void on_actionClear_All_triggered();

    void on_btnAdd_clicked();

    void btnDeleteClicked();

    void on_lnFilter_textChanged(const QString &arg1);




    void on_actionContains_triggered();

    void on_actionNot_Contains_triggered();

    void on_actionStarts_With_triggered();

    void on_actionEnds_With_triggered();

    void on_actionEqual_triggered();

private:
    Ui::vListWidget *ui;
    bool _filtering;
    bool _manipulation;
    QStringList _values;
    Q_PROPERTY(bool filtering READ filtering WRITE setFiltering NOTIFY filteringChanged)
    Q_PROPERTY(bool manipulation READ manipulation WRITE setManipulation NOTIFY manipulationChanged)
    Q_PROPERTY(QStringList values READ values WRITE setValues NOTIFY valuesChanged)

    QAction *_prevAction;

    std::function<bool(QString, QString)> containsFunc = [](QString value, QString filter){
        return value.contains(filter);
    };
    std::function<bool(QString, QString)> notContainsFunc = [](QString value, QString filter){
        return !value.contains(filter);
    };
    std::function<bool(QString, QString)> startsWithFunc = [](QString value, QString filter){
        return value.startsWith(filter);
    };
    std::function<bool(QString, QString)> endsWithFunc = [](QString value, QString filter){
        return value.endsWith(filter);
    };
    std::function<bool(QString, QString)> equalFunc = [](QString value, QString filter){
        return value== filter;
    };
    std::function<bool(QString, QString)> comparatorFunc;

    void updateFilteringOption(std::function<bool(QString, QString)> func);

    void updateListValues(const QString &arg1);
};

#endif // VLISTWIDGET_H
