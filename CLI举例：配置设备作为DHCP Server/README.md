# CLI举例：配置设备作为DHCP Server  

## 组网需求  

三层以太网接口配置基于接口地址池的DHCP Server。  

### 数据规划

|项目|数据|说明|
|----|----|----|
|接口|GigabitEthernet0/0/0||
|ip|192.0.1.1/24||
|安全域|trust||
|ip池|192.0.1.10[0-9]||
|网关|192.0.1.1||
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
 ip address 192.0.1.1 255.255.255.0
firewall zone trust
 add interface GigabitEthernet0/0/0

interface GigabitEthernet0/0/0
 dhcp server mask 255.255.255.0
 dhcp server ip-range 192.0.1.100 192.0.1.109
 dhcp select interface
 dhcp server gateway-list 192.0.1.1
 dhcp server lease day 0 hour 0 minute 10
 dhcp server dns-list 114.114.114.114 8.8.8.8

```

## 组网需求  

vlan接口配置基于接口地址池的DHCP Server。  

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

## 组网需求  

三层以太网接口配置基于全局地址池的DHCP Server。  

### 数据规划

|项目|数据|说明|
|----|----|----|
|接口|GigabitEthernet0/0/3||
|ip|192.100.1.1/24||
|安全域|trust||
|ip池|192.100.1.0/24||
|网关|192.100.1.1||
|期限|10 min||

### 思路  

1. 开启dhcp。  
2. 配置三层接口。  
3. 配置全局ip地址池。 
4. 配置dhcp。   
5. 验证客户端。  

### 操作  

```
dhcp enable

interface GigabitEthernet0/0/3
 ip address 192.100.1.1 255.255.255.0
firewall zone trust
 add interface GigabitEthernet0/0/3

ip pool 1001
 gateway-list 192.100.1.1
 network 192.100.1.0 mask 255.255.255.0
 lease day 0 hour 0 minute 10
 domain-name example.com

interface GigabitEthernet0/0/3
 dhcp select global

```

## 组网需求  

vlan接口配置基于全局地址池的DHCP Server。  

### 数据规划

|项目|数据|说明|
|----|----|----|
|二层接口|GigabitEthernet0/0/4||
|vlan|1002||
|vlan接口|Vlanif1002||
|ip|192.100.2.1/24||
|安全域|trust||
|ip池|192.100.2.0/24||
|网关|192.100.2.1||
|期限|10 min||

### 思路  

1. 开启dhcp。  
2. 配置二层接口。  
2. 配置vlan接口。  
3. 配置全局ip地址池。 
4. 配置dhcp。   
6. 验证客户端。  

### 操作  

```
dhcp enable

vlan 1002
interface GigabitEthernet0/0/4
 portswitch
 port link-type trunk
 port trunk pvid vlan 1002
 port trunk allow-pass vlan 1002
firewall zone trust
 add interface GigabitEthernet0/0/4

interface Vlanif 1002
 ip address 192.100.2.1 255.255.255.0
firewall zone trust
 add interface Vlanif 1002

ip pool 1002
 gateway-list 192.100.2.1
 network 192.100.2.0 mask 255.255.255.0
 lease day 0 hour 0 minute 10
 domain-name example.com

interface Vlanif 1002
 dhcp select global

```
