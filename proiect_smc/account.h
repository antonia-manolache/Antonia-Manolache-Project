#pragma once

#include <QDialog>
#include "ui_account.h"
#include"ui_mainwindow.h"
#include"mainwindow.h"
#include "borrow.h"
#include "borrowedbooks.h"
#include "mainwindow.h"
#include "manageaccount.h"
#include<QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
#include<QMessageBox>

class Account : public QDialog
{
	Q_OBJECT

public:
	Account(const QString& username, const QString& password, QWidget* parent = Q_NULLPTR);
	QString username;
	QString password;
	~Account();

private slots:
	void on_mybooksBtn_clicked();

	void on_borrowBtn_clicked();

	void on_SignOutBtn_clicked();

	void on_manageBtn_clicked();

private:

	Ui::Account ui;

};
