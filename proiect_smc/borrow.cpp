#include "borrow.h"
#include"account.h"
Borrow::Borrow(const QString& username, const QString& password, QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    this->username = username;
    this->password = password;
    ui.search->setPlaceholderText("search...");


	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* display_query = new QSqlQuery(books_database);
		QSqlQuery* verify_returningdate_query = new QSqlQuery(books_database);
		QSqlQuery* modify_late_query = new QSqlQuery(books_database);
		QSqlQuery* get_id_query = new QSqlQuery(books_database);

		QString title = ui.tableView->currentIndex().data().toString();

		display_query->prepare("select * from books;");
		display_query->exec();
		table->setQuery(*display_query);

		get_id_query->prepare("SELECT id FROM books WHERE title = :title;");
		get_id_query->bindValue(":title", title);
		get_id_query->exec();
		int id;
		while (get_id_query->next())
		{
			id = get_id_query->value(0).toInt();
		}

		verify_returningdate_query->prepare("select returning_date from borrow where username=:username;");
		verify_returningdate_query->bindValue(":username", username);
		verify_returningdate_query->exec();
		QDate date;
		date = date.currentDate();
		while (verify_returningdate_query->next())
		{
			if (date > verify_returningdate_query->value(0).toDate())
			{
				QString late = "YES";
				modify_late_query->prepare("UPDATE users SET late = :late where username = :username;");
				modify_late_query->bindValue(":late", late);
				modify_late_query->bindValue(":id", id);
				modify_late_query->bindValue(":username", username);
				modify_late_query->exec();
			}
		}


		table->setHeaderData(0, Qt::Horizontal, tr("ID"));
		table->setHeaderData(1, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(2, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(3, Qt::Horizontal, tr("ISBN"));
		table->setHeaderData(4, Qt::Horizontal, tr("AVAILABLE QUANTITY"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();
	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

void Borrow::on_backBtn_clicked()
{
	this->close();
	Account dialog(username,password);
	dialog.setModal(true);
	dialog.exec();
}

Borrow::~Borrow()
{
}

void Borrow::on_SearchTitleBtn_clicked()
{
	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* display_query = new QSqlQuery(books_database);
		QString title = ui.search->text();
		title.push_back("%");
		title.push_front("%");
		display_query->prepare("select * from books where title like :title;");
		display_query->bindValue(":title", title);
		display_query->exec();
		table->setQuery(*display_query);


		table->setHeaderData(0, Qt::Horizontal, tr("ID"));
		table->setHeaderData(1, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(2, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(3, Qt::Horizontal, tr("ISBN"));
		table->setHeaderData(4, Qt::Horizontal, tr("AVAILABLE QUANTITY"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();


	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

void Borrow::on_SearchAuthorBtn_clicked()
{
	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* display_query = new QSqlQuery(books_database);
		QString authors = ui.search->text();
		authors.push_back("%");
		authors.push_front("%");
		display_query->prepare("select * from books where authors like :authors;");
		display_query->bindValue(":authors", authors);
		display_query->exec();
		table->setQuery(*display_query);


		table->setHeaderData(0, Qt::Horizontal, tr("ID"));
		table->setHeaderData(1, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(2, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(3, Qt::Horizontal, tr("ISBN"));
		table->setHeaderData(4, Qt::Horizontal, tr("AVAILABLE QUANTITY"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();

	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

void Borrow::on_SearchIsbnBtn_clicked()
{
	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* display_query = new QSqlQuery(books_database);
		QString isbn = ui.search->text();
		isbn.push_back("%");
		isbn.push_front("%");
		display_query->prepare("select * from books where isbn like :isbn;");
		display_query->bindValue(":isbn", isbn);
		display_query->exec();
		table->setQuery(*display_query);


		table->setHeaderData(0, Qt::Horizontal, tr("ID"));
		table->setHeaderData(1, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(2, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(3, Qt::Horizontal, tr("ISBN"));
		table->setHeaderData(4, Qt::Horizontal, tr("AVAILABLE QUANTITY"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();

	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

void Borrow::on_RefreshBtn_clicked()
{
	ui.search->setPlaceholderText("search...");


	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* display_query = new QSqlQuery(books_database);
		QSqlQuery* verify_returningdate_query = new QSqlQuery(books_database);
		QSqlQuery* modify_late_query = new QSqlQuery(books_database);
		QSqlQuery* get_id_query = new QSqlQuery(books_database);

		QString title = ui.tableView->currentIndex().data().toString();

		display_query->prepare("select * from books;");
		display_query->exec();
		table->setQuery(*display_query);

		get_id_query->prepare("SELECT id FROM books WHERE title = :title;");
		get_id_query->bindValue(":title", title);
		get_id_query->exec();
		int id;
		while (get_id_query->next())
		{
			id = get_id_query->value(0).toInt();
		}

		verify_returningdate_query->prepare("select returning_date from borrow where username=:username;");
		verify_returningdate_query->bindValue(":username", username);
		verify_returningdate_query->exec();
		QDate date;
		date = date.currentDate();
		while (verify_returningdate_query->next())
		{
			if (date > verify_returningdate_query->value(0).toDate())
			{
				QString late = "YES";
				modify_late_query->prepare("UPDATE users SET late = :late where username = :username;");
				modify_late_query->bindValue(":late", late);
				modify_late_query->bindValue(":id", id);
				modify_late_query->bindValue(":username", username);
				modify_late_query->exec();
			}
		}


		table->setHeaderData(0, Qt::Horizontal, tr("ID"));
		table->setHeaderData(1, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(2, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(3, Qt::Horizontal, tr("ISBN"));
		table->setHeaderData(4, Qt::Horizontal, tr("AVAILABLE QUANTITY"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();
	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

void Borrow::on_borrowBtn_clicked()
{
	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* modify_quantity_query = new QSqlQuery(books_database);
		QSqlQuery* modify_borrowedbooks_quantity_query = new QSqlQuery(books_database);
		QSqlQuery* modify_late_query = new QSqlQuery(books_database);

		QSqlQuery* borrow_query = new QSqlQuery(books_database);

		QSqlQuery* verify_borrowings_query = new QSqlQuery(books_database);
		QSqlQuery* verify_iflate_query = new QSqlQuery(books_database);
		QSqlQuery* verify_returningdate_query = new QSqlQuery(books_database);

		QSqlQuery* get_id_query = new QSqlQuery(books_database);
		QSqlQuery* get_quantity_query = new QSqlQuery(books_database);
		QSqlQuery* get_borrowedbooks_query = new QSqlQuery(books_database);
		QSqlQuery* get_iflate_query = new QSqlQuery(books_database);
		QSqlQuery* get_borrowingdate_query = new QSqlQuery(books_database);
		QSqlQuery* get_returningdate_query = new QSqlQuery(books_database);

		QSqlQuery* display_query = new QSqlQuery(books_database);


		QString title = ui.tableView->currentIndex().data().toString();



		get_id_query->prepare("SELECT id FROM books WHERE title = :title;");
		get_id_query->bindValue(":title", title);
		get_id_query->exec();
		int id;
		while (get_id_query->next())
		{
			id = get_id_query->value(0).toInt();
		}

		get_quantity_query->prepare("SELECT available_quantity FROM books WHERE id = :id;");
		get_quantity_query->bindValue(":id", id);
		get_quantity_query->exec();
		int quantity;
		while (get_quantity_query->next())
		{
			quantity = get_quantity_query->value(0).toInt();
		}

		get_borrowedbooks_query->prepare("SELECT borrowed_books FROM users WHERE username = :username;");
		get_borrowedbooks_query->bindValue(":username", username);
		get_borrowedbooks_query->exec();
		int borrowed_books;
		while (get_borrowedbooks_query->next())
		{
			borrowed_books = get_borrowedbooks_query->value(0).toInt();
		}

		get_iflate_query->prepare("SELECT late FROM users WHERE username = :username;");
		get_iflate_query->bindValue(":username", username);
		get_iflate_query->exec();
		bool late;
		while (get_iflate_query->next())
		{
			if (get_iflate_query->value(0).toString() == "YES")
			{
				late = true;
			}
			else
			{
				late = false;
			}
		}

		get_borrowingdate_query->prepare("select date('now');");
		get_borrowingdate_query->exec();
		QString borrowing_date;
		while (get_borrowingdate_query->next())
		{
			borrowing_date = get_borrowingdate_query->value(0).toString();
		}

		get_returningdate_query->prepare("select date('now', '+14 days');");
		get_returningdate_query->exec();
		QString returning_date;
		while (get_returningdate_query->next())
		{
			returning_date = get_returningdate_query->value(0).toString();
		}

		verify_borrowings_query->prepare("select borrow_id from borrowed_books where book_id= :id and username=:username;");
		verify_borrowings_query->bindValue(":id", id);
		verify_borrowings_query->bindValue(":username", username);
		verify_borrowings_query->exec();
		bool ok = false;
		while (verify_borrowings_query->next())
		{
			ok = true;
		}

		verify_returningdate_query->prepare("select returning_date from borrowed_books where username=:username;");
		verify_returningdate_query->bindValue(":username", username);
		verify_returningdate_query->exec();
		QDate date;
		date.currentDate();
		while (verify_returningdate_query->next())
		{
			if (date > verify_returningdate_query->value(0).toDate())
			{
				QString late = "YES";
				modify_late_query->prepare("UPDATE users SET late = :late where username = :username;");
				modify_quantity_query->bindValue(":late", late);
				modify_quantity_query->bindValue(":id", id);
				modify_quantity_query->bindValue(":username", username);
				modify_quantity_query->exec();
			}
		}



		if (quantity)
		{
			if (borrowed_books < 5)
			{
				if (ok == false)
				{
					if (late == false)
					{
						borrowed_books++;
						modify_quantity_query->prepare("UPDATE books SET available_quantity = :quantity WHERE id = :id;");
						modify_quantity_query->bindValue(":quantity", quantity - 1);
						modify_quantity_query->bindValue(":id", id);
						modify_quantity_query->exec();
						modify_borrowedbooks_quantity_query->prepare("UPDATE users SET borrowed_books = :quantity WHERE username = :username;");
						modify_borrowedbooks_quantity_query->bindValue(":quantity", borrowed_books);
						modify_borrowedbooks_quantity_query->bindValue(":username", username);
						modify_borrowedbooks_quantity_query->exec();
						borrow_query->prepare("INSERT INTO borrowed_books (username, book_id, borrowing_date, returning_date)"
							"VALUES (:username, :book_id, :borrowing_date, :returning_date)");
						borrow_query->bindValue(":username", username);
						borrow_query->bindValue(":book_id", id);
						borrow_query->bindValue(":borrowing_date", borrowing_date);
						borrow_query->bindValue(":returning_date", returning_date);
						borrow_query->exec();


					}
					else
					{
						QMessageBox::warning(this, "Borrow", "You are late!");
					}
				}
				else
				{
					QMessageBox::warning(this, "Borrow", "You already have this book!");
				}
			}
			else
			{
				QMessageBox::warning(this, "Borrow", "You already have 5 booked books!");
			}
		}
		else
		{
			QMessageBox::warning(this, "Borrow", "There are not enough books!");
		}


		display_query->prepare("select * from books;");
		display_query->exec();
		table->setQuery(*display_query);

		table->setHeaderData(0, Qt::Horizontal, tr("BOOK AUTHOR"));
		table->setHeaderData(1, Qt::Horizontal, tr("BOOK TITLE"));




		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();
	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

