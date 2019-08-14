
# SNMPTRAP  

## 测试模型  

snmptrapd来接收网络设备发出的trap,调用自定义的脚本处理trap或者转发trap  

![snmptrapArchitecture.jpg](snmptrapArchitecture.jpg)  

## 资料参考  

* [snmpd配置](http://www.net-snmp.org/wiki/index.php/TUT:SNMPv3_Options#Configuration)
* [snmpd,snmp配置](https://www.linuxidc.com/Linux/2016-03/129618.htm)
* [snmptrapd配置](http://www.net-snmp.org/wiki/index.php/TUT:Configuring_snmptrapd)
* [功能操作](http://www.net-snmp.org/wiki/index.php/TUT:SNMP)
* [TRAP功能](https://blog.csdn.net/huntinux/article/details/80527190)  

## 环境安装  

测试环境为ubuntu 1804，并切换到root用户  

*root@plus:~/C# uname -a  
Linux plus 4.15.0-55-generic #60-Ubuntu SMP Tue Jul 2 18:22:20 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux*  

安装组件  

```
apt-get update 
apt install snmp snmpd snmp-mibs-downloader snmptrapd libsnmp-dev
```  

## 配置修改  

```
mkdir -p /etc/snmp
mkdir -p ~/.snmp/mibs
_modifyTime=`date +"%Y%m%d_%H%M%S"`
#添加自定义mib
cat > ~/.snmp/mibs/IBM-DW-SAMPLE.mib << eof
IBM-DW-SAMPLE DEFINITIONS ::= BEGIN
IMPORTS
MODULE-IDENTITY, OBJECT-TYPE, TimeTicks FROM SNMPv2-SMI
DisplayString, FROM SNMPv2-TC
enterprises
FROM RFC1155-SMI;
test OBJECT IDENTIFIER ::= { enterprises 1000 }
TestTraps OBJECT IDENTIFIER ::= { test 1 }
nodeDown NOTIFICATION-TYPE
STATUS current
DESCRIPTION "node down notification"
::= { TestTraps 1 }
nodeDownTest0 OBJECT IDENTIFIER ::= { nodeDown 0 }
nodeDownTest1 OBJECT IDENTIFIER ::= { nodeDown 1 }
END
eof
#修改snmpd配置
cp /etc/snmp/snmpd.conf /etc/snmp/snmpd.conf.backup.$_modifyTime
cat > /etc/snmp/snmpd.conf << eof
agentAddress udp:127.0.0.1:161
rouser noAuthUser
rouser MD5User
rwuser MD5DESUser
createUser NoAuthUser
createUser MD5User MD5 "The Net-SNMP Demo Password"
createUser MD5DESUser MD5 "The Net-SNMP Demo Password" DES
view systemonly included .1.3.6.1.2.1.1
view systemonly included .1.3.6.1.2.1.25.1
view systemonly included .1
rocommunity public default -V systemonly
rocommunity6 public default -V systemonly
rouser authOnlyUser
sysLocation Sitting on the Dock of the Bay
sysContact Me <me@example.org>
sysServices 72
proc mountd
proc ntalkd 4
proc sendmail 10 1
disk / 10000
disk /var 5%
includeAllDisks 10%
load 12 10 5
trapsink localhost public
iquerySecName internalUser
rouser internalUser
defaultMonitors yes
linkUpDownNotifications yes
extend test1 /bin/echo Hello, world!
extend-sh test2 echo Hello, world! ; echo Hi there ; exit 35
master agentx
eof
#修改snmpd配置
cp /etc/snmp/snmp.conf /etc/snmp/snmp.conf.backup.$_modifyTime
echo mibs +/root/.snmp/mibs/IBM-DW-SAMPLE.mib > /etc/snmp/snmp.conf
#修改snmptrapd配置，增加对自定义类型PDU的处理 （指定由脚本/tmp/lognotify进行处理）
cp /etc/snmp/snmptrapd.conf /etc/snmp/snmptrapd.conf.backup.$_modifyTime
echo traphandle default /tmp/lognotify IBM-DW-SAMPLE::nodeDown > /etc/snmp/snmptrapd.conf
echo authCommunity log,execute,net public >> /etc/snmp/snmptrapd.conf
#服务重启
systemctl restart snmpd
```  

## 例子  

### 测试lib库是否能正常使用  

```
cat > testLib.c << eof
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <string.h>
#define _GOGOGO ".1.3.6.1.2.1.1.1.0"
/* change the word "define" to "undef" to try the (insecure) SNMPv1 version */
#define DEMO_USE_SNMP_VERSION_3
#ifdef DEMO_USE_SNMP_VERSION_3
const char *our_v3_passphrase = "The Net-SNMP Demo Password";
//const char *our_v3_passphrase = "public";
#endif
int main(int argc, char ** argv)
{
printf("...main\n");
netsnmp_session session, *ss;
netsnmp_pdu *pdu;
netsnmp_pdu *response;
oid anOID[MAX_OID_LEN];
size_t anOID_len;
netsnmp_variable_list *vars;
int status;
int count=1;
/*
* Initialize the SNMP library
*/
init_snmp("snmpdemoapp");
/*
* Initialize a "session" that defines who we're going to talk to
*/
snmp_sess_init( &session ); /* set up defaults */
//session.peername = strdup("test.net-snmp.org");
session.peername = strdup("127.0.0.1");
/* set up the authentication parameters for talking to the server */
#ifdef DEMO_USE_SNMP_VERSION_3
/* Use SNMPv3 to talk to the experimental server */
/* set the SNMP version number */
session.version=SNMP_VERSION_3;
/* set the SNMPv3 user name */
session.securityName = strdup("MD5User");
session.securityNameLen = strlen(session.securityName);
/* set the security level to authenticated, but not encrypted */
session.securityLevel = SNMP_SEC_LEVEL_AUTHNOPRIV;
/* set the authentication method to MD5 */
session.securityAuthProto = usmHMACMD5AuthProtocol;
session.securityAuthProtoLen = sizeof(usmHMACMD5AuthProtocol)/sizeof(oid);
session.securityAuthKeyLen = USM_AUTH_KU_LEN;
/* set the authentication key to a MD5 hashed version of our
passphrase "The Net-SNMP Demo Password" (which must be at least 8
characters long) */
if (generate_Ku(session.securityAuthProto,
session.securityAuthProtoLen,
(u_char *) our_v3_passphrase, strlen(our_v3_passphrase),
session.securityAuthKey,
&session.securityAuthKeyLen) != SNMPERR_SUCCESS) {
snmp_perror(argv[0]);
snmp_log(LOG_ERR,
"Error generating Ku from authentication pass phrase. \n");
exit(1);
}
#else /* we'll use the insecure (but simplier) SNMPv1 */
/* set the SNMP version number */
session.version = SNMP_VERSION_1;
/* set the SNMPv1 community name used for authentication */
session.community = "demopublic";
session.community_len = strlen(session.community);
#endif /* SNMPv1 */
/*
* Open the session
*/
SOCK_STARTUP;
printf("...snmp_open wait\n");
ss = snmp_open(&session); /* establish the session */
printf("...snmp_open ok\n");
if (!ss) {
snmp_sess_perror("ack", &session);
SOCK_CLEANUP;
exit(1);
}
/*
* Create the PDU for the data for our request.
* 1) We're going to GET the system.sysDescr.0 node.
*/
pdu = snmp_pdu_create(SNMP_MSG_GET);
anOID_len = MAX_OID_LEN;
//if (!snmp_parse_oid(".1.3.6.1.2.1.1.1.0", anOID, &anOID_len)) {
if (!snmp_parse_oid(_GOGOGO, anOID, &anOID_len)) {
//snmp_perror(".1.3.6.1.2.1.1.1.0");
snmp_perror(_GOGOGO);
SOCK_CLEANUP;
exit(1);
}
#if OTHER_METHODS
/*
* These are alternatives to the 'snmp_parse_oid' call above,
* e.g. specifying the OID by name rather than numerically.
*/
//read_objid(".1.3.6.1.2.1.1.1.0", anOID, &anOID_len);
read_objid(_GOGOGO, anOID, &anOID_len);
get_node("sysDescr.0", anOID, &anOID_len);
read_objid("system.sysDescr.0", anOID, &anOID_len);
#endif
snmp_add_null_var(pdu, anOID, anOID_len);
/*
* Send the Request out.
*/
status = snmp_synch_response(ss, pdu, &response);
/*
* Process the response.
*/
if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR) {
/*
* SUCCESS: Print the result variables
*/
for(vars = response->variables; vars; vars = vars->next_variable)
print_variable(vars->name, vars->name_length, vars);
/* manipuate the information ourselves */
for(vars = response->variables; vars; vars = vars->next_variable) {
if (vars->type == ASN_OCTET_STR) {
char *sp = (char *)malloc(1 + vars->val_len);
memcpy(sp, vars->val.string, vars->val_len);
sp[vars->val_len] = '\0';
printf("value #%d is a string: %s\n", count++, sp);
free(sp);
}
else
printf("value #%d is NOT a string! Ack!\n", count++);
}
} else {
/*
* FAILURE: print what went wrong!
*/
if (status == STAT_SUCCESS)
fprintf(stderr, "Error in packet\nReason: %s\n",
snmp_errstring(response->errstat));
else if (status == STAT_TIMEOUT)
fprintf(stderr, "Timeout: No response from %s.\n",
session.peername);
else
snmp_sess_perror("snmpdemoapp", ss);
}
/*
* Clean up:
* 1) free the response.
* 2) close the session.
*/
if (response)
snmp_free_pdu(response);
snmp_close(ss);
SOCK_CLEANUP;
return (0);
} /* main() */
#undef _GOGOGO
eof
gcc testLib.c -lnetsnmp && ./a.out
```  

输出结果  

*root@plus:~/snmp# gcc testLib.c -lnetsnmp && ./a.out  
...main  
...snmp_open wait  
...snmp_open ok  
SNMPv2-MIB::sysDescr.0 = STRING: Linux plus 4.15.0-55-generic #60-Ubuntu SMP Tue Jul 2 18:22:20 UTC 2019 x86_64  
value #1 is a string: Linux plus 4.15.0-55-generic #60-Ubuntu SMP Tue Jul 2 18:22:20 UTC 2019 x86_64*  

### 测试TRAP功能是否能正常使用  

创建处理脚本 /tmp/lognotify后启动snmptrapd  

```
cat > /tmp/lognotify <<eof
#!/bin/sh
read host
read ip
vars=
while read oid val
do
if [ "\$vars" = "" ]
then
vars="\$oid = \$val"
else
vars="\$vars, \$oid = \$val"
fi
done
echo trap: \$1 >/tmp/checkfile
echo host: \$host >>/tmp/checkfile
echo ip: \$ip >>/tmp/checkfile
echo vars: \$vars >>/tmp/checkfile
eof
chmod 777 /tmp/lognotify
snmptrapd -f -d -c /etc/snmp/snmptrapd.conf -Lo
```  

新建会话确认PDU类型的编号  

*root@plus:~/snmp# snmptranslate IBM-DW-SAMPLE::nodeDown -On  
.1.3.6.1.4.1.1000.1.1*
*root@plus:~/snmp# snmptranslate IBM-DW-SAMPLE::nodeDownTest0 -On  
.1.3.6.1.4.1.1000.1.1.0*
*root@plus:~/snmp# snmptranslate IBM-DW-SAMPLE::nodeDownTest1 -On  
.1.3.6.1.4.1.1000.1.1.1*  

创建测试程序  

```
cat > testTrap.c << eof
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
char peername[256],commu[256];
init_snmp("myexample");
struct snmp_session session;
snmp_sess_init(&session);
session.version = SNMP_VERSION_2c;
strcpy(peername,"127.0.0.1:162");
strcpy(commu,"public");
session.peername = peername;
session.community = (unsigned char*)commu;
session.community_len = strlen(commu);
netsnmp_session *ss = snmp_open(&session);
oid objid_sysuptime[] = { 1, 3, 6, 1, 2, 1, 1, 3, 0 };
oid objid_snmptrap[] = { 1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0 };
oid objid_test[] = { 1, 3, 6, 1, 4, 1, 1000, 1, 1, 0 };//Test0:1.3.6.1.4.1.1000.1.1.0 Test1:1.3.6.1.4.1.1000.1.1.1
netsnmp_pdu * pdu = NULL;
in_addr_t addr;
pdu = snmp_pdu_create(SNMP_MSG_TRAP2);
long sysuptime = 0;
char tempbuf[128];
memset(tempbuf,0 ,sizeof(tempbuf));
sysuptime = get_uptime();
sprintf(tempbuf,"%ld",sysuptime);
snmp_add_var(pdu, objid_sysuptime, sizeof(objid_sysuptime)/sizeof(oid), 't', tempbuf);
snmp_add_var(pdu, objid_snmptrap, sizeof(objid_snmptrap)/sizeof(oid),'o',"IBM-DW-SAMPLE::nodeDown");
snmp_add_var(pdu, objid_test, sizeof(objid_test)/sizeof(oid),'s',"test0..... successfully");
size_t tmpOID_len = 10;
oid tmpOID[10];
snmp_parse_oid("IBM-DW-SAMPLE::nodeDownTest1", tmpOID, &tmpOID_len);
snmp_add_var(pdu, tmpOID, sizeof(tmpOID)/sizeof(oid),'s',"test1..... successfully");
if( !snmp_send(ss, pdu) )
{
printf("Send pdu error \n");
}
snmp_close(ss);
snmp_shutdown( "myexample" );
SOCK_CLEANUP;
return 0;
}
eof
gcc testTrap.c -lnetsnmp && ./a.out
cat /tmp/checkfile
```  

输出结果  

*root@plus:~# cat /tmp/checkfile  
trap: IBM-DW-SAMPLE::nodeDown  
host: localhost.localdomain  
ip: UDP: [127.0.0.1]:56931->[127.0.0.1]:162  
vars: DISMAN-EVENT-MIB::sysUpTimeInstance = 0:2:00:14.98, SNMPv2-MIB::snmpTrapOID.0 = SNMPv2-SMI::enterprises.1000.1.1, SNMPv2-SMI::enterprises.1000.1.1.0 = "test0..... successfully", SNMPv2-SMI::enterprises.1000.1.1.1 = "test1..... successfully"*    

### 测试TRAP是否能正常转发  

添加转发规则到配置文件中，重新运行snmptrapd  

```
cat > /etc/snmp/snmptrapd.conf << eof
traphandle default /tmp/lognotify IBM-DW-SAMPLE::nodeDown
authCommunity log,execute,net public
forward default localhost:1620
forward default localhost:1621
forward default localhost:1622
eof
snmptrapd -f -d -c /etc/snmp/snmptrapd.conf -Lo
```  

另外新建三个窗口运行新的snmptrapd并且不指定配置文件(用/etc/snmp/snmptrapd.conf会造成无穷无尽的转发)，分别监听1620、1621、1622端口  

```
snmptrapd -f -d -Lo 1620
```  

```
snmptrapd -f -d -Lo 1621
```  

```
snmptrapd -f -d -Lo 1622
```  

新建窗口执行测试程序  

```
gcc testTrap.c -lnetsnmp && ./a.out
```  

可观察到每个窗口下的程序都能接收snmptrap报文  

### 测试INFORM功能是否能正常使用  

与TRAP功能类似，将代码中SNMP_MSG_TRAP2改为SNMP_MSG_INFORM再编译运行，snmptrapd接收到消息会进行反馈。  


