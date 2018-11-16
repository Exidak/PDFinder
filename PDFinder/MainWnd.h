#pragma once
class MainWnd : public QMainWindow
{
	Q_OBJECT
public:
	MainWnd();
	~MainWnd();
private:
	QLineEdit * m_le_root_path;
	QLineEdit * m_le_find_phrase;
	QTreeWidget * m_tree_result;
	QLabel *m_lblResult;
private slots:
	void browseDirectory();
	void startSearch();
	void openDocument(QTreeWidgetItem *item, int column);
};

