/*
    Copyright 2012-2013  Jan Grulich <jgrulich@redhat.com>
    Copyright 2013 Daniel Nicoletti <dantti12@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "connectionsettings.h"
#include "connectionsettings_p.h"

#include "wiredsetting.h"
#include "olpcmeshsetting.h"
#include "wirelesssetting.h"
#include "wirelesssecuritysetting.h"
#include "security8021xsetting.h"
#include "adslsetting.h"
#include "bluetoothsetting.h"
#include "bondsetting.h"
#include "bridgesetting.h"
#include "bridgeportsetting.h"
#include "gsmsetting.h"
#include "cdmasetting.h"
#include "infinibandsetting.h"
#include "ipv4setting.h"
#include "ipv6setting.h"
#include "pppsetting.h"
#include "pppoesetting.h"
#include "serialsetting.h"
#include "tunsetting.h"
#include "vlansetting.h"
#include "vpnsetting.h"
#include "wimaxsetting.h"
#include "iptunnelsetting.h"

#undef signals
#include <libnm/NetworkManager.h>

#if !NM_CHECK_VERSION(1, 6, 0)
#define NM_SETTING_CONNECTION_AUTOCONNECT_RETRIES "autoconnect-retries"
#endif

#include "teamsetting.h"
#include "genericsetting.h"

#include <QUuid>

namespace NetworkManager {
    extern int checkVersion(const int x, const int y, const int z);
}

NetworkManager::ConnectionSettingsPrivate::ConnectionSettingsPrivate(ConnectionSettings *q)
    : name(NM_SETTING_CONNECTION_SETTING_NAME)
    , uuid(QUuid().toString())
    , type(ConnectionSettings::Wired)
    , autoconnect(true)
    , readOnly(false)
    , gatewayPingTimeout(0)
    , autoconnectPriority(0)
    , autoconnectRetries(-1)
    , autoconnectSlaves(ConnectionSettings::SlavesDefault)
    , lldp(ConnectionSettings::LldpDefault)
    , metered(ConnectionSettings::MeteredUnknown)
    , q_ptr(q)
{ }

void NetworkManager::ConnectionSettingsPrivate::addSetting(const NetworkManager::Setting::Ptr &setting)
{
    settings.push_back(setting);
}

void NetworkManager::ConnectionSettingsPrivate::clearSettings()
{
    settings.clear();
}

void NetworkManager::ConnectionSettingsPrivate::initSettings(NMBluetoothCapabilities bt_cap)
{
    clearSettings();

    switch (type) {
    case ConnectionSettings::Adsl:
        addSetting(Setting::Ptr(new AdslSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        break;
    case ConnectionSettings::Bond:
        addSetting(Setting::Ptr(new BondSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        break;
    case ConnectionSettings::Bluetooth:
        addSetting(Setting::Ptr(new BluetoothSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        //addSetting(Setting::Ptr(new Ipv6Setting()));
        if (bt_cap == NM_BT_CAPABILITY_DUN) {
            addSetting(Setting::Ptr(new GsmSetting()));
            addSetting(Setting::Ptr(new PppSetting()));
            addSetting(Setting::Ptr(new SerialSetting()));
        }
        break;
    case ConnectionSettings::Bridge:
        addSetting(Setting::Ptr(new BridgeSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        break;
    case ConnectionSettings::Cdma:
        addSetting(Setting::Ptr(new CdmaSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        if (NetworkManager::checkVersion(1, 0, 0)) {
            addSetting(Setting::Ptr(new Ipv6Setting()));
        }
        addSetting(Setting::Ptr(new PppSetting()));
        break;
    case ConnectionSettings::Gsm:
        addSetting(Setting::Ptr(new GsmSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        if (NetworkManager::checkVersion(1, 0, 0)) {
            addSetting(Setting::Ptr(new Ipv6Setting()));
        }
        addSetting(Setting::Ptr(new PppSetting()));
        break;
    case ConnectionSettings::Infiniband:
        addSetting(Setting::Ptr(new InfinibandSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        break;
    case ConnectionSettings::OLPCMesh:
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        addSetting(Setting::Ptr(new OlpcMeshSetting()));
        break;
    case ConnectionSettings::Pppoe:
        addSetting(Setting::Ptr(new Ipv4Setting()));
        //addSetting(new Ipv6Setting()));
        addSetting(Setting::Ptr(new PppSetting()));
        addSetting(Setting::Ptr(new PppoeSetting()));
        addSetting(Setting::Ptr(new WiredSetting()));
        break;
    case ConnectionSettings::Vlan:
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        addSetting(Setting::Ptr(new VlanSetting()));
        break;
    case ConnectionSettings::Vpn:
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        addSetting(Setting::Ptr(new VpnSetting()));
        break;
    case ConnectionSettings::Wimax:
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        addSetting(Setting::Ptr(new WimaxSetting()));
        break;
    case ConnectionSettings::Wired:
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        addSetting(Setting::Ptr(new Security8021xSetting()));
        addSetting(Setting::Ptr(new WiredSetting()));
        break;
    case ConnectionSettings::Wireless:
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        addSetting(Setting::Ptr(new Security8021xSetting()));
        addSetting(Setting::Ptr(new WirelessSetting()));
        addSetting(Setting::Ptr(new WirelessSecuritySetting()));
        break;
    case ConnectionSettings::Team:
        addSetting(Setting::Ptr(new TeamSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        break;
    case ConnectionSettings::Generic:
        addSetting(Setting::Ptr(new GenericSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        break;
    case ConnectionSettings::Tun:
        addSetting(Setting::Ptr(new TunSetting()));
        addSetting(Setting::Ptr(new Ipv4Setting()));
        addSetting(Setting::Ptr(new Ipv6Setting()));
        addSetting(Setting::Ptr(new IpTunnelSetting()));
        break;
    case ConnectionSettings::Unknown:
    default:
        break;
    }
}

void NetworkManager::ConnectionSettingsPrivate::initSettings(const NetworkManager::ConnectionSettings::Ptr &connectionSettings)
{
    Q_Q(ConnectionSettings);

    clearSettings();

    switch (type) {
    case ConnectionSettings::Adsl:
        addSetting(connectionSettings->setting(Setting::Adsl));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        break;
    case ConnectionSettings::Bond:
        addSetting(connectionSettings->setting(Setting::Bond));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        break;
    case ConnectionSettings::Bluetooth:
        addSetting(connectionSettings->setting(Setting::Bluetooth));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        if (NetworkManager::checkVersion(1, 0, 0)) {
            addSetting(connectionSettings->setting(Setting::Ipv6));
        }
        if (q->setting(Setting::Gsm) && q->setting(Setting::Ppp) && q->setting(Setting::Serial)) {
            addSetting(connectionSettings->setting(Setting::Gsm));
            addSetting(connectionSettings->setting(Setting::Ppp));
            addSetting(connectionSettings->setting(Setting::Serial));
        }
        break;
    case ConnectionSettings::Bridge:
        addSetting(connectionSettings->setting(Setting::Bridge));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        break;
    case ConnectionSettings::Cdma:
        addSetting(connectionSettings->setting(Setting::Cdma));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        if (NetworkManager::checkVersion(1, 0, 0)) {
            addSetting(connectionSettings->setting(Setting::Ipv6));
        }
        addSetting(connectionSettings->setting(Setting::Ppp));
        break;
    case ConnectionSettings::Gsm:
        addSetting(connectionSettings->setting(Setting::Gsm));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        if (NetworkManager::checkVersion(1, 0, 0)) {
            addSetting(connectionSettings->setting(Setting::Ipv6));
        }
        addSetting(connectionSettings->setting(Setting::Ppp));
        break;
    case ConnectionSettings::Infiniband:
        addSetting(connectionSettings->setting(Setting::Infiniband));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        break;
    case ConnectionSettings::OLPCMesh:
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        addSetting(connectionSettings->setting(Setting::OlpcMesh));
        break;
    case ConnectionSettings::Pppoe:
        addSetting(connectionSettings->setting(Setting::Ipv4));
        //addSetting(Ipv6Setting(connectionSettings->setting(Setting::Ipv6));
        addSetting(connectionSettings->setting(Setting::Ppp));
        addSetting(connectionSettings->setting(Setting::Pppoe));
        addSetting(connectionSettings->setting(Setting::Wired));
        break;
    case ConnectionSettings::Vlan:
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        addSetting(connectionSettings->setting(Setting::Vlan));
        break;
    case ConnectionSettings::Vpn:
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        addSetting(connectionSettings->setting(Setting::Vpn));
        break;
    case ConnectionSettings::Wimax:
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        addSetting(connectionSettings->setting(Setting::Wimax));
        break;
    case ConnectionSettings::Wired:
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        addSetting(connectionSettings->setting(Setting::Security8021x));
        addSetting(connectionSettings->setting(Setting::Wired));
        break;
    case ConnectionSettings::Wireless:
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        addSetting(connectionSettings->setting(Setting::Security8021x));
        addSetting(connectionSettings->setting(Setting::Wireless));
        addSetting(connectionSettings->setting(Setting::WirelessSecurity));
        break;
    case ConnectionSettings::Team:
        addSetting(connectionSettings->setting(Setting::Team));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        break;
    case ConnectionSettings::Generic:
        addSetting(connectionSettings->setting(Setting::Generic));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        break;
    case ConnectionSettings::Tun:
        addSetting(connectionSettings->setting(Setting::Tun));
        addSetting(connectionSettings->setting(Setting::Ipv4));
        addSetting(connectionSettings->setting(Setting::Ipv6));
        break;
    case ConnectionSettings::Unknown:
    default:
        break;
    }
}

NetworkManager::ConnectionSettings::ConnectionType NetworkManager::ConnectionSettings::typeFromString(const QString &typeString)
{
    ConnectionSettings::ConnectionType type = Wired;

    if (typeString == QLatin1String(NM_SETTING_ADSL_SETTING_NAME)) {
        type = Adsl;
    } else if (typeString == QLatin1String(NM_SETTING_BLUETOOTH_SETTING_NAME)) {
        type = Bluetooth;
    } else if (typeString == QLatin1String(NM_SETTING_BOND_SETTING_NAME)) {
        type = Bond;
    } else if (typeString == QLatin1String(NM_SETTING_BRIDGE_SETTING_NAME)) {
        type = Bridge;
    } else if (typeString == QLatin1String(NM_SETTING_CDMA_SETTING_NAME)) {
        type = Cdma;
    } else if (typeString == QLatin1String(NM_SETTING_GSM_SETTING_NAME)) {
        type = Gsm;
    } else if (typeString == QLatin1String(NM_SETTING_INFINIBAND_SETTING_NAME)) {
        type = Infiniband;
    } else if (typeString == QLatin1String(NM_SETTING_OLPC_MESH_SETTING_NAME)) {
        type = OLPCMesh;
    } else if (typeString == QLatin1String(NM_SETTING_PPPOE_SETTING_NAME)) {
        type = Pppoe;
    } else if (typeString == QLatin1String(NM_SETTING_VLAN_SETTING_NAME)) {
        type = Vlan;
    } else if (typeString == QLatin1String(NM_SETTING_VPN_SETTING_NAME)) {
        type = Vpn;
    } else if (typeString == QLatin1String(NM_SETTING_WIMAX_SETTING_NAME)) {
        type = Wimax;
    } else if (typeString == QLatin1String(NM_SETTING_WIRED_SETTING_NAME)) {
        type = Wired;
    } else if (typeString == QLatin1String(NM_SETTING_WIRELESS_SETTING_NAME)) {
        type = Wireless;
    } else if (typeString == QLatin1String(NM_SETTING_TEAM_SETTING_NAME)) {
        type = Team;
    } else if (typeString == QLatin1String(NM_SETTING_GENERIC_SETTING_NAME)) {
        type = Generic;
    } else if (typeString == QLatin1String(NM_SETTING_TUN_SETTING_NAME)) {
        type = Tun;
    }

    return type;
}

QString NetworkManager::ConnectionSettings::typeAsString(NetworkManager::ConnectionSettings::ConnectionType type)
{
    QString typeString;

    switch (type) {
    case Adsl:
        typeString = QLatin1String(NM_SETTING_ADSL_SETTING_NAME);
        break;
    case Bond:
        typeString = QLatin1String(NM_SETTING_BOND_SETTING_NAME);
        break;
    case Bluetooth:
        typeString = QLatin1String(NM_SETTING_BLUETOOTH_SETTING_NAME);
        break;
    case Bridge:
        typeString = QLatin1String(NM_SETTING_BRIDGE_SETTING_NAME);
        break;
    case Cdma:
        typeString = QLatin1String(NM_SETTING_CDMA_SETTING_NAME);
        break;
    case Gsm:
        typeString = QLatin1String(NM_SETTING_GSM_SETTING_NAME);
        break;
    case Infiniband:
        typeString = QLatin1String(NM_SETTING_INFINIBAND_SETTING_NAME);
        break;
    case OLPCMesh:
        typeString = QLatin1String(NM_SETTING_OLPC_MESH_SETTING_NAME);
        break;
    case Pppoe:
        typeString = QLatin1String(NM_SETTING_PPPOE_SETTING_NAME);
        break;
    case Vlan:
        typeString = QLatin1String(NM_SETTING_VLAN_SETTING_NAME);
        break;
    case Vpn:
        typeString = QLatin1String(NM_SETTING_VPN_SETTING_NAME);
        break;
    case Wimax:
        typeString = QLatin1String(NM_SETTING_WIMAX_SETTING_NAME);
        break;
    case Wired:
        typeString = QLatin1String(NM_SETTING_WIRED_SETTING_NAME);
        break;
    case Wireless:
        typeString = QLatin1String(NM_SETTING_WIRELESS_SETTING_NAME);
        break;
    case Team:
        typeString = QLatin1String(NM_SETTING_TEAM_SETTING_NAME);
        break;
    case Generic:
        typeString = QLatin1String(NM_SETTING_GENERIC_SETTING_NAME);
        break;
    case Tun:
        typeString = QLatin1String(NM_SETTING_TUN_SETTING_NAME);
        break;
    default:
        break;
    };

    return typeString;
}

QString NetworkManager::ConnectionSettings::createNewUuid()
{
    return QUuid::createUuid().toString().mid(1, QUuid::createUuid().toString().length() - 2);
}

NetworkManager::ConnectionSettings::ConnectionSettings()
    : d_ptr(new ConnectionSettingsPrivate(this))
{ }

NetworkManager::ConnectionSettings::ConnectionSettings(NetworkManager::ConnectionSettings::ConnectionType type, NMBluetoothCapabilities bt_cap)
    : d_ptr(new ConnectionSettingsPrivate(this))
{
    setConnectionType(type, bt_cap);
}

NetworkManager::ConnectionSettings::ConnectionSettings(const NetworkManager::ConnectionSettings::Ptr &other)
    : d_ptr(new ConnectionSettingsPrivate(this))
{
    Q_D(ConnectionSettings);

    setId(other->id());
    setUuid(other->uuid());
    setInterfaceName(other->interfaceName());
    setConnectionType(other->connectionType());
    setPermissions(other->permissions());
    setAutoconnect(other->autoconnect());
    setAutoconnectPriority(other->autoconnectPriority());
    setTimestamp(other->timestamp());
    setReadOnly(other->readOnly());
    setZone(other->zone());
    setMaster(other->master());
    setSlaveType(other->slaveType());
    setGatewayPingTimeout(other->gatewayPingTimeout());
    setAutoconnectRetries(other->autoconnectRetries());
    setAutoconnectSlaves(other->autoconnectSlaves());
    setLldp(other->lldp());
    setMetered(other->metered());
    setStableId(other->stableId());

    d->initSettings(other);
}

NetworkManager::ConnectionSettings::ConnectionSettings(const NMVariantMapMap &map)
    : d_ptr(new ConnectionSettingsPrivate(this))
{
    fromMap(map);
}

NetworkManager::ConnectionSettings::~ConnectionSettings()
{
    d_ptr->clearSettings();

    delete d_ptr;
}

void NetworkManager::ConnectionSettings::fromMap(const NMVariantMapMap &map)
{
    QVariantMap connectionSettings = map.value(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME));

    setId(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_ID)).toString());
    setUuid(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_UUID)).toString());
    setConnectionType(typeFromString(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_TYPE)).toString()));

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_INTERFACE_NAME))) {
        setInterfaceName(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_INTERFACE_NAME)).toString());
    }
    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_PERMISSIONS))) {
        QStringList permissions = connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_PERMISSIONS)).toStringList();
        Q_FOREACH (const QString & permission, permissions) {
            const QStringList split = permission.split(QLatin1String(":"), QString::KeepEmptyParts);
            addToPermissions(split.at(1), split.at(2));
        }
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT))) {
        setAutoconnect(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT)).toBool());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_PRIORITY))) {
        setAutoconnectPriority(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_PRIORITY)).toInt());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_TIMESTAMP))) {
        const int timestamp = connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_TIMESTAMP)).toInt();
        QDateTime dateTime;
        dateTime.setTime_t(timestamp);
        setTimestamp(dateTime);
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_READ_ONLY))) {
        setReadOnly(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_READ_ONLY)).toBool());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_ZONE))) {
        setZone(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_ZONE)).toString());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_MASTER))) {
        setMaster(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_MASTER)).toString());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_SLAVE_TYPE))) {
        setSlaveType(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_SLAVE_TYPE)).toString());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_SECONDARIES))) {
        setSecondaries(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_SECONDARIES)).toStringList());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_GATEWAY_PING_TIMEOUT))) {
        setGatewayPingTimeout(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_GATEWAY_PING_TIMEOUT)).toUInt());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_RETRIES))) {
        setAutoconnectRetries(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_RETRIES)).toInt());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_SLAVES))) {
        setAutoconnectSlaves((NetworkManager::ConnectionSettings::AutoconnectSlaves)connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_SLAVES)).toInt());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_LLDP))) {
        setLldp((NetworkManager::ConnectionSettings::Lldp)connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_LLDP)).toInt());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_METERED))) {
        setMetered((NetworkManager::ConnectionSettings::Metered)connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_METERED)).toInt());
    }

    if (connectionSettings.contains(QLatin1String(NM_SETTING_CONNECTION_STABLE_ID))) {
        setStableId(connectionSettings.value(QLatin1String(NM_SETTING_CONNECTION_STABLE_ID)).toString());
    }

    Q_FOREACH (const Setting::Ptr & setting, settings()) {
        if (map.contains(setting->name())) {
            setting->fromMap(map.value(setting->name()));
            setting->setInitialized(true);
        } else {
            setting->setInitialized(false);
        }
    }
}

NMVariantMapMap NetworkManager::ConnectionSettings::toMap() const
{
    NMVariantMapMap result;
    QVariantMap connectionSetting;

    if (!id().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_ID), id());
    }

    if (!uuid().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_UUID), uuid());
    }

    if (connectionType()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_TYPE), typeAsString(connectionType()));
    }

    if (!interfaceName().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_INTERFACE_NAME), interfaceName());
    }

    if (!permissions().isEmpty()) {
        QStringList perm;
        QHash<QString, QString> perms = permissions();
        QHash<QString, QString>::const_iterator it = perms.constBegin();
        while (it != perms.constEnd()) {
            const QString tmp = "user:" + it.key() + ':' + it.value();
            perm << tmp;
            ++it;
        }

        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_PERMISSIONS), perm);
    }

    if (!autoconnect()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT), autoconnect());
    }

    if (autoconnectPriority()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_PRIORITY), autoconnectPriority());
    }

    if (timestamp().isValid()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_TIMESTAMP), timestamp().toTime_t());
    }

    if (readOnly()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_READ_ONLY), readOnly());
    }

    if (!zone().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_ZONE), zone());
    }

    if (!master().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_MASTER), master());
    }

    if (!slaveType().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_SLAVE_TYPE), slaveType());
    }

    if (!secondaries().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_SECONDARIES), secondaries());
    }

    if (gatewayPingTimeout()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_GATEWAY_PING_TIMEOUT), gatewayPingTimeout());
    }

    if (autoconnectRetries() >= 0) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_RETRIES), autoconnectRetries());
    }

    connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_AUTOCONNECT_SLAVES), autoconnectSlaves());
    connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_LLDP), lldp());
    connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_METERED), metered());

    if (!stableId().isEmpty()) {
        connectionSetting.insert(QLatin1String(NM_SETTING_CONNECTION_STABLE_ID), stableId());
    }

    result.insert(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME), connectionSetting);

    Q_FOREACH (const Setting::Ptr & setting, settings()) {
        QVariantMap map = setting->toMap();
        if (!setting->isNull()) {
            result.insert(setting->name(), map);
        }
    }
    return result;
}

QString NetworkManager::ConnectionSettings::name() const
{
    Q_D(const ConnectionSettings);

    return d->name;
}

void NetworkManager::ConnectionSettings::setId(const QString &id)
{
    Q_D(ConnectionSettings);

    d->id = id;
}

QString NetworkManager::ConnectionSettings::id() const
{
    Q_D(const ConnectionSettings);

    return d->id;
}

void NetworkManager::ConnectionSettings::setUuid(const QString &uuid)
{
    Q_D(ConnectionSettings);

    d->uuid = uuid;
}

QString NetworkManager::ConnectionSettings::uuid() const
{
    Q_D(const ConnectionSettings);

    return d->uuid;
}

void NetworkManager::ConnectionSettings::setInterfaceName(const QString &interfaceName)
{
    Q_D(ConnectionSettings);

    d->interfaceName = interfaceName;
}

QString NetworkManager::ConnectionSettings::interfaceName() const
{
    Q_D(const ConnectionSettings);

    return d->interfaceName;
}

void NetworkManager::ConnectionSettings::setConnectionType(NetworkManager::ConnectionSettings::ConnectionType type, NMBluetoothCapabilities bt_cap)
{
    Q_D(ConnectionSettings);

    d->type = type;
    d->initSettings(bt_cap);
}

NetworkManager::ConnectionSettings::ConnectionType NetworkManager::ConnectionSettings::connectionType() const
{
    Q_D(const ConnectionSettings);

    return d->type;
}

void NetworkManager::ConnectionSettings::addToPermissions(const QString &user, const QString &type)
{
    Q_D(ConnectionSettings);

    d->permissions.insert(user, type);
}

void NetworkManager::ConnectionSettings::setPermissions(const QHash< QString, QString > &perm)
{
    Q_D(ConnectionSettings);

    d->permissions = perm;
}

QHash< QString, QString > NetworkManager::ConnectionSettings::permissions() const
{
    Q_D(const ConnectionSettings);

    return d->permissions;
}

void NetworkManager::ConnectionSettings::setAutoconnect(bool autoconnect)
{
    Q_D(ConnectionSettings);

    d->autoconnect = autoconnect;
}

bool NetworkManager::ConnectionSettings::autoconnect() const
{
    Q_D(const ConnectionSettings);

    return d->autoconnect;
}

void NetworkManager::ConnectionSettings::setAutoconnectPriority(int priority)
{
    Q_D(ConnectionSettings);

    d->autoconnectPriority = priority;
}

int NetworkManager::ConnectionSettings::autoconnectPriority() const
{
    Q_D(const ConnectionSettings);

    return d->autoconnectPriority;
}

void NetworkManager::ConnectionSettings::setTimestamp(const QDateTime &timestamp)
{
    Q_D(ConnectionSettings);

    d->timestamp = timestamp;
}

QDateTime NetworkManager::ConnectionSettings::timestamp() const
{
    Q_D(const ConnectionSettings);

    return d->timestamp;
}

void NetworkManager::ConnectionSettings::setReadOnly(bool readonly)
{
    Q_D(ConnectionSettings);

    d->readOnly = readonly;
}

bool NetworkManager::ConnectionSettings::readOnly() const
{
    Q_D(const ConnectionSettings);

    return d->readOnly;
}

void NetworkManager::ConnectionSettings::setZone(const QString &zone)
{
    Q_D(ConnectionSettings);

    d->zone = zone;
}

QString NetworkManager::ConnectionSettings::zone() const
{
    Q_D(const ConnectionSettings);

    return d->zone;
}

bool NetworkManager::ConnectionSettings::isSlave() const
{
    Q_D(const ConnectionSettings);

    return !d->master.isEmpty() && !d->slaveType.isEmpty();
}

void NetworkManager::ConnectionSettings::setMaster(const QString &master)
{
    Q_D(ConnectionSettings);

    d->master = master;
}

QString NetworkManager::ConnectionSettings::master() const
{
    Q_D(const ConnectionSettings);

    return d->master;
}

void NetworkManager::ConnectionSettings::setSlaveType(const QString &type)
{
    Q_D(ConnectionSettings);

    d->slaveType = type;
}

QString NetworkManager::ConnectionSettings::slaveType() const
{
    Q_D(const ConnectionSettings);

    return d->slaveType;
}

void NetworkManager::ConnectionSettings::setSecondaries(const QStringList &secondaries)
{
    Q_D(ConnectionSettings);

    d->secondaries = secondaries;
}

QStringList NetworkManager::ConnectionSettings::secondaries() const
{
    Q_D(const ConnectionSettings);

    return d->secondaries;
}

void NetworkManager::ConnectionSettings::setGatewayPingTimeout(quint32 timeout)
{
    Q_D(ConnectionSettings);

    d->gatewayPingTimeout = timeout;
}

quint32 NetworkManager::ConnectionSettings::gatewayPingTimeout() const
{
    Q_D(const ConnectionSettings);

    return d->gatewayPingTimeout;
}

int NetworkManager::ConnectionSettings::autoconnectRetries() const
{
    Q_D(const ConnectionSettings);

    return d->autoconnectRetries;
}

void NetworkManager::ConnectionSettings::setAutoconnectRetries(int retries)
{
    Q_D(ConnectionSettings);

    d->autoconnectRetries = retries;
}

NetworkManager::ConnectionSettings::AutoconnectSlaves NetworkManager::ConnectionSettings::autoconnectSlaves() const
{
    Q_D(const ConnectionSettings);

    return d->autoconnectSlaves;
}

void NetworkManager::ConnectionSettings::setAutoconnectSlaves(NetworkManager::ConnectionSettings::AutoconnectSlaves autoconnectSlaves)
{
    Q_D(ConnectionSettings);

    d->autoconnectSlaves = autoconnectSlaves;
}

NetworkManager::ConnectionSettings::Lldp NetworkManager::ConnectionSettings::lldp() const
{
    Q_D(const ConnectionSettings);

    return d->lldp;
}

void NetworkManager::ConnectionSettings::setLldp(NetworkManager::ConnectionSettings::Lldp lldp)
{
    Q_D(ConnectionSettings);

    d->lldp = lldp;
}

NetworkManager::ConnectionSettings::Metered NetworkManager::ConnectionSettings::metered() const
{
    Q_D(const ConnectionSettings);

    return d->metered;
}

void NetworkManager::ConnectionSettings::setMetered(NetworkManager::ConnectionSettings::Metered metered)
{
    Q_D(ConnectionSettings);

    d->metered = metered;
}

QString NetworkManager::ConnectionSettings::stableId() const
{
    Q_D(const ConnectionSettings);

    return d->stableId;
}

void NetworkManager::ConnectionSettings::setStableId(const QString &stableId)
{
    Q_D(ConnectionSettings);

    d->stableId = stableId;
}

NetworkManager::Setting::Ptr NetworkManager::ConnectionSettings::setting(Setting::SettingType type) const
{
    Q_FOREACH (const Setting::Ptr & setting, settings()) {
        if (setting->type() == type) {
            return setting;
        }
    }

    return Setting::Ptr();
}

NetworkManager::Setting::Ptr NetworkManager::ConnectionSettings::setting(const QString &type) const
{
    return setting(Setting::typeFromString(type));
}

NetworkManager::Setting::List NetworkManager::ConnectionSettings::settings() const
{
    Q_D(const ConnectionSettings);

    return d->settings;
}

QDebug NetworkManager::operator <<(QDebug dbg, const NetworkManager::ConnectionSettings &setting)
{
    dbg.nospace() << "CONNECTION SETTINGS\n";
    dbg.nospace() << "===================\n";

    dbg.nospace() << NM_SETTING_CONNECTION_ID << ": " << setting.id() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_UUID << ": " << setting.uuid() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_INTERFACE_NAME << ": " << setting.interfaceName() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_TYPE << ": " << setting.typeAsString(setting.connectionType()) << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_PERMISSIONS << ": " << setting.permissions() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_AUTOCONNECT << ": " << setting.autoconnect() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_AUTOCONNECT_PRIORITY << ": " << setting.autoconnectPriority() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_TIMESTAMP << ": " << setting.timestamp().toTime_t() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_READ_ONLY << ": " << setting.readOnly() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_ZONE << ": " << setting.zone() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_MASTER << ": " << setting.master() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_SLAVE_TYPE << ": " << setting.slaveType() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_SECONDARIES << ": " << setting.secondaries() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_GATEWAY_PING_TIMEOUT << ": " << setting.gatewayPingTimeout() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_AUTOCONNECT_RETRIES << ": " << setting.autoconnectRetries() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_AUTOCONNECT_SLAVES << ": " << setting.autoconnectSlaves() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_LLDP << ": " << setting.lldp() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_METERED << ": " << setting.metered() << '\n';
    dbg.nospace() << NM_SETTING_CONNECTION_STABLE_ID << ": " << setting.stableId() << '\n';
    dbg.nospace() << "===================\n";
    Q_FOREACH (const Setting::Ptr & settingPtr, setting.settings()) {
        dbg.nospace() << settingPtr->typeAsString(settingPtr->type()).toUpper() << " SETTINGS\n";
        dbg.nospace() << "---------------------------\n";
        switch (settingPtr->type()) {
        case Setting::Adsl:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::AdslSetting>().data());
            break;
        case Setting::Bond:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::BondSetting>().data());
            break;
        case Setting::Bluetooth:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::BluetoothSetting>().data());
            break;
        case Setting::Bridge:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::BridgeSetting>().data());
            break;
        case Setting::BridgePort:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::BridgePortSetting>().data());
            break;
        case Setting::Cdma:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::CdmaSetting>().data());
            break;
        case Setting::Gsm:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::GsmSetting>().data());
            break;
        case Setting::Infiniband:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::InfinibandSetting>().data());
            break;
        case Setting::Ipv4:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::Ipv4Setting>().data());
            break;
        case Setting::Ipv6:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::Ipv6Setting>().data());
            break;
        case Setting::OlpcMesh:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::OlpcMeshSetting>().data());
            break;
        case Setting::Ppp:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::PppSetting>().data());
            break;
        case Setting::Pppoe:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::PppoeSetting>().data());
            break;
        case Setting::Security8021x:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::Security8021xSetting>().data());
            break;
        case Setting::Serial:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::SerialSetting>().data());
            break;
        case Setting::Vlan:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::VlanSetting>().data());
            break;
        case Setting::Vpn:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::VpnSetting>().data());
            break;
        case Setting::Wimax:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::WimaxSetting>().data());
            break;
        case Setting::Wired:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::WiredSetting>().data());
            break;
        case Setting::Wireless:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::WirelessSetting>().data());
            break;
        case Setting::WirelessSecurity:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::WirelessSecuritySetting>().data());
            break;
        case Setting::Team:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::TeamSetting>().data());
            break;
        case Setting::IpTunnel:
            dbg.nospace() << *(settingPtr.staticCast<NetworkManager::IpTunnelSetting>().data());
            break;
        default:
            dbg.nospace() << *settingPtr.data();
        }

        dbg.nospace() << '\n';
    }
    return dbg.maybeSpace();
}
