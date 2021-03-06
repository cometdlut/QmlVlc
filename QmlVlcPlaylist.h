/*******************************************************************************
* Copyright (c) 2014, Sergey Radionov <rsatom_gmail.com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright notice,
*      this list of conditions and the following disclaimer in the documentation
*      and/or other materials provided with the distribution.

* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
* OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef QMLVLCPLAYLIST_H
#define QMLVLCPLAYLIST_H

#include <QObject>
#include <QQmlListProperty>

#include "libvlc_wrapper/vlc_player.h"

#include "QmlVlcMediaDesc.h"

class QmlVlcPlaylist : public QObject
{
    Q_OBJECT
public:
    QmlVlcPlaylist( vlc::player& player )
        : m_player( player ) { }

    typedef QQmlListProperty<QmlVlcMediaDesc> ItemsProperty_t;

    enum Mode {
        Normal = vlc::mode_normal,
        Loop = vlc::mode_loop,
        Single = vlc::mode_single,
    };
    Q_ENUMS( Mode )

    Q_PROPERTY( unsigned itemCount READ get_itemCount )
    Q_PROPERTY( bool isPlaying READ get_isPlaying )

    Q_PROPERTY( int currentItem READ get_current WRITE set_current NOTIFY currentItemChanged )
    Q_PROPERTY( Mode mode READ get_mode WRITE set_mode )

    Q_PROPERTY( QQmlListProperty<QmlVlcMediaDesc> items READ get_items )

    unsigned get_itemCount();
    bool get_isPlaying();

    int get_current();
    void set_current( unsigned idx );

    Mode get_mode();
    void set_mode( Mode );

    ItemsProperty_t get_items();

    Q_INVOKABLE int add( const QString& mrl );
    Q_INVOKABLE int addWithOptions( const QString& mrl, const QStringList& options );

    Q_INVOKABLE void play();
    Q_INVOKABLE bool playItem( unsigned idx );
    Q_INVOKABLE void pause();
    Q_INVOKABLE void togglePause();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void next();
    Q_INVOKABLE void prev();
    Q_INVOKABLE void clear();
    Q_INVOKABLE bool removeItem( unsigned idx );

Q_SIGNALS:
    //will emit from QmlPlayerProxy
    void currentItemChanged();

private:
    static int itemsCount( ItemsProperty_t* );
    static QmlVlcMediaDesc* getItem( ItemsProperty_t*, int index );
    static void itemsClear( ItemsProperty_t* );

private:
    vlc::player& m_player;
};

#endif //QMLVLCPLAYLIST_H
