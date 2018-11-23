#include "stdafx.h"
#include "tmp\moc_MainWnd.cpp"

QMutex mutex;

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

	m_btnSearch = new QPushButton("Search", this);

	m_lblResult = new QLabel("Result", this);

	m_progress = new QProgressBar(this);
	m_progress->setVisible(false);

	m_tree_result = new QTreeWidget(this);
	m_tree_result->setHeaderHidden(true);

	ltPath->addWidget(lblPath);
	ltPath->addWidget(m_le_root_path);
	ltPath->addWidget(btnBrowse);

	lbPhrase->addWidget(lblPhrase);
	lbPhrase->addWidget(m_le_find_phrase);

	ltMain->addLayout(ltPath);
	ltMain->addLayout(lbPhrase);
	ltMain->addWidget(m_btnSearch);
	ltMain->addWidget(m_lblResult);
	ltMain->addWidget(m_progress);
	ltMain->addWidget(m_tree_result);

	centralwidget->setLayout(ltMain);

	connect(btnBrowse, &QPushButton::released, this, &MainWnd::browseDirectory);
	connect(m_btnSearch, &QPushButton::released, this, &MainWnd::startSearch);
	connect(m_tree_result, &QTreeWidget::itemDoubleClicked, this, &MainWnd::openDocument);
	connect(m_progress, &QProgressBar::valueChanged, this, &MainWnd::progressChanged);

#ifdef _DEBUG
	m_le_find_phrase->setText("37");
	m_le_root_path->setText("C:/Work/UpWork/PDFinder");
#endif // DEBUG

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
	m_btnSearch->setEnabled(false);
	m_le_find_phrase->setEnabled(false);

	int count_entries = 0;
	m_tree_result->clear();
	m_lblResult->setText("Result");

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
	m_progress->setVisible(true);
	m_progress->setRange(0, list_file.size());
	m_progress->setValue(0);

	struct PDFProcessor
	{
		PDFProcessor(QString searchtext, QTreeWidget *tree, QProgressBar *bar)
			: m_searchtext(searchtext),
			m_tree(tree),
			m_bar(bar)
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

// 				m_bar->blockSignals(true);
// 				mutex.lock();
				int value = m_bar->value() + 1;
				QMetaObject::invokeMethod(m_bar, "setValue", Qt::QueuedConnection, Q_ARG(int, value));
// 				m_bar->blockSignals(false);
// 				mutex.unlock();
			}
			return file_path;
		}

		QString m_searchtext;
		QTreeWidget *m_tree;
		QProgressBar *m_bar;
	};

	QFutureWatcher<void> watcher;
	connect(&watcher, SIGNAL(finished()), this, SLOT(searchFinished()));
	QFuture<void> fut = QtConcurrent::mapped(list_file, PDFProcessor(m_le_find_phrase->text(), m_tree_result, m_progress));
	watcher.setFuture(fut);
}

void MainWnd::openDocument(QTreeWidgetItem * item, int column)
{
	qDebug() << "file:///" + item->data(0, Qt::UserRole).toString();
	QDesktopServices::openUrl(QUrl("file:///" + item->data(0, Qt::UserRole).toString(), QUrl::TolerantMode));
}

void MainWnd::searchFinished()
{
	//
	m_progress->setVisible(false);
}

void MainWnd::progressChanged(int value)
{
	if (value == m_progress->maximum())
	{
		m_le_find_phrase->setEnabled(true);
		m_btnSearch->setEnabled(true);
		m_progress->hide();
		int count_entries = 0;
		QTreeWidgetItemIterator it(m_tree_result, QTreeWidgetItemIterator::NoChildren);
		while (*it) {
			count_entries++;
			++it;
		}
		m_lblResult->setText("Result: [" + QString::number(m_tree_result->topLevelItemCount()) + " files\t" + QString::number(count_entries) + " entries]");
	}
}
