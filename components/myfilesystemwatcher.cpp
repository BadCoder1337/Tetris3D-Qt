#include "myfilesystemwatcher.h"

MyFileSystemWatcher* MyFileSystemWatcher::instance = NULL;
MyFileSystemWatcher::GC MyFileSystemWatcher::GC::gc;

MyFileSystemWatcher::MyFileSystemWatcher(QObject *parent):QObject(parent)
{

}

// Monitor files or directories
void MyFileSystemWatcher::addWatchPath(QString path)
{
    qDebug() << QString("Add to watch: %1").arg(path);
    instance->fileSystemWatcher->addPath(path);

    // If the add path is a directory, save the current content list
    QFileInfo file(path);
    if (file.isDir())
    {
        const QDir dirw(path);
        instance->currentContentsMap[path] = dirw.entryList(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files, QDir::DirsFirst);
    }
}

MyFileSystemWatcher *MyFileSystemWatcher::getInstance()
{
    if (instance == NULL)
    {
        instance = new MyFileSystemWatcher();
        instance->fileSystemWatcher = new QFileSystemWatcher(instance);

        connect(instance->fileSystemWatcher, SIGNAL(directoryChanged(QString)), instance, SLOT(directoryUpdated(QString)));
        connect(instance->fileSystemWatcher, SIGNAL(fileChanged(QString)), instance, SLOT(fileUpdated(QString)));
    }
    return instance;
}

// Called whenever any monitored directory is updated (added, deleted, renamed).
void MyFileSystemWatcher::directoryUpdated(const QString &path)
{
    // Find the file or directory that has changed in the path
    QStringList currEntryList = currentContentsMap[path];
    const QDir dir(path);

    QStringList newEntryList = dir.entryList(QDir::NoDotAndDotDot  | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

    QSet<QString> newDirSet = QSet<QString>::fromList(newEntryList);
    QSet<QString> currentDirSet = QSet<QString>::fromList(currEntryList);

    // Added file
    QSet<QString> newFiles = newDirSet - currentDirSet;
    QStringList newFile = newFiles.toList();

    // file has been removed
    QSet<QString> deletedFiles = currentDirSet - newDirSet;
    QStringList deleteFile = deletedFiles.toList();

    // update current settings
    currentContentsMap[path] = newEntryList;

    if (!newFile.isEmpty() && !deleteFile.isEmpty())
    {
        // file/directory rename
        if ((newFile.count() == 1) && (deleteFile.count() == 1))
        {
            emit sigRenameFileOrDir(deleteFile.first(),newFile.first());
        }
    }
    else
    {
        // Add new file/directory to Dir
        if (!newFile.isEmpty())
        {
            emit sigAddFileOrDir(newFile.first());
        }

        // Delete files/directories from Dir
        if (!deleteFile.isEmpty())
        {
            emit sigDeleteFileOrDir(deleteFile.first());
        }
    }
}

// The file being listened to must already exist. The deletion and new file cannot be detected. It will only be triggered if the file name or file content is modified.
void MyFileSystemWatcher::fileUpdated(const QString &file)
{
    QFileInfo fileInfo(file);
    QString strPath = fileInfo.absolutePath();
    QString strName = fileInfo.fileName();

    emit sigFileUpdated(strName,strPath);
}
