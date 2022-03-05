#pragma once

#include <QDialog>
#include<QtSql>
#include<QSqlDatabase>
#include<QMessageBox>
#include "ui_borrow.h"

class Borrow : public QDialog
{
    Q_OBJECT

public:
    Borrow(const QString& username, const QString& password, QWidget* parent = Q_NULLPTR);
    QString username;
    QString password;
    ~Borrow();

private slots:
	void on_backBtn_clicked();
	void on_SearchTitleBtn_clicked();
	void on_SearchAuthorBtn_clicked();
	void on_SearchIsbnBtn_clicked();
	void on_RefreshBtn_clicked();
	void on_borrowBtn_clicked();
	

private:
	Ui::Borrow ui;
	QSqlDatabase books_database;
	QSqlQueryModel* table;
};
