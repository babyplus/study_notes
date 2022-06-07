# CLI举例：配置设备作为DHCP Server（基于接口地址池）  

## 组网需求  

通过三层以太网接口配置基于基于接口地址池的DHCP Server。  

### 数据规划

|项目|数据|说明|
|----|----|----|
|接口|GigabitEthernet0/0/0||
|ip|192.168.7.7/24||
|安全域|trust||
|ip池|192.168.7.10[0-9]||
|网关|192.168.7.7||
|期限|10 min||

### 思路  

1. 开启dhcp。  
2. 配置接口。  
3. 配置dhcp。  
4. 验证客户端。  

### 操作  

```
dhcp enable

interface GigabitEthernet0/0/0
 ip address 192.168.7.7 255.255.255.0
firewall zone trust
 add interface GigabitEthernet0/0/0

interface GigabitEthernet0/0/0
 dhcp server mask 255.255.255.0
 dhcp server ip-range 192.168.7.100 192.168.7.109
 dhcp select interface
 dhcp server gateway-list 192.168.7.7
 dhcp server lease day 0 hour 0 minute 10
 dhcp server dns-list 114.114.114.114 8.8.8.8

```

## 组网需求  

通过vlan接口配置基于基于接口地址池的DHCP Server。  

### 数据规划

|项目|数据|说明|
|----|----|----|
|二层接口|GigabitEthernet0/0/1||
|vlan|1000||
|vlan接口|Vlanif1000||
|ip|192.100.0.1/24||
|安全域|trust||
|ip池|192.100.0.10[0-9]||
|网关|192.100.0.1||
|期限|10 min||

### 思路  

1. 开启dhcp。  
2. 配置二层接口。  
3. 配置vlan接口。  
4. 配置dhcp。  
5. 验证客户端。  

### 操作  

```
dhcp enable

vlan 1000
interface GigabitEthernet0/0/1
 portswitch
 port link-type trunk
 port trunk pvid vlan 1000
 port trunk allow-pass vlan 1000
firewall zone trust
 add interface GigabitEthernet0/0/1

interface Vlanif 1000
 ip address 192.100.0.1 255.255.255.0
firewall zone trust
 add interface Vlanif 1000

interface Vlanif 1000
 dhcp server mask 255.255.255.0
 dhcp server ip-range 192.100.0.100 192.100.0.109
 dhcp select interface
 dhcp server gateway-list 192.100.0.1
 dhcp server lease day 0 hour 0 minute 10
 dhcp server dns-list 114.114.114.114 8.8.8.8
```
