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
#include "ApplicationWindow.h"
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QSettings>
#include <QTextStream>
#include <QWhatsThis>

ApplicationWindow::ApplicationWindow(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {

	ui.setupUi(this);

	printer = new QPrinter(QPrinter::HighResolution);

	auto fileOpenText = tr("<p>"
	                       "Click this button to open a <em>new file</em>.<br>"
	                       "You can also select the <b>Open</b> command from the <b>File</b> menu."
	                       "</p>");

	auto fileSaveText = tr("<p>"
	                       "Click this button to save the file you are editing. You will be prompted for a file name.<br>"
	                       "You can also select the <b>Save</b> command from the <b>File</b> menu."
	                       "</p>");

	auto filePrintText = tr("<p>"
	                        "Click this button to print the file you are editing.<br>"
	                        "You can also select the <b>Print</b> command from the <b>File</b> menu."
	                        "</p>");

	ui.action_Open->setWhatsThis(fileOpenText);
	ui.action_Save->setWhatsThis(fileSaveText);
	ui.action_Print->setWhatsThis(filePrintText);

	statusBar()->showMessage(tr("Ready"), 2000);
	loadActions();
}

ApplicationWindow::~ApplicationWindow() {
	delete printer;
}

void ApplicationWindow::on_action_New_triggered() {
	auto ed = new ApplicationWindow;
	ed->show();
}

void ApplicationWindow::on_action_Open_triggered() {
	QString fn = QFileDialog::getOpenFileName(this, QString(), QString(), QString());

	if (!fn.isEmpty()) {
		load(fn);
	} else {
		statusBar()->showMessage(tr("Loading aborted"), 2000);
	}
}

void ApplicationWindow::on_action_Save_triggered() {
	if (filename.isEmpty()) {
		on_action_Save_As_triggered();
		return;
	}

	QString text = ui.textEdit->document()->toPlainText();
	QFile f(filename);
	if (!f.open(QIODevice::WriteOnly)) {
		statusBar()->showMessage(tr("Could not write to %1").arg(filename), 2000);
		return;
	}

	QTextStream t(&f);
	t << text;
	f.close();

	ui.textEdit->document()->setModified(false);

	setWindowTitle(filename);

	statusBar()->showMessage(tr("File %1 saved").arg(filename), 2000);
}

void ApplicationWindow::on_action_Save_As_triggered() {
	QString fn = QFileDialog::getSaveFileName(this, QString(), QString(), QString());

	if (!fn.isEmpty()) {
		filename = fn;
		on_action_Save_triggered();
	} else {
		statusBar()->showMessage(tr("Saving aborted"), 2000);
	}
}

void ApplicationWindow::on_action_Print_triggered() {
	printer->setFullPage(true);

	QPrintDialog printDialog(printer, this);
	if (printDialog.exec() == QDialog::Accepted) {
		statusBar()->showMessage(tr("Printing..."));

		QTextDocument *doc = ui.textEdit->document();
		doc->print(printer);

		statusBar()->showMessage(tr("Printing completed"), 2000);
	} else {
		statusBar()->showMessage(tr("Printing aborted"), 2000);
	}
}

void ApplicationWindow::on_action_Quit_triggered() {
	qApp->closeAllWindows();
}

void ApplicationWindow::on_action_Edit_Actions_triggered() {
	QList<QAction *> actions = findChildren<QAction *>();
	ActionsDialog actionsDialog(actions, this);
	actionsDialog.exec();
}

void ApplicationWindow::on_action_Save_Actions_triggered() {
	QSettings settings;
	settings.beginGroup("/Action");

	QList<QAction *> actions = findChildren<QAction *>();
	Q_FOREACH (QAction *action, actions) {
		if (!action->text().isEmpty()) {
			QString accelText = action->shortcut().toString();
			settings.setValue(action->text(), accelText);
		}
	}
}

void ApplicationWindow::on_action_About_triggered() {
	QMessageBox::about(this, tr("Qt Application Example"), tr("This example demonstrates simple use of QMainWindow, QMenuBar, and QToolBar."));
}

void ApplicationWindow::on_action_About_Qt_triggered() {
	QMessageBox::aboutQt(this, tr("Qt Application Example"));
}

void ApplicationWindow::on_action_Whats_This_triggered() {
	QWhatsThis::enterWhatsThisMode();
}

void ApplicationWindow::loadActions() {
	QSettings settings;
	settings.beginGroup("/Action");

	QList<QAction *> actions = findChildren<QAction *>();
	Q_FOREACH (QAction *action, actions) {
		QString accelText = settings.value(action->text()).toString();
		if (!accelText.isNull())
			action->setShortcut(QKeySequence(accelText));
	}
}

void ApplicationWindow::load(const QString &fileName) {
	QFile f(fileName);
	if (!f.open(QIODevice::ReadOnly))
		return;

	ui.textEdit->setText(f.readAll());
	ui.textEdit->document()->setModified(false);
	setWindowTitle(fileName);
	statusBar()->showMessage(tr("Loaded document %1").arg(fileName), 2000);
}

void ApplicationWindow::closeEvent(QCloseEvent *ce) {
	if (!ui.textEdit->document()->isModified()) {
		ce->accept();
		return;
	}

	switch (QMessageBox::information(this, tr("Qt Application Example"), tr("The document has been changed since the last save."), tr("Save Now"), tr("Cancel"), tr("Leave Anyway"), 0, 1)) {
	case 0:
		on_action_Save_triggered();
		ce->accept();
		break;
	case 1:
	default: // just for sanity
		ce->ignore();
		break;
	case 2:
		ce->accept();
		break;
	}
}
