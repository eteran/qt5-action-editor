/****************************************************************************
** $Id: $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include "ActionsDialog.h"
#include <QAction>
#include <QTableWidget>

ActionsDialog::ActionsDialog(const QList<QAction *> &actions, QWidget *parent, Qt::WindowFlags f) : QDialog(parent, f) {
	ui.setupUi(this);

	// NOTE: added so the cellChanged event doesn't trigger during initial population
	ui.tableWidget->blockSignals(true);

	int row = 0;
	Q_FOREACH (QAction *action, actions) {
		if (!action->text().isEmpty()) {

			ui.tableWidget->insertRow(row);

			auto newItem0 = new QTableWidgetItem(action->text());
			newItem0->setFlags(newItem0->flags() & ~Qt::ItemIsEditable);

			auto newItem1 = new QTableWidgetItem(action->shortcut().toString());

			ui.tableWidget->setItem(row, 0, newItem0);
			ui.tableWidget->setItem(row, 1, newItem1);

			actionsList.append(action);
			++row;
		}
	}

	ui.tableWidget->blockSignals(false);
}

ActionsDialog::~ActionsDialog() {
}

void ActionsDialog::accept() {

	int row = 0;
	Q_FOREACH (QAction *action, actionsList) {
		action->setShortcut(QKeySequence(ui.tableWidget->item(row, 1)->text()));
		++row;
	}

	QDialog::accept();
}

void ActionsDialog::on_tableWidget_currentCellChanged(int row, int column, int prevousRow, int previousCol) {
	if (column == 1) {
		oldAccelText = ui.tableWidget->item(row, column)->text();
	}
}

void ActionsDialog::on_tableWidget_cellChanged(int row, int column) {

	// NOTE: since QKeySequence never seems to return an empty string,
	//       this validation technique is a bit useless :-/
	//       keeping it here for consistency with the original code
	if (column == 1) {
		QTableWidgetItem *item = ui.tableWidget->item(row, column);

		QKeySequence keySequence(item->text());

		QString accelText = keySequence.toString();

		if (accelText.isEmpty() && !item->text().isEmpty()) {
			item->setText(oldAccelText);
		} else {
			item->setText(accelText);
		}
	}
}
