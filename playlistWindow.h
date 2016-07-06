#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H
#include <QListWidget>
#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include  <QLineEdit>
#include <QMediaPlaylist>
#include <QFileInfo>
#include <QFileDialog>
#include <QtScript>

#include "playconfig.h"


class PlaylistWindow : public QWidget
{
    Q_OBJECT
public:
	explicit PlaylistWindow(QMediaPlaylist *playList, QWidget *parent = 0, int playModel = QMediaPlaylist::Sequential);

signals:
    void	currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous);
    void	currentRowChanged(int currentRow);
    void	currentTextChanged(const QString & currentText);
    void	itemActivated(QListWidgetItem * item);
    void	itemChanged(QListWidgetItem * item);
    void	itemClicked(QListWidgetItem * item);
    void	itemDoubleClicked(QListWidgetItem * item, bool doubleClicked = true);
    void	itemEntered(QListWidgetItem * item);
    void	itemPressed(QListWidgetItem * item);
    void	itemSelectionChanged();
	void playlistWindowClosed();

public slots:
    void clear();
    void removeItems();
    void searchItem();
	void clearSearch();
    void setItemPlay(int row);
	void setPlaylistIndex(QListWidgetItem *item);
    void setItemPlayView(QListWidgetItem* item);
    void setItemNormalView(QListWidgetItem* item);
    void setItemSearchView(QListWidgetItem* item);
    void setPlayMode();
    void next();
    void previous();
    void openfiles();
	void closeEvent(QCloseEvent *event);
	void savePlaylist();
	void loadPlaylist();
private:
    QListWidget *listWidget;
    QLineEdit *search_edit;
    QPushButton *playType;
    QPushButton *search_btn;
    QPushButton *delBtn;
    QPushButton *clearBtn;
    QPushButton *addBtn;
    QList<QListWidgetItem*> searchList;//记录搜索到的item
    bool search_flag = false;
    QMediaPlaylist *playlist;
    int playBackMode;

	bool doubleClicked;


private:
    void updateIndex();
    int getMediaType(const QString fileName);

public:
    int addItemFromLocal(const QStringList &addList,bool playNow = true);
    int addItemFromNet(const QString &additem,const QString &link,int id, bool playNow = true);
	

};

#endif // PLAYLISTVIEW_H
