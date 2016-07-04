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
#define ITEM_COLOR_NORMAL "#f68"
#define ITEM_COLOR_PLAY "#129"
#define ITEM_COLOR_SEARCH "#19c"
#define CUR_ITEM_LOOP 0x1
#define SEQUENTIAL 0x2
#define LOOP 0x3
#define RANDOM 0x4
#define MEDIA_TYPE_MUSIC 0
#define MEDIA_TYPE_VIDEO 1


class PlaylistWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PlaylistWindow(QMediaPlaylist *playList,QWidget *parent = 0);

signals:
    void	currentItemChanged(QListWidgetItem * current, QListWidgetItem * previous);
    void	currentRowChanged(int currentRow);
    void	currentTextChanged(const QString & currentText);
    void	itemActivated(QListWidgetItem * item);
    void	itemChanged(QListWidgetItem * item);
    void	itemClicked(QListWidgetItem * item);
    void	itemDoubleClicked(QListWidgetItem * item);
    void	itemEntered(QListWidgetItem * item);
    void	itemPressed(QListWidgetItem * item);
    void	itemSelectionChanged();

public slots:
    void clear();
    void removeItems();
    void searchItem();
    void clearSearch();
    void setItemPlay(QListWidgetItem* item);
    void setItemPlay(int row);
    void setItemPlayView(QListWidgetItem* item);
    void setItemNormalView(QListWidgetItem* item);
    void setItemSearchView(QListWidgetItem* item);
    void setPlayMode();
    void next();
    void previous();
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
    int playBackMode = SEQUENTIAL;


private:
    void updateIndex();
    int getMediaType(const QString fileName);

public:
    int addItemFromLocal(const QStringList &addList,bool playNow = true);
    int addItemFromNet(const QString &additem,const QString &link,int id);


};

#endif // PLAYLISTVIEW_H
