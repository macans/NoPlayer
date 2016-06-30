#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractItemModel(parent)
{

}

void PlaylistModel::setPlaylist(QMediaPlaylist *playlist)
{
	this->m_playlist = playlist;
}

int PlaylistModel::rowCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return m_playlist && (!parent.isValid() ? m_playlist->mediaCount() : 0);
}

int PlaylistModel::columnCount(const QModelIndex &parent /*= QModelIndex()*/) const
{
	return !parent.isValid() ? 1 : 0;
}

QT_NAMESPACE::QModelIndex PlaylistModel::index(int row, int column, const QModelIndex &parent /*= QModelIndex()*/) const
{
	return m_playlist && !parent.isValid()
		&& row >= 0 && row < m_playlist->mediaCount()
		&& column >= 0 && column < ColumnCount
		? createIndex(row, column)
		: QModelIndex();
}

QModelIndex PlaylistModel::parent(const QModelIndex &child) const
{
	Q_UNUSED(child);

	return QModelIndex();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role /*= Qt::DisplayRole*/) const
{
	if (index.isValid() && role == Qt::DisplayRole) {
		QVariant value = m_data[index];
		if (!value.isValid() && index.column() == Title) {
			QUrl location = m_playlist->media(index.row()).canonicalUrl();
			return QFileInfo(location.path()).fileName();
		}
		return value;
	}
	return QVariant();
}

