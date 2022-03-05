#include "borrowedbooks.h"
#include"account.h"
#include"reader.h"
BorrowedBooks::BorrowedBooks(const QString& username, const QString& password, QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    this->username = username;
    this->password = password;

	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();

		QSqlQuery* display_query = new QSqlQuery(books_database);

		display_query->prepare("select books.title, books.authors, borrowed_books.borrowing_date, borrowed_books.returning_date from books inner join borrowed_books on books.id = borrowed_books.book_id and borrowed_books.username = :username;");
		display_query->bindValue(":username", username);
		display_query->exec();
		table->setQuery(*display_query);

		table->setHeaderData(0, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(1, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(2, Qt::Horizontal, tr("BORROWING DATE"));
		table->setHeaderData(3, Qt::Horizontal, tr("RETURNING DATE"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();
	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

BorrowedBooks::~BorrowedBooks()
{
}


void BorrowedBooks::on_returnBtn_clicked()
{
	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* display_query = new QSqlQuery(books_database);

		QSqlQuery* return_query = new QSqlQuery(books_database);

		QSqlQuery* get_id_query = new QSqlQuery(books_database);
		QSqlQuery* get_quantity_query = new QSqlQuery(books_database);
		QSqlQuery* get_borrowedbooks_query = new QSqlQuery(books_database);

		QSqlQuery* modify_quantity_query = new QSqlQuery(books_database);
		QSqlQuery* modify_borrowedbooks_quantity_query = new QSqlQuery(books_database);
		QSqlQuery* modify_extendings_query = new QSqlQuery(books_database);

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


		modify_quantity_query->prepare("UPDATE books SET available_quantity = :quantity WHERE id = :id;");
		modify_quantity_query->bindValue(":quantity", quantity + 1);
		modify_quantity_query->bindValue(":id", id);
		modify_quantity_query->exec();
		modify_borrowedbooks_quantity_query->prepare("UPDATE users SET borrowed_books = :quantity WHERE username = :username;");
		modify_borrowedbooks_quantity_query->bindValue(":quantity", borrowed_books - 1);
		modify_borrowedbooks_quantity_query->bindValue(":username", username);
		modify_borrowedbooks_quantity_query->exec();


		return_query->prepare("delete from borrowed_books where book_id= :id;");
		return_query->bindValue(":id", id);
		return_query->exec();

		display_query->prepare("select books.title, books.authors, borrowed_books.borrowing_date, borrowed_books.returning_date from books inner join borrowed_books on books.id = borrowed_books.book_id and borrowed_books.username = :username;");
		display_query->bindValue(":username", username);
		display_query->exec();
		table->setQuery(*display_query);

		table->setHeaderData(0, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(1, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(2, Qt::Horizontal, tr("BORROWING DATE"));
		table->setHeaderData(3, Qt::Horizontal, tr("RETURNING DATE"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();
	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

void BorrowedBooks::on_extendBtn_clicked()
{
	books_database = QSqlDatabase::addDatabase("QSQLITE");
	books_database.setDatabaseName("Library.db");

	if (books_database.open())
	{
		table = new QSqlQueryModel();
		QSqlQuery* display_query = new QSqlQuery(books_database);

		QSqlQuery* extend_query = new QSqlQuery(books_database);

		QSqlQuery* get_id_query = new QSqlQuery(books_database);
		QSqlQuery* get_extendings_query = new QSqlQuery(books_database);

		QSqlQuery* get_returningdate_query = new QSqlQuery(books_database);

		QSqlQuery* modify_extendings_query = new QSqlQuery(books_database);
		QSqlQuery* modify_returningdate_query = new QSqlQuery(books_database);

		QString title = ui.tableView->currentIndex().data().toString();

		get_id_query->prepare("SELECT id FROM books WHERE title = :title;");
		get_id_query->bindValue(":title", title);
		get_id_query->exec();
		int id;
		while (get_id_query->next())
		{
			id = get_id_query->value(0).toInt();
		}

		get_extendings_query->prepare("select extendings from borrowed_books where book_id = :id and username = :username;");
		get_extendings_query->bindValue(":id", id);
		get_extendings_query->bindValue(":username", username);
		get_extendings_query->exec();
		int extendings;
		while (get_extendings_query->next())
		{
			extendings = get_extendings_query->value(0).toInt();
		}

		get_returningdate_query->prepare("select returning_date from borrowed_books where book_id= :id and username = :username; ");
		get_returningdate_query->bindValue(":id", id);
		get_returningdate_query->bindValue(":username", username);
		get_returningdate_query->exec();
		QDate returning_date;

		while (get_returningdate_query->next())
		{
			returning_date = get_returningdate_query->value(0).toDate();
		}


		if (extendings < 2)
		{
			extendings++;
			QString new_returning_date = returning_date.addDays(14).toString("yyyy-MM-dd");
			modify_returningdate_query->prepare("UPDATE borrowed_books SET returning_date = :new_returning_date WHERE book_id = :id and username=:username;");
			modify_returningdate_query->bindValue(":new_returning_date", new_returning_date);
			modify_returningdate_query->bindValue(":id", id);
			modify_returningdate_query->bindValue(":username", username);
			modify_returningdate_query->exec();

			modify_extendings_query->prepare("UPDATE borrowed_books SET extendings = :extendings WHERE book_id = :id and username = :username;");
			modify_extendings_query->bindValue(":extendings", extendings);
			modify_extendings_query->bindValue(":id", id);
			modify_extendings_query->bindValue(":username", username);
			modify_extendings_query->exec();

		}
		else
		{
			QMessageBox::warning(this, "Borrow", "You already extened the time for this book two times!");
		}

		display_query->prepare("select books.title, books.authors, borrowed_books.borrowing_date, borrowed_books.returning_date from books inner join borrowed_books on books.id = borrowed_books.book_id and borrowed_books.username = :username;");
		display_query->bindValue(":username", username);
		display_query->exec();
		table->setQuery(*display_query);

		table->setHeaderData(0, Qt::Horizontal, tr("TITLE"));
		table->setHeaderData(1, Qt::Horizontal, tr("AUTHOR"));
		table->setHeaderData(2, Qt::Horizontal, tr("BORROWING DATE"));
		table->setHeaderData(3, Qt::Horizontal, tr("RETURNING DATE"));


		ui.tableView->setModel(table);
		ui.tableView->resizeColumnsToContents();
	}
	else
	{
		QMessageBox::warning(this, "Connection", "Database is not connected");
	}
}

void BorrowedBooks::on_readBtn_clicked()
{
    this->close();
    Reader dialog(username,password);
    dialog.setModal(true);
    dialog.exec();
}


void BorrowedBooks::on_backBtn_clicked()
{
    this->close();
    Account dialog(username, password);
    dialog.setModal(true);
    dialog.exec();
}