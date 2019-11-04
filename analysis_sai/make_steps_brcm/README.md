### 博通平台相关makefile    

在[sonic镜像构建说明](https://github.com/Azure/sonic-buildimage/blob/201904/README.md)中搜索 docker-syncd-brcm.gz   

构建镜像时会在./target目录生成docker-syncd-brcm.gz     

#### rules.mk  

根据rules.mk进行分析  
   
* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/rules.mk  


```
# Inject brcm sai into sairedis
$(LIBSAIREDIS)_DEPENDS += $(BRCM_SAI) $(BRCM_SAI_DEV) $(LIBSAITHRIFT_DEV)
```

##### sai-modules.mk

* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/sai-modules.mk

```
#Broadcom SAI modules  
KVERSION = 4.9.0-9-2-amd64
BRCM_OPENNSL_KERNEL_VERSION = 3.4.1.11-1
BRCM_OPENNSL_KERNEL = opennsl-modules_$(BRCM_OPENNSL_KERNEL_VERSION)_amd64.deb
$(BRCM_OPENNSL_KERNEL)_SRC_PATH = $(PLATFORM_PATH)/saibcm-modules
$(BRCM_OPENNSL_KERNEL)_DEPENDS += $(LINUX_HEADERS) $(LINUX_HEADERS_COMMON)
SONIC_DPKG_DEBS += $(BRCM_OPENNSL_KERNEL)
SONIC_STRETCH_DEBS += $(BRCM_OPENNSL_KERNEL)
```

在依赖包里加入了opennsl-modules_3.4.1.11-1_amd64.deb  

[github上有个opennsl项目但是没找到对应版本](https://github.com/Broadcom-Switch/OpenNSL/tree/master)    

##### sai.mk

* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/sai.mk

```
BRCM_SAI = libsaibcm_3.5.2.3_amd64.deb
```

 看起来像是只提供库，不提供源码   
 
 [在GitHub上找到个类似项目但是没那么新并且可能对芯片型号有要求](https://github.com/Broadcom-Switch/SAI)  
 
This SAI release supports the Broadcom TD2, Tomahawk and TH2 switching ASIC.  

```
$(eval $(call add_derived_package,$(BRCM_SAI),$(BRCM_SAI_DEV)))
```  

这句话看不懂!!!    

##### platform-modules-XXXX.mk

应该是针对厂商,有源码   

##### docker-syncd-brcm.mk

* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/docker-syncd-brcm.mk    
* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/docker-syncd-brcm/Dockerfile.j2

往基础镜像里添加安装包(在其他主机里抽出来的,版本不一定正确)   

* debs/libnl-3-200_3.2.27-2_amd64.deb
* debs/libnl-route-3-200_3.2.27-2_amd64.deb
* debs/libnl-genl-3-200_3.2.27-2_amd64.deb
* debs/libnl-nf-3-200_3.2.27-2_amd64.deb
* debs/libhiredis0.13_0.13.3-2_amd64.deb
* debs/libnl-cli-3-200_3.2.27-2_amd64.deb
* debs/libswsscommon_1.0.0_amd64.deb
* debs/libsairedis_1.0.0_amd64.deb
* debs/libsaimetadata_1.0.0_amd64.deb
* debs/libsaibcm_3.5.2.3_amd64.deb
* debs/syncd_1.0.0_amd64.deb
   
   
```
sonic@sonic-KVM:~/sonic-buildimage-broadcom$ cat ./platform/broadcom/docker-syncd-brcm/Dockerfile
FROM docker-config-engine-stretch

ARG docker_container_name
RUN [ -f /etc/rsyslog.conf ] && sed -ri "s/%syslogtag%/$docker_container_name#%syslogtag%/;" /etc/rsyslog.conf

## Make apt-get non-interactive
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update

COPY \
debs/libnl-3-200_3.2.27-2_amd64.deb debs/libnl-route-3-200_3.2.27-2_amd64.deb debs/libnl-genl-3-200_3.2.27-2_amd64.deb debs/libnl-nf-3-200_3.2.27-2_amd64.deb debs/libhiredis0.13_0.13.3-2_amd64.deb debs/libnl-cli-3-200_3.2.27-2_amd64.deb debs/libswsscommon_1.0.0_amd64.deb debs/libsairedis_1.0.0_amd64.deb debs/libsaimetadata_1.0.0_amd64.deb debs/libsaibcm_3.5.2.3_amd64.deb debs/syncd_1.0.0_amd64.deb debs/

RUN dpkg -i \
debs/libnl-3-200_3.2.27-2_amd64.deb debs/libnl-route-3-200_3.2.27-2_amd64.deb debs/libnl-genl-3-200_3.2.27-2_amd64.deb debs/libnl-nf-3-200_3.2.27-2_amd64.deb debs/libhiredis0.13_0.13.3-2_amd64.deb debs/libnl-cli-3-200_3.2.27-2_amd64.deb debs/libswsscommon_1.0.0_amd64.deb debs/libsairedis_1.0.0_amd64.deb debs/libsaimetadata_1.0.0_amd64.deb debs/libsaibcm_3.5.2.3_amd64.deb debs/syncd_1.0.0_amd64.deb 

## TODO: add kmod into Depends
RUN apt-get install -yf kmod

COPY ["files/dsserve", "files/bcmcmd", "start.sh", "bcmsh", "/usr/bin/"]
RUN chmod +x /usr/bin/dsserve /usr/bin/bcmcmd

COPY ["supervisord.conf", "/etc/supervisor/conf.d/"]

## Clean up
RUN apt-get clean -y; apt-get autoclean -y; apt-get autoremove -y
RUN rm -rf /debs

ENTRYPOINT ["/usr/bin/supervisord"]

```

##### docker-syncd-brcm-rpc.mk

* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/docker-syncd-brcm-rpc.mk    
* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/docker-syncd-brcm-rpc/Dockerfile.j2    

在docker-syncd-brcm的基础上增加了nanomsg,cffi,nnpy   

* nanomsg: 类似rabbitmq  
* cffi: python调用C的工具包

##### docker-saiserver-brcm.mk

* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/docker-saiserver-brcm.mk
* https://github.com/Azure/sonic-buildimage/blob/201904/platform/broadcom/docker-saiserver-brcm/Dockerfile.j2    

```
COPY \
{% for deb in docker_saiserver_brcm_debs.split(' ') -%}
debs/{{ deb }}{{' '}}
{%- endfor -%}
debs/

RUN dpkg_apt() { [ -f $1 ] && { dpkg -i $1 || apt-get -y install -f; } || return 
1; } ; \
{% for deb in docker_saiserver_brcm_debs.split(' ') -%}
dpkg_apt debs/{{ deb }}{{'; '}}
{%- endfor %}
```

saiserver暂时不清楚用来干嘛   

用start.sh在supervisor注册一个服务，运行时会先注册日志服务，创建字符串设备文件，启动saiserver   

##### one-image.mk

略

##### raw-image.mk

略

##### one-aboot.mk

略

##### libsaithrift-dev.mk

* libsaithrift-dev_0.9.4_amd64.deb
* python-saithrift_0.9.4_amd64.deb
* saiserver_0.9.4_amd64.deb
* saiserver-dbg_0.9.4_amd64.deb
  
  
##### docker-ptf-brcm.mk

略
