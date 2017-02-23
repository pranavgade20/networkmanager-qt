/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was:
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef VPNCONNECTIONINTERFACE_H
#define VPNCONNECTIONINTERFACE_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>
#include "generictypes.h"

/*
 * Proxy class for interface org.freedesktop.NetworkManager.VPN.Connection
 */
class OrgFreedesktopNetworkManagerVPNConnectionInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
#ifdef NMQT_STATIC
    {
        return "org.kde.fakenetwork.Settings.VPN.Connection";
    }
#else
    {
        return "org.freedesktop.NetworkManager.VPN.Connection";
    }
#endif

public:
    OrgFreedesktopNetworkManagerVPNConnectionInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);

    ~OrgFreedesktopNetworkManagerVPNConnectionInterface();

    Q_PROPERTY(QString Banner READ banner)
    inline QString banner() const
    {
        return qvariant_cast< QString >(property("Banner"));
    }

    Q_PROPERTY(uint VpnState READ vpnState)
    inline uint vpnState() const
    {
        return qvariant_cast< uint >(property("VpnState"));
    }

public Q_SLOTS: // METHODS
Q_SIGNALS: // SIGNALS
    void PropertiesChanged(const QVariantMap &properties);
    void VpnStateChanged(uint state, uint reason);
};

#endif