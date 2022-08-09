# CLI举例：配置Client-Initiated场景下的L2TP_VPN（本地认证）

## 组网需求  

企业希望公司外的移动办公用户能够通过L2TP VPN隧道访问公司内网的各种资源。  

![移动办公用户使用SecoClient通过L2TP_VPN隧道访问企业内网.png](移动办公用户使用SecoClient通过L2TP_VPN隧道访问企业内网.png)

## 数据规划  

```

```

## 思路  

1. 配置接口
2. 配置地址池 
3. 配置业务方案 
4. 配置VT接口
5. 配置L2TP group
6. 配置认证域和用户
7. 配置路由
8. 配置安全策略

## 操作  

```
interface GigabitEthernet1/0/0
 undo shutdown
 ip address 1.1.1.1 255.255.255.0
 service-manage all permit
firewall zone untrust
 add interface GigabitEthernet1/0/0
interface GigabitEthernet1/0/1
 undo shutdown
 ip address 10.1.1.1 255.255.255.0
 service-manage ping permit
firewall zone trust
 add interface GigabitEthernet1/0/1

ip pool test
 section 1 172.16.1.2 172.16.1.100

aaa
 service-scheme test
  ip-pool test

interface Virtual-Template1
 ppp authentication-mode chap
 y
 remote service-scheme test
 ip address 172.16.1.1 255.255.255.0
firewall zone dmz
 add interface Virtual-Template1

l2tp enable
l2tp-group default-lns
 undo tunnel authentication
 y
 allow l2tp virtual-template 1

security-policy
 rule name trust_to_dmz
  source-zone trust
  destination-zone dmz
  source-address 10.1.1.0 mask 255.255.255.0
  destination-address 172.16.1.0 mask 255.255.255.0
  action permit
 rule name dmz_to_trust
  source-zone dmz
  destination-zone trust
  source-address 172.16.1.0 mask 255.255.255.0
  destination-address 10.1.1.0 mask 255.255.255.0
  action permit
 rule name untrust_to_local
  source-zone untrust
  destination-zone local
  destination-address 1.1.1.0 mask 255.255.255.0
  action permit

aaa
 domain test
  service-type l2tp
  authentication-scheme default

aaa
 user-manage group /test/research
 user-manage group /default/research

aaa
 user-manage user user0001 domain test
  parent-group /test/research
  password Pa55word0001
 user-manage user user0001
  parent-group /default/research
  password Pa55word0001

```
