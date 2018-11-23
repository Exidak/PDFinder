#pragma once

void searchText(QFileInfo &file_path);

class MainWnd : public QMainWindow
{
	Q_OBJECT
public:
	MainWnd();
	~MainWnd();
private:
	QVector<QFileInfo> serachFiles();
private:
	QPushButton * m_btnBrowse;
	QLineEdit * m_le_root_path;
	QLineEdit * m_le_find_phrase;
	QPushButton *m_btnSearch;
	QTreeWidget * m_tree_result;
	QLabel *m_lblResult;
	QProgressBar *m_progress;
	QCheckBox *m_chb_deep;

	QFutureWatcher<QVector<QFileInfo>> *m_filesearch_watcher;
	QFutureWatcher<void> *m_textsearch_watcher;
private slots:
	void browseDirectory();
	void startSearch();
	void openDocument(QTreeWidgetItem *item, int column);

	void searchFilesFinished();
	void searchTextFinished();

	void saveResult();
	void loadResult();
};

