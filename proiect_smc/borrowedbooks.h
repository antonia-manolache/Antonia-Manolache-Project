#pragma once

#include <QDialog>
#include<QtSql>
#include<QSqlDatabase>
#include<QMessageBox>
#include "ui_borrowedbooks.h"

class BorrowedBooks : public QDialog
{
	Q_OBJECT

public:
	BorrowedBooks(const QString& username, const QString& password, QWidget* parent = Q_NULLPTR);
	QString username;
	QString password;
	~BorrowedBooks();

private slots:

	void on_backBtn_clicked();
	void on_returnBtn_clicked();
	void on_extendBtn_clicked();
	void on_readBtn_clicked();


private:
	Ui::BorrowedBooks ui;
	QSqlDatabase books_database;
	QSqlQueryModel* table;
};
