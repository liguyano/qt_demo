# CHATLITE

## what to do

about the feature of this file.  
This project is build for the local net text and **binary** *file* transport.

## about version 2.2

update in 2024年1月19日17点37分

use the broadcast function to find the other host.

but it can only run in

```c++ 
for (auto ip: all_ip) {
        auto ips = ip.toString();
        auto all = ips.split('.');
        for (int i = 0; i < 255; ++i) {
                needIp=ipAddr.arg(all[0]).arg(all[1]).arg(i).arg(255);
                QHostAddress tmp(needIp);tcp->getUdpSock()->writeDatagram("hello", tmp, this->port);
        }
    }
```

but can't be in

```c++
for (auto ip: all_ip) {
        auto ips = ip.toString();
        auto all = ips.split('.');
        
                needIp=ipAddr.arg(all[0]).arg(all[1]).arg(255).arg(255);
                QHostAddress tmp(needIp);tcp->getUdpSock()->writeDatagram("hello", tmp, this->port);
        
    }
```

## about this version 1.0

this version is already implement the text send and ***file convert***. But the
*last part* of the scent file can't be received. Reason unknown.  
This project is powered by QT.

> System.out.println("hello world");

## about this version 2.0

this version can show the ipaddress and use a name instand of an ip  
and it can send the full file now!

* 111
* 222

``int itime=0;
while (true)
{
sleep(1);
itime++;
itime%=50;
if (itime==40)
{
// emit testAlive();}}
``
---
[offical net](http://124.222.232.23:8080/firstweb/register.html)  
<www.bilibili.com>  
[![nothing](mainwindow.png)]

## about the version 2.1

we fineshed the file transport the file less than 1GB. And trans diractions.And file
save path and the net port name of self computer can be change now.

## about the version 2.2

we can use a css file to control to the test style now.
> &lt;link rel="stylesheet" type="text/css" href="./setting/style.css"&gt;

