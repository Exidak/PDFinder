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
	QVector<QFileInfo> collectFiles();
private:
	QMenuBar * m_menu;
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

	struct UndoData
	{
		int m_index;
		QString m_parent_data;
		QString m_text;
		QString m_data_0;
		QString m_data_1;
		QStringList m_child_text;
	};

	QVector<UndoData> m_undo_stack;
private slots:
	void browseDirectory();
	void startSearch();
	void openDocument(QTreeWidgetItem *item, int column);

	void searchFilesFinished();
	void searchTextFinished();

	void saveResult();
	void loadResult();

	void hideResultLine();
	void showLastHiddenLine();
	void highlightItem();
	void unhighlightItem();

	void editItemText();
};

