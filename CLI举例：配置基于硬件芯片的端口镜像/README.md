# CLI举例：配置基于硬件芯片的端口镜像  

## 需求  

开启端口镜像功能后，将观测端口与网络流量分析设备相连，即可分析出镜像端口上的各应用报文的分布情况。  

### 规划  

|项目|数据|说明|
|----|----|----|
|观测端口|GigabitEthernet0/0/7|| 
|业务端口|GigabitEthernet0/0/1||

### 思路  

1. 配置观测端口。  
2. 启动端口镜像。  

### 操作  

```
observing-port hardware GigabitEthernet 0/0/7
port-mirroring hardware GigabitEthernet 0/0/1 both GigabitEthernet 0/0/7
y
```
