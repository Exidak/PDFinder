#include "stdafx.h"
#include "tmp\moc_MainWnd.cpp"


MainWnd::MainWnd()
{
	QWidget *centralwidget = new QWidget(this);
	setCentralWidget(centralwidget);

	QVBoxLayout *ltMain = new QVBoxLayout(centralwidget);

	QHBoxLayout *ltPath = new QHBoxLayout(this);
	QLabel *lblPath = new QLabel("Path", this);
	m_le_root_path = new QLineEdit(this);
	m_le_root_path->setReadOnly(true);
	QPushButton *btnBrowse = new QPushButton("browse", this);

	QHBoxLayout *lbPhrase = new QHBoxLayout(this);
	QLabel *lblPhrase = new QLabel("Search for", this);
	m_le_find_phrase = new QLineEdit(this);

	QPushButton *btnSearch = new QPushButton("Search", this);

	m_lblResult = new QLabel("Result", this);

	m_tree_result = new QTreeWidget(this);
	m_tree_result->setHeaderHidden(true);

	ltPath->addWidget(lblPath);
	ltPath->addWidget(m_le_root_path);
	ltPath->addWidget(btnBrowse);

	lbPhrase->addWidget(lblPhrase);
	lbPhrase->addWidget(m_le_find_phrase);

	ltMain->addLayout(ltPath);
	ltMain->addLayout(lbPhrase);
	ltMain->addWidget(btnSearch);
	ltMain->addWidget(m_lblResult);
	ltMain->addWidget(m_tree_result);

	centralwidget->setLayout(ltMain);

	connect(btnBrowse, &QPushButton::released, this, &MainWnd::browseDirectory);
	connect(btnSearch, &QPushButton::released, this, &MainWnd::startSearch);
	connect(m_tree_result, &QTreeWidget::itemDoubleClicked, this, &MainWnd::openDocument);
}


MainWnd::~MainWnd()
{
}

void MainWnd::browseDirectory()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	m_le_root_path->setText(dir);
}

void MainWnd::startSearch()
{
	int count_entries = 0;
	m_tree_result->clear();

	QVector<QFileInfo> list_file;
	QDirIterator it(m_le_root_path->text(),QDirIterator::Subdirectories);
	while (it.hasNext()) 
	{
		it.next();
		if (it.fileInfo().suffix() == "pdf")
		{
			list_file.push_back(it.fileInfo());
		}
	}

	struct PDFProcessor
	{
		PDFProcessor(QString searchtext, QTreeWidget *tree)
			: m_searchtext(searchtext),
			m_tree(tree)
		{ }

		typedef QFileInfo result_type;

		QFileInfo operator()(const QFileInfo & file_path)
		{
			QProcess gzip;
			gzip.start("pdftotext.exe", QStringList() << file_path.absoluteFilePath());
			if (gzip.waitForFinished(600000))
			{
				QString txtPath = file_path.absolutePath() + "/" + file_path.completeBaseName() + ".txt";

				QList<QTreeWidgetItem*> children;

				QFile MyFile(txtPath);
				MyFile.open(QIODevice::ReadWrite);
				QTextStream in(&MyFile);
				QString line;
				do
				{
					line = in.readLine();
					if (line.contains(m_searchtext, Qt::CaseInsensitive))
					{
						QTreeWidgetItem *childitem = new QTreeWidgetItem();
						childitem->setText(0, line);
						children.push_back(childitem);
					}
				} while (!line.isNull());
				MyFile.close();

				if (!children.empty())
				{
					QTreeWidgetItem *item = new QTreeWidgetItem();
					item->setText(0, file_path.fileName() + " [" + QString::number(children.size()) + "]");
					item->setText(1, QString::number(children.size()));
					item->setData(0, Qt::UserRole, file_path.absoluteFilePath());
					item->addChildren(children);
					m_tree->addTopLevelItem(item);
				}

				QFile::remove(txtPath);
			}
			return file_path;
		}

		QString m_searchtext;
		QTreeWidget *m_tree;
	};

	QtConcurrent::map(list_file, PDFProcessor(m_le_find_phrase->text(), m_tree_result));

	m_lblResult->setText("Result: [" + QString::number(m_tree_result->topLevelItemCount())+" files\t"+ QString::number(count_entries) + " entries]");
}

void MainWnd::openDocument(QTreeWidgetItem * item, int column)
{
	qDebug() << "file:///" + item->data(0, Qt::UserRole).toString();
	QDesktopServices::openUrl(QUrl("file:///" + item->data(0, Qt::UserRole).toString(), QUrl::TolerantMode));
}

void searchText(QFileInfo & file_path)
{
	
}
