#pragma once

void searchText(QFileInfo &file_path);

class MainWnd : public QMainWindow
{
	Q_OBJECT
public:
	MainWnd();
	~MainWnd();
private:
	QLineEdit * m_le_root_path;
	QLineEdit * m_le_find_phrase;
	QPushButton *m_btnSearch;
	QTreeWidget * m_tree_result;
	QLabel *m_lblResult;
	QProgressBar *m_progress;
private slots:
	void browseDirectory();
	void startSearch();
	void openDocument(QTreeWidgetItem *item, int column);
	void searchFinished();
	void progressChanged(int value);
};

