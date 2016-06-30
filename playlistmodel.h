#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QAbstractItemModel>

class PlaylistModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit PlaylistModel(QObject *parent = 0);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

	void  setPlaylist(QMediaPlaylist *playlist);
signals:

public slots:

private:
	QMediaPlaylist *m_playlist;
};

#endif // PLAYLISTWIDGET_H
