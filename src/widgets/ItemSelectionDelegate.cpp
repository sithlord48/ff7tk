#include "ItemSelectionDelegate.h"
#include <QAbstractItemView>
#include <ItemSelector.h>
#include <FF7Item.h>
#include <QLabel>

ItemSelectionDelegate::ItemSelectionDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

QWidget* ItemSelectionDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index);
    const auto &selector = new ItemSelector(parent);
    selector->setEditableItemCombo(m_editableItemCombo);
    selector->setMaximumQty(m_maxQty);
    connect(selector, &ItemSelector::itemChanged, this, [this, selector]{
        Q_EMIT commitData(static_cast<QWidget*>(selector));
    });
    return selector;
}

void ItemSelectionDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto *selector = static_cast<ItemSelector*>(editor);
    selector->setCurrentItem(FF7Item::itemDecode(index.model()->data(index, Qt::EditRole).toUInt()));
}

void ItemSelectionDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto *selector = static_cast<ItemSelector*>(editor);
    model->setData(index, selector->currentItem(), Qt::EditRole);
}

void ItemSelectionDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!index.isValid())
        return;

    editor->setFixedSize(editor->sizeHint());
    editor->move(0, option.rect.y());
}

void ItemSelectionDelegate::setMaximumQty(int maxQty)
{
    m_maxQty = maxQty;
}

void ItemSelectionDelegate::setEditableItemCombo(bool editable)
{
    m_editableItemCombo = editable;
}

QSize ItemSelectionDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option);
    if(!index.isValid())
        return QSize(0,0);
    ItemSelector selector;
    return selector.size();
}
