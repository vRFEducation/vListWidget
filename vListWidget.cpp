#include "vListWidget.h"
#include "ui_vListWidget.h"

vListWidget::vListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vListWidget),
    _filtering(true),
    _manipulation(true)
{
    ui->setupUi(this);
    ui->btnDelete->addAction(ui->actionClear_All);

    QList<QAction *> filterinOptionActions;
    filterinOptionActions << ui->actionContains << ui->actionNot_Contains
                          << ui->actionStarts_With << ui->actionEnds_With
                          << ui->actionEqual;
    ui->btnFilterOptions->addActions(filterinOptionActions);
    _prevAction = ui->actionContains;
    comparatorFunc = containsFunc;
    connect(ui->btnDelete, &QToolButton::clicked, this, &vListWidget::btnDeleteClicked);
}

vListWidget::~vListWidget()
{
    delete ui;
}

void vListWidget::on_actionClear_All_triggered()
{
    _values.clear();
    ui->lstItems->clear();
}

bool vListWidget::manipulation() const
{
    return _manipulation;
}

void vListWidget::setManipulation(bool newManipulation)
{
    if (_manipulation == newManipulation)
        return;
    _manipulation = newManipulation;
    ui->wdgManipulation->setVisible(_manipulation);
    emit manipulationChanged();
}

bool vListWidget::filtering() const
{
    return _filtering;
}

void vListWidget::setFiltering(bool newFiltering)
{
    if (_filtering == newFiltering)
        return;
    _filtering = newFiltering;
    ui->wdgFiltering->setVisible(_filtering);
    emit filteringChanged();
}


void vListWidget::on_btnAdd_clicked()
{
    auto text = ui->lnNewItem->text().trimmed();
    if (text.length() > 0) {
        ui->lstItems->addItem(text);
        _values.append(text);
        ui->lnNewItem->clear();
        ui->lnNewItem->setFocus();
    }
}


void vListWidget::btnDeleteClicked()
{
    auto ind = ui->lstItems->currentRow();
    if (ind != -1) {
        _values.removeAt(ind);
        ui->lstItems->takeItem(ind);
    }
}

const QStringList &vListWidget::values() const
{
    return _values;
}

void vListWidget::setValues(const QStringList &newValues)
{
    if (_values == newValues)
        return;
    _values = newValues;
    ui->lstItems->clear();
    ui->lstItems->addItems(_values);
    emit valuesChanged();
}

void vListWidget::setValues(const QVariantList &newValues)
{
    QStringList values;
    foreach (auto item, newValues) {
        values.append(item.toString());
    }
    setValues(values);
}


void vListWidget::updateListValues(const QString &arg1)
{
    QStringList res;
    if (arg1 == "") {
        res = _values;
    } else {
        foreach (auto item, _values) {
            if(comparatorFunc(item, arg1))
                res.append(item);
        }
    }
    ui->lstItems->clear();
    ui->lstItems->addItems(res);
}

void vListWidget::on_lnFilter_textChanged(const QString &arg1)
{
    updateListValues(arg1);
}


void vListWidget::on_actionContains_triggered()
{
    updateFilteringOption(containsFunc);
}


void vListWidget::on_actionNot_Contains_triggered()
{
    updateFilteringOption(notContainsFunc);
}


void vListWidget::on_actionStarts_With_triggered()
{
    updateFilteringOption(startsWithFunc);
}


void vListWidget::on_actionEnds_With_triggered()
{
    updateFilteringOption(endsWithFunc);
}


void vListWidget::on_actionEqual_triggered()
{
    updateFilteringOption(equalFunc);
}

void vListWidget::updateFilteringOption(std::function<bool (QString, QString)> func)
{
    comparatorFunc = func;
    _prevAction->setChecked(false);
    _prevAction = qobject_cast<QAction *>(sender());
    updateListValues(ui->lnFilter->text());

}

