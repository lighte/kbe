/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#ifndef READWRITEMANAGER_H
#define READWRITEMANAGER_H

#include <QObject>
#include <QMap>

#include "interfaces/fileloaderinterface.h"
#include "interfaces/filewriterinterface.h"

class FileLoaderFactoryInterface;
class FileWriterFactoryInterface;

class ReadWriteManager : public QObject
{
Q_OBJECT
public:

    explicit ReadWriteManager(QObject *parent = 0);
    virtual ~ReadWriteManager();

    static ReadWriteManager* instance();

    //! Get extension name from filter description
    static QString extFromFilter(const QString &filter);

private:
    //! Poitner to instance
    static ReadWriteManager *mInstance;

public:
    /*! Register file loader factory
      @note Factory will be removed automaticaly on manager shutdown. Also
            alocated for factory memory will be free.
      */
    void registerFileLoaderFactory(FileLoaderFactoryInterface *factory);

    /*! Register file writer factory
      @note Factory will be removed automaticaly on manager shutdown. Also
            alocated for factory memory will be free.
      */
    void registerFileWriterFactory(FileWriterFactoryInterface *factory);

    /*! Unregister all factories
      */
    void unregisterAllFactories();

    /*! Create file loader
      @param ext    File extension
      */
    FileLoaderInterface* createLoader(const QString &ext);

    /*! Create file writer
      @param ext    File extension
      */
    FileWriterInterface* createWriter(const QString &ext);

    /*! Get filters of registered loaders for file opening
      @note Return string with filters description
      */
    QString openFilters() const;

    /*! Get filters of registered writers for file saving
      @note Return string with filters description
      */
    QString saveFilters() const;

    /*! Get filters of registered loaders for file importing
      @note Return string with filters description
      */
    QString importFilters() const;

    /*! Get filters of registered writers for file exporting
      @note Return string with filters description
      */
    QString exportFilters() const;

    /*! Get loader filters for a specified loader type
      */
    QString loaderFilters(FileLoaderInterface::Type type) const;

    /*! Get writer filters for a specified writer type
      */
    QString writerFilters(FileWriterInterface::Type type) const;

    /*!
     * @return all registered loader extensions
     */
    QList<QString> registeredLoaderExtensions() const;

    /*!
     * @return all registered loader extensions
     */
    QList<QString> registeredWriterExtensions() const;


protected:
    //! Map of file loader factories
    typedef QMap<QString, FileLoaderFactoryInterface*> StringFileLoaderFactoryMap;
    StringFileLoaderFactoryMap mFileLoaderFactories;

    //! Map of file wrtier factories
    typedef QMap<QString, FileWriterFactoryInterface*> StringFileWriterFactoryMap;
    StringFileWriterFactoryMap mFileWriteFactories;


signals:

public slots:

};

#endif // READWRITEMANAGER_H