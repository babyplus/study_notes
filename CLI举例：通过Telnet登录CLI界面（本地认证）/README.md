# CLI举例：通过Telnet登录CLI界面（本地认证）  

## 组网需求  

管理员可以通过Telnet登录到CLI界面对FW进行管理和维护。FW对管理员进行本地认证。  

## 数据规划  

|项目|数据|说明|
|----|----|----|
|VTY界面超时断连时间|5分钟|默认为10分钟|
|自动锁定的验证失败次数|2次|默认为3次|
|自动锁定的时间|10分钟|默认为30分钟|
|帐号密码|vtyadmin Huawei@123||
|IP|192.168.7.7/24||

## 思路  

1. 开启Telnet
2. 配置接口
3. 配置vty
4. 配置管理员
5. 配置ip并验证

## 操作  

```

telnet server enable
interface GigabitEthernet 0/0/0
ip address 192.168.7.7 255.255.255.0
service-manage telnet permit
firewall zone trust
add interface GigabitEthernet 0/0/0

user-interface vty 0 4
authentication-mode aaa
protocol inbound telnet
user privilege level 3
idle-timeout 5

aaa
role service-admin
dashboard read-write
monitor read-write
system read-write
network read-write
object read-write
policy read-write

manager-user vtyadmin
password cipher Huawei@123
service-type telnet
level 15
bind manager-user vtyadmin role service-admin

lock-authentication enable
lock-authentication failed-count 2 
lock-authentication timeout 10

```
