#pragma once

#include <QDialog>
#include "ui_reader.h"
#include"borrowedbooks.h"

class Reader : public QDialog
{
	Q_OBJECT

public:
	Reader(const QString& username, const QString& password, QWidget* parent = Q_NULLPTR);
	QString username;
	QString password;
	~Reader();

private slots:
	void on_returnBtn_clicked();

private:
	Ui::Reader ui;
};