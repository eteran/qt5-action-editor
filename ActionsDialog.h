/****************************************************************************
** $Id: $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef ACTIONS_DIALOG_H
#define ACTIONS_DIALOG_H

#include <QDialog>
#include <QList>
#include <QString>
#include "ui_ActionsDialog.h"

class QAction;

class ActionsDialog : public QDialog {
	Q_OBJECT

public:
	ActionsDialog(const QList<QAction *> &actions, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	virtual ~ActionsDialog();
protected Q_SLOTS:
	void accept();

private Q_SLOTS:
	void on_tableWidget_currentCellChanged(int row, int column, int prevousRow, int previousCol);
	void on_tableWidget_cellChanged(int row, int column);

private:
	QString oldAccelText;
	QList<QAction *> actionsList;
	Ui::ActionsDialog ui;
};

#endif
