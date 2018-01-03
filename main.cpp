/****************************************************************************
** $Id: $
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of an example program for Qt.  This example
** program may be used, distributed and modified without limitation.
**
*****************************************************************************/

#include <QApplication>
#include "ApplicationWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	QApplication::setOrganizationName("trolltech.com");
	QApplication::setOrganizationDomain("trolltech.com");
	QApplication::setApplicationName("action");

	auto mw = new ApplicationWindow();
	mw->setWindowTitle("Document 1");
	mw->show();
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
	return app.exec();
}
