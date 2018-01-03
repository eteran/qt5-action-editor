/****************************************************************************
** $Id: $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#include <QMainWindow>
#include "ui_ApplicationWindow.h"

class QPrinter;

class ApplicationWindow : public QMainWindow {
	Q_OBJECT

public:
	ApplicationWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
	~ApplicationWindow();

protected:
	virtual void closeEvent(QCloseEvent *);

private Q_SLOTS:
	void on_action_New_triggered();
	void on_action_Open_triggered();
	void on_action_Save_triggered();
	void on_action_Save_As_triggered();
	void on_action_Print_triggered();
	void on_action_Quit_triggered();
	void on_action_Edit_Actions_triggered();
	void on_action_Save_Actions_triggered();
	void on_action_About_triggered();
	void on_action_About_Qt_triggered();
	void on_action_Whats_This_triggered();

private:
	void load(const QString &fileName);
	void loadActions();

private:
	QPrinter *printer;
	QString filename;
	Ui::ApplicationWindow ui;
};

#endif
