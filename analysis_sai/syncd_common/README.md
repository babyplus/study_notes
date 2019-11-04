## syncd    

资料参考:  

* [sonic镜像构建说明](https://github.com/Azure/sonic-buildimage/blob/201904/README.md)    
* [基础通用镜像](https://github.com/Azure/sonic-buildimage/blob/201904/platform/template/docker-syncd-base.mk)    
* [syncd_start.sh](https://github.com/Azure/sonic-sairedis/blob/d5c89cd92d93cd0ec338c629046f67cf22a54e38/syncd/scripts/syncd_start.sh)   
* [根据不同平台配置syncd](https://github.com/Azure/sonic-sairedis/blob/d5c89cd92d93cd0ec338c629046f67cf22a54e38/syncd/scripts/syncd_init_common.sh)

supervisor启动配置  

```
root@sonic:/etc/supervisor/conf.d# cat supervisord.conf 
[supervisord]
logfile_maxbytes=1MB
logfile_backups=2
nodaemon=true

[program:start.sh]
command=/usr/bin/start.sh
priority=1
autostart=true
autorestart=false
stdout_logfile=syslog
stderr_logfile=syslog

[program:rsyslogd]
command=/usr/sbin/rsyslogd -n
priority=2
autostart=false
autorestart=false
stdout_logfile=syslog
stderr_logfile=syslog

[program:syncd]
command=/usr/bin/syncd_start.sh
priority=3
autostart=false
autorestart=false
stdout_logfile=syslog
stderr_logfile=syslog

```  

/usr/bin/start.sh  

```
root@sonic:/etc/supervisor/conf.d# cat /usr/bin/start.sh
#!/usr/bin/env bash

PLATFORM_DIR=/usr/share/sonic/platform
HWSKU_DIR=/usr/share/sonic/hwsku

SYNCD_SOCKET_FILE=/var/run/sswsyncd/sswsyncd.socket

# Function: wait until syncd has created the socket for bcmcmd to connect to
wait_syncd() {
    while true; do
        if [ -e ${SYNCD_SOCKET_FILE} ]; then
            break
        fi
        sleep 1
    done

    # wait until bcm sdk is ready to get a request
    sleep 3
}


# Remove stale files if they exist
rm -f /var/run/rsyslogd.pid
rm -f ${SYNCD_SOCKET_FILE}

supervisorctl start rsyslogd

mkdir -p /etc/sai.d/

# Create/Copy the sai.profile to /etc/sai.d/sai.profile
if [ -f $HWSKU_DIR/sai.profile.j2 ]; then
    sonic-cfggen -d -t $HWSKU_DIR/sai.profile.j2 > /etc/sai.d/sai.profile
else
    if [ -f $HWSKU_DIR/sai.profile ]; then
        cp $HWSKU_DIR/sai.profile /etc/sai.d/sai.profile
    fi
fi

supervisorctl start syncd

# If this platform has an initialization file for the Broadcom LED microprocessor, load it
if [ -r ${PLATFORM_DIR}/led_proc_init.soc ]; then
    wait_syncd
    supervisorctl start ledinit
fi

```  

/usr/bin/syncd_start.sh   

```
root@sonic:/etc/supervisor/conf.d# cat /usr/bin/syncd_start.sh
#!/usr/bin/env bash
#
# Script to start syncd using supervisord
#

# Source the file that holds common code for systemd and supervisord
. /usr/bin/syncd_init_common.sh

config_syncd

exec ${CMD} ${CMD_ARGS}

```  

不同平台会读取同一个配置文件/etc/sai.d/sai.profile   

```
root@sonic:/# cat /etc/sai.d/sai.profile 
SAI_WARM_BOOT_READ_FILE=/var/cache/sai_warmboot.bin
SAI_WARM_BOOT_WRITE_FILE=/var/cache/sai_warmboot.bin
SAI_VS_SWITCH_TYPE=SAI_VS_SWITCH_TYPE_BCM56850
SAI_VS_HOSTIF_USE_TAP_DEVICE=true
SAI_VS_INTERFACE_LANE_MAP_FILE=/usr/share/sonic/hwsku/lanemap.ini
```  


