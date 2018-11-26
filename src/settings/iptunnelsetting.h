/*
    Copyright 2018 Jan Grulich <jgrulich@redhat.com>

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

#ifndef NETWORKMANAGERQT_IPTUNNEL_SETTING_H
#define NETWORKMANAGERQT_IPTUNNEL_SETTING_H

#include <networkmanagerqt/networkmanagerqt_export.h>
#include "setting.h"

#include <QString>

#define NMQT_SETTING_IP_TUNNEL_CONFIG_ENCAPSULATION_LIMIT   NM_SETTING_IP_TUNNEL_ENCAPSULATION_LIMIT
#define NMQT_SETTING_IP_TUNNEL_CONFIG_FLAGS                 "flags"//NM_SETTING_IP_TUNNEL_FLAGS
#define NMQT_SETTING_IP_TUNNEL_CONFIG_FLOW_LABEL            NM_SETTING_IP_TUNNEL_FLOW_LABEL
#define NMQT_SETTING_IP_TUNNEL_CONFIG_MTU                   NM_SETTING_IP_TUNNEL_MTU
#define NMQT_SETTING_IP_TUNNEL_CONFIG_TOS                   NM_SETTING_IP_TUNNEL_TOS
#define NMQT_SETTING_IP_TUNNEL_CONFIG_TTL                   NM_SETTING_IP_TUNNEL_TTL
#define NMQT_SETTING_IP_TUNNEL_CONFIG_INPUT_KEY             NM_SETTING_IP_TUNNEL_INPUT_KEY
#define NMQT_SETTING_IP_TUNNEL_CONFIG_LOCAL                 NM_SETTING_IP_TUNNEL_LOCAL
#define NMQT_SETTING_IP_TUNNEL_CONFIG_OUTPUT_KEY            NM_SETTING_IP_TUNNEL_OUTPUT_KEY
#define NMQT_SETTING_IP_TUNNEL_CONFIG_PARENT                NM_SETTING_IP_TUNNEL_PARENT
#define NMQT_SETTING_IP_TUNNEL_CONFIG_REMOTE                NM_SETTING_IP_TUNNEL_REMOTE
#define NMQT_SETTING_IP_TUNNEL_CONFIG_MODE                  NM_SETTING_IP_TUNNEL_MODE
#define NMQT_SETTING_IP_TUNNEL_CONFIG_PATH_MTU_DISCOVERY    NM_SETTING_IP_TUNNEL_PATH_MTU_DISCOVERY

namespace NetworkManager
{

class IpTunnelSettingPrivate;

/**
 * Represents generic setting
 */
class NETWORKMANAGERQT_EXPORT IpTunnelSetting : public Setting
{
public:
    typedef QSharedPointer<IpTunnelSetting> Ptr;
    typedef QList<Ptr> List;
    enum Mode { DefaultMode, Ipip, Gre };

    IpTunnelSetting();
    explicit IpTunnelSetting(const Ptr &other);
    ~IpTunnelSetting() override;

    QString name() const override;

    void setMode(Mode mode);
    Mode mode() const;

    void setPathMtuDiscovery(bool discovery);
    bool pathMtuDiscovery() const;

    void setEncapsulationLimit(quint32 limit);
    quint32 encapsulationLimit() const;

    void setFlags(quint32 flags);
    quint32 flags() const;

    void setFlowLabel(quint32 label);
    quint32 flowLabel() const;

    void setMtu(quint32 mtu);
    quint32 mtu() const;

    void setTos(quint32 tos);
    quint32 tos() const;

    void setTtl(quint32 ttl);
    quint32 ttl() const;

    void setInputKey(const QString& key);
    QString inputKey() const;

    void setLocal(const QString& local);
    QString local() const;

    void setOutputKey(const QString& key);
    QString outputKey() const;

    void setParent(const QString& parent);
    QString parent() const;

    void setRemote(const QString& remote);
    QString remote() const;

    void fromMap(const QVariantMap &setting) override;

    QVariantMap toMap() const override;

protected:
    IpTunnelSettingPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(IpTunnelSetting)
};

NETWORKMANAGERQT_EXPORT QDebug operator<<(QDebug dbg, const IpTunnelSetting &setting);

}

#endif // NETWORKMANAGERQT_IP_TUNNEL_SETTING_H

