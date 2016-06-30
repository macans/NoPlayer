#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H

#include <QAbstractItemModel>
#include <QMediaPlaylist>
#include <QFileInfo>

class PlaylistModel : public QAbstractItemModel
{
    Q_OBJECT
public:
	enum Column
	{
		Title = 0,
		ColumnCount
	};
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
	QMap<QModelIndex, QVariant> m_data;
};

#endif // PLAYLISTWIDGET_H
